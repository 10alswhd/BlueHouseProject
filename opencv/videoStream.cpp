#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>

// For UDPSocket and SocketException
#include "PracticalSocket.h"
#include "config.h"

// Stitching
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include <zmq.hpp>

using namespace cv;
using namespace std;

// int sizeofmat(Mat *mat) {
//     return mat->rows * mat->cols * CV_ELEM_SIZE();
// }

int main(int argc, char * argv[]) {

    // if ((argc < 3) || (argc > 3)) { // Test for correct number of arguments
    //     cerr << "Usage: " << argv[0] << " <Server> <Server Port>\n";
    //     exit(1);
    // }

    string servAddress = "127.0.0.1"; // First arg: server address
    // unsigned short servPort0 = Socket::resolveService("10000", "udp");
    // unsigned short servPort1 = Socket::resolveService("10001", "udp");

    // Declare Mats
    Mat edges, edges1, view, map1, map2, frame, frame1, newCamMat, cameraMatrix, distCoeffs;

    // Config file
    std::string filename = "out_camera_data.xml";
    std::string config_distortion_coeff = "distortion_coefficients";
    std::string config_camera_matrix= "camera_matrix";

    // Camera 0
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) {
        cout <<  "Can't find camera 0" << endl;
        return -1;
    }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    // declare video window
    namedWindow("Camera 0",1);

  const double fps = cap.get(CV_CAP_PROP_FPS);
  const int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  const int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    // Camera 1
    VideoCapture cap1(0); // open the default camera
    if(!cap1.isOpened()) {
        cout <<  "Can't find camera 1" << endl;
        return -1;
    }
    cap1.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    //declare video window
    namedWindow("Camera 1",2);

    // Get picture size
    Size imageSize;
    cap >> view;
    imageSize = view.size();
    // cout << to_string(imageSize.width) << endl;
    // cout << to_string(imageSize.height) << endl;

    // Read undistortion matrix and coefficients and calculate
    FileStorage fs(filename,FileStorage::READ);
    fs[config_camera_matrix] >> cameraMatrix;
    fs[config_distortion_coeff] >> distCoeffs;
    fs.release();

    fisheye::estimateNewCameraMatrixForUndistortRectify(cameraMatrix, distCoeffs, imageSize,
                                                               Matx33d::eye(), newCamMat, 1);
    fisheye::initUndistortRectifyMap(cameraMatrix, distCoeffs, Matx33d::eye(), newCamMat, imageSize,
                                             CV_16SC2, map1, map2);

    int x = 70;
    int y = 150;
    cv::Rect roi;
    roi.x = x;
    roi.y = y;

    Mat pano;
    namedWindow("Pano", 3);
    // stitcher.setWarper(new CylindricalWarper());
    // stitcher.setFeaturesFinder(new detail::SurfFeaturesFinder(300,3,4,3,4));
    // stitcher.setRegistrationResol(0.1);
    // stitcher.setSeamEstimationResol(0.1);
    // stitcher.setCompositingResol(1);
    // stitcher.setPanoConfidenceThresh(1);
    // stitcher.setWaveCorrection(true);
    // stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
    // stitcher.setFeaturesMatcher(new detail::BestOf2NearestMatcher(false,0.3));
    // stitcher.setBundleAdjuster(new detail::BundleAdjusterRay());

    Mat saved_edges, saved_edges1;
    Stitcher stitcher = Stitcher::createDefault(false); // create a Stitcher object

    // second part of sender pipeline
    // cv::VideoWriter writer;
    // writer.open("appsrc ! rtpvrawpay ! udpsink host=\"127.0.0.1\" port=\"5000\"", 0, fps, cv::Size(1920, 1080), true);

    // if (!writer.isOpened()) {
    //     printf("=ERR= can't create video writer\n");
    //     return -1;
    // }

        cap >> frame;
        cap1 >> frame1;
        if (frame.empty()) {
            edges = saved_edges;
        } else {
            remap(frame, edges, map1, map2, INTER_LINEAR);
            saved_edges = edges;
        }
        if (frame1.empty()) {
            edges1 = saved_edges1;
        } else {
            remap(frame1, edges1, map1, map2, INTER_LINEAR);
            saved_edges1 = edges1;
        }

        roi.width = edges.size().width - (x*2);
        roi.height = edges.size().height - (y*2);
        cv::Mat edges_cropped = edges(roi);
        cv::Mat edges_cropped1 = edges1(roi);

    // cout << roi.width << endl;
    // cout << roi.height << endl;

    vector < int > compression_params;
    vector < uchar > encoded;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);
    imencode(".jpg", edges_cropped1, encoded, compression_params);

    // cout << encoded.size();


    // int size = edges_cropped1.total()*edges_cropped1.elemSize();
    // cout << size;
    // encoded2 = reinterpret_cast<char*>(encoded1.data());

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("ipc:///zero/0");

    zmq::message_t request (encoded.data(), encoded.size());
    socket.send (request);

    //  Get the reply.
    zmq::message_t reply;
    socket.recv (&reply);

    // cout << reinterpret_cast<char*>(encoded1.data()) << endl;

   // int shmid;
   // // Give your shared memory an id, anything will do
   // key_t key = 123456;
   // unsigned char* shared_memory;
   // // Setup shared memory
   // if ((shmid = shmget(key, sizeof(edges_cropped1.data), IPC_CREAT | 0666)) < 0)
   // {
   //    printf("Error getting shared memory id");
   //    exit(1);
   // }
   // // Attached shared memory
   // if ((char *)shmat(shmid, NULL, 0) == (char *) -1)
   // {
   //    printf("Error attaching shared memory id");
   //    exit(1);
   // }
   // // Copy to shared memory
   // shared_memory = edges_cropped1.data;

    for(;;) {
        // Capture pic and crop
        cap >> frame;
        cap1 >> frame1;
        if (frame.empty()) {
            edges = saved_edges;
        } else {
            remap(frame, edges, map1, map2, INTER_LINEAR);
            saved_edges = edges;
        }
        if (frame1.empty()) {
            edges1 = saved_edges1;
        } else {
            remap(frame1, edges1, map1, map2, INTER_LINEAR);
            saved_edges1 = edges1;
        }

        roi.width = edges.size().width - (x*2);
        roi.height = edges.size().height - (y*2);
        cv::Mat edges_cropped = edges(roi);
        cv::Mat edges_cropped1 = edges1(roi);

        // shared_memory = edges_cropped1.data;

        // imencode(".jpg", edges_cropped1, encoded1);

        // cout << reinterpret_cast<char*>(encoded1.data());
                
        // /* Send camera 0 over socket */
        // vector < int > compression_params;
        // compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        // compression_params.push_back(jpegqual);
        // imencode(".jpg", edges_cropped, encoded, compression_params);
        // int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;
        // cout << "total pack: " << total_pack;
        // int ibuf[1];
        // ibuf[0] = total_pack;
        // sock.sendTo(ibuf, sizeof(int), servAddress, servPort0);

        // for (int i = 0; i < total_pack; i++)
        //     sock.sendTo( & encoded[i * PACK_SIZE], PACK_SIZE, servAddress, servPort0);

        // waitKey(FRAME_INTERVAL);

        // clock_t next_cycle = clock();
        // double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
        // cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;

        // cout << next_cycle - last_cycle;
        // last_cycle = next_cycle;

        // /* Send camera 1 over socket */
        // vector < int > compression_params1;
        // compression_params1.push_back(CV_IMWRITE_JPEG_QUALITY);
        // compression_params1.push_back(jpegqual);
        // imencode(".jpg", edges_cropped1, encoded1, compression_params1);
        // int total_pack1 = 1 + (encoded1.size() - 1) / PACK_SIZE;
        // int ibuf1[1];
        // ibuf1[0] = total_pack1;
        // sock.sendTo(ibuf1, sizeof(int), servAddress, servPort1);

        // for (int i = 0; i < total_pack1; i++)
        //     sock.sendTo( & encoded1[i * PACK_SIZE], PACK_SIZE, servAddress, servPort1);

        // waitKey(FRAME_INTERVAL);

        // cout << next_cycle - last_cycle;
        // last_cycle = next_cycle;

        // imshow("Camera 0", edges_cropped1);
        imencode(".jpg", edges_cropped1, encoded, compression_params);

        zmq::message_t request (encoded.data(), encoded.size());
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);

        // zmq::message_t request (encoded.data(), encoded.size());
        // socket.send (request);

        // //  Get the reply.
        // zmq::message_t reply;
        // socket.recv (&reply);


        // if (!edges1.empty()) {
        //     writer << edges1;
        // }
        cv::waitKey( 30 );

        // cout << buff;

        // vector<Mat> imgs;
        // imgs.push_back(edges_cropped);
        // imgs.push_back(edges_cropped1);
        // Stitcher::Status status = stitcher.stitch(imgs, pano); // stitch the input images together
        // if (status != Stitcher::OK) {
        //     cout << "Can't stitch images, error code = " << int(status) << endl;
        //     continue;
        // }
        // imshow("Pano", pano);

        if(waitKey(1) >= 0) break;
        }

    return 0;
}
