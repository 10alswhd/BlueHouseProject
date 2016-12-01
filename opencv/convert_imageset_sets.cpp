#include <string>
#include <vector>
#include <utility>
#include <string>
#include <opencv2/opencv.hpp>
#include <leveldb/db.h>
#include <pficommon/text/json.h>
#include <pficommon/math/random.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <lmdb.h>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>  // NOLINT(readability/streams)
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"
#include "caffe/util/rng.hpp"


typedef std::pair<std::vector<std::string>, int> Line;
typedef std::vector<Line> Lines;
typedef std::vector< cv::Mat_<cv::Vec3b> > Images;

// From http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?string%A4%CB%A4%E8%A4%EB%CA%B8%BB%FA%CE%F3%BD%E8%CD%FD#z1afc674
inline bool IsInteger(const std::string &str) {
    if(str.find_first_not_of("-0123456789 \t") != std::string::npos) {
        return false;
    }

    return true;
}

void CVMatSetToDatum(Images& images, caffe::Datum& datum) {
  int image_num = static_cast<int>(images.size());

  datum.set_channels(images[0].channels() * image_num);
  datum.set_height(images[0].rows);
  datum.set_width(images[0].cols);
  datum.clear_data();
  datum.clear_float_data();
  // datum.set_encoded(false);
  int datum_channels = datum.channels();
  int datum_height = datum.height();
  int datum_width = datum.width();
  int datum_size = datum_channels * datum_height * datum_width;
  int offset = image_num * images[0].rows * images[0].cols;
  std::string buffer(datum_size, ' ');
  for (int h = 0; h < datum_height; ++h) {
    for (int w = 0; w < datum_width; ++w) {
      for (int c = 0; c < 3; ++c) {
        int datum_index = (c * datum_height + h) * datum_width + w;
        for (int n = 0; n < image_num; n++){
          buffer[datum_index + offset * n] = static_cast<char>(images[n](h, w)[c]);
        }
      }
    }
  }
  datum.set_data(buffer);
}

cv::Mat_<cv::Vec3b> read_image(const std::string& path) {
  cv::Mat_<cv::Vec3b> image = cv::imread(path, 1);
  if (image.empty()) {
    throw std::runtime_error("Cannot open " + path);
  }
  return image;
}

bool ReadImageSetToDatum(Line files_and_label, std::string root, caffe::Datum& datum){
  Images images;
  std::string buf;

  for (int i = 0; i < static_cast<int>(files_and_label.first.size()); i++){
    images.push_back(read_image(root + files_and_label.first[i]));
  }

  CVMatSetToDatum(images, datum);
  datum.set_label(files_and_label.second);

  return true;
}


using namespace caffe;  // NOLINT(build/namespaces)
using std::pair;
using std::string;

DEFINE_bool(gray, false,
    "When this option is on, treat images as grayscale ones");
DEFINE_bool(shuffle, false,
    "Randomly shuffle the order of images and their labels");
DEFINE_string(backend, "lmdb", "The backend for storing the result");
DEFINE_int32(resize_width, 0, "Width images are resized to");
DEFINE_int32(resize_height, 0, "Height images are resized to");

int main(int argc, char** argv) {
  ::google::InitGoogleLogging(argv[0]);

#ifndef GFLAGS_GFLAGS_H_
  namespace gflags = google;
#endif

  gflags::SetUsageMessage("Convert a set of images to the leveldb/lmdb\n"
        "format used as input for Caffe.\n"
        "Usage:\n"
        "    convert_imageset [FLAGS] ROOTFOLDER/ LISTFILE DB_NAME\n"
        "The ImageNet dataset for the training demo is at\n"
        "    http://www.image-net.org/download-images\n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (argc != 4) {
    gflags::ShowUsageWithFlagsRestrict(argv[0], "tools/convert_imageset");
    return 1;
  }

  bool is_color = !FLAGS_gray;
  std::ifstream infile(argv[2]);

  // Read images to std::vector
  Lines lines;
  std::string buf;
  int label;
  while (std::getline(infile, buf)){
    std::string tmp_s;
    std::stringstream stream(buf);
    std::vector<std::string> tmp_v;

    while(std::getline(stream, tmp_s, ' ')){
        tmp_v.push_back(tmp_s);
    }

    label = std::atoi(tmp_v[tmp_v.size()-1].c_str());
    tmp_v.pop_back();

    lines.push_back(std::make_pair(tmp_v, label));
  }

  int image_num = lines[0].first.size();
  LOG(INFO) << "Number of image by each line is " << image_num << ".";

  if (FLAGS_shuffle) {
    // randomly shuffle data
    LOG(INFO) << "Shuffling data";
    shuffle(lines.begin(), lines.end());
  }
  LOG(INFO) << "A total of " << lines.size() << " sets (." << lines.size() * image_num <<  " images)";

  const string& db_backend = FLAGS_backend;
  const char* db_path = argv[3];

  int resize_height = std::max<int>(0, FLAGS_resize_height);
  int resize_width = std::max<int>(0, FLAGS_resize_width);

  // Open new db
  // lmdb
  MDB_env *mdb_env;
  MDB_dbi mdb_dbi;
  MDB_val mdb_key, mdb_data;
  MDB_txn *mdb_txn;
  // leveldb
  leveldb::DB* db;
  leveldb::Options options;
  options.error_if_exists = true;
  options.create_if_missing = true;
  options.write_buffer_size = 268435456;
  leveldb::WriteBatch* batch = NULL;

  // Open db
  if (db_backend == "leveldb") {  // leveldb
    LOG(INFO) << "Opening leveldb " << db_path;
    leveldb::Status status = leveldb::DB::Open(
        options, db_path, &db);
    CHECK(status.ok()) << "Failed to open leveldb " << db_path
        << ". Is it already existing?";
    batch = new leveldb::WriteBatch();
  } else if (db_backend == "lmdb") {  // lmdb
    LOG(INFO) << "Opening lmdb " << db_path;
    CHECK_EQ(mkdir(db_path, 0744), 0)
        << "mkdir " << db_path << "failed";
    CHECK_EQ(mdb_env_create(&mdb_env), MDB_SUCCESS) << "mdb_env_create failed";
    CHECK_EQ(mdb_env_set_mapsize(mdb_env, 1099511627776), MDB_SUCCESS)  // 1TB
        << "mdb_env_set_mapsize failed";
    CHECK_EQ(mdb_env_open(mdb_env, db_path, 0, 0664), MDB_SUCCESS)
        << "mdb_env_open failed";
    CHECK_EQ(mdb_txn_begin(mdb_env, NULL, 0, &mdb_txn), MDB_SUCCESS)
        << "mdb_txn_begin failed";
    CHECK_EQ(mdb_open(mdb_txn, NULL, 0, &mdb_dbi), MDB_SUCCESS)
        << "mdb_open failed. Does the lmdb already exist?";
  } else {
    LOG(FATAL) << "Unknown db backend " << db_backend;
  }

  // Storing to db
  string root_folder(argv[1]);
  Datum datum;
  int count = 0;
  const int kMaxKeyLength = 256;
  char key_cstr[kMaxKeyLength];
  int data_size;
  bool data_size_initialized = false;

  for (int line_id = 0; line_id < lines.size(); ++line_id) {
    if(!ReadImageSetToDatum(lines[line_id], root_folder, datum)){
      // std::cout << "aaaa" << std::endl;
      continue;
    }
    if (!data_size_initialized) {
      data_size = datum.channels() * datum.height() * datum.width();
      data_size_initialized = true;
    } else {
      const string& data = datum.data();
      CHECK_EQ(data.size(), data_size) << "Incorrect data field size "
          << data.size();
    }
    // sequential
    snprintf(key_cstr, kMaxKeyLength, "%08d", line_id);
    string value;
    datum.SerializeToString(&value);
    string keystr(key_cstr);

    // Put in db
    if (db_backend == "leveldb") {  // leveldb
      batch->Put(keystr, value);
    } else if (db_backend == "lmdb") {  // lmdb
      mdb_data.mv_size = value.size();
      mdb_data.mv_data = reinterpret_cast<void*>(&value[0]);
      mdb_key.mv_size = keystr.size();
      mdb_key.mv_data = reinterpret_cast<void*>(&keystr[0]);
      CHECK_EQ(mdb_put(mdb_txn, mdb_dbi, &mdb_key, &mdb_data, 0), MDB_SUCCESS)
          << "mdb_put failed";
    } else {
      LOG(FATAL) << "Unknown db backend " << db_backend;
    }

    if (++count % 1000 == 0) {
      // Commit txn
      if (db_backend == "leveldb") {  // leveldb
        db->Write(leveldb::WriteOptions(), batch);
        delete batch;
        batch = new leveldb::WriteBatch();
      } else if (db_backend == "lmdb") {  // lmdb
        CHECK_EQ(mdb_txn_commit(mdb_txn), MDB_SUCCESS)
            << "mdb_txn_commit failed";
        CHECK_EQ(mdb_txn_begin(mdb_env, NULL, 0, &mdb_txn), MDB_SUCCESS)
            << "mdb_txn_begin failed";
      } else {
        LOG(FATAL) << "Unknown db backend " << db_backend;
      }
      LOG(ERROR) << "Processed " << count << " files.";
    }
  }
  // write the last batch
  if (count % 1000 != 0) {
    if (db_backend == "leveldb") {  // leveldb
      db->Write(leveldb::WriteOptions(), batch);
      delete batch;
      delete db;
    } else if (db_backend == "lmdb") {  // lmdb
      CHECK_EQ(mdb_txn_commit(mdb_txn), MDB_SUCCESS) << "mdb_txn_commit failed";
      mdb_close(mdb_env, mdb_dbi);
      mdb_env_close(mdb_env);
    } else {
      LOG(FATAL) << "Unknown db backend " << db_backend;
    }
    LOG(ERROR) << "Processed " << count << " files.";
  }
  return 0;
}
