#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv_lib.hpp"
#include "svm.h"
#include <iostream>
#include <vector>

int main(void) {
  std::vector<data> samples;
  const auto kClass1DataNum = 100;
  const auto kClass2DataNum = 100;
  const auto kClass1Label = 1;
  const auto kClass2Label = -1;
  auto class1_x_generator = std::normal_distribution<double>(0.3, 0.2);
  auto class1_y_generator = std::normal_distribution<double>(0.3, 0.2);
  auto class2_x_generator = std::normal_distribution<double>(0.7, 0.2);
  auto class2_y_generator = std::normal_distribution<double>(0.7, 0.2);
  std::mt19937 eng(static_cast<unsigned int>(time(nullptr)));
  for (auto i = 0; i < kClass1DataNum; ++i) {
    samples.push_back(data(kClass1Label, class1_x_generator(eng), class1_y_generator(eng)));
  }
  for (auto i = 0; i < kClass2DataNum; ++i) {
    samples.push_back(data(kClass2Label, class2_x_generator(eng), class2_y_generator(eng)));
  }
  // svm 学習スタート
  svm_problem problem; // 学習データの構造体
  svm_node* problem_vector; // 
  problem.l = samples.size(); // 訓練データ数
  problem.y = new double[problem.l];
  for (auto i = 0; i < samples.size(); ++i) {
    problem.y[i] = samples[i].label_;
  }
  problem_vector = new svm_node[problem.l * (data::dimension + 1)]; // データ数 × (次元数 + 1) = 全次元数
  problem.x = new svm_node*[problem.l];
  for (auto i = 0; i < samples.size(); ++i) {
    problem.x[i] = problem_vector + i * 3; // コピーコンストラクタの発動？
    problem.x[i][0].index = 1;
    problem.x[i][0].value = samples[i].x_;
    problem.x[i][1].index = 2;
    problem.x[i][1].value = samples[i].y_;
    problem.x[i][2].index = -1;
    //problem.x[i][0].value = samples[i].x_;
  }
  svm_parameter param;
  param.svm_type = C_SVC;     // NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR
  param.kernel_type = RBF; // POLY, RBF, SIGMOID, PRECOMPUTED
  param.C = 8096;             // コスト：大きいほどハードマージン
  param.gamma = 1.1;          // POLY, RBF, SIGMOID で使われるパラメータ
  param.coef0 = 0;            // POLY, SIGMOID で使われるパラメータ
  param.cache_size = 100;     // カーネルキャッシュ？
  param.eps = 1e-3;           // 停止条件 readmeによると usually use 0.00001 in nu-SVC, 0.001 in others
  param.shrinking = 1;        // 1:shrinking が行われる， 0:otherwise
  param.probability = 0;      // 1:確率情報が付随したモデルとなる，0:otherwise
  param.degree = 3;           // POLY で使われるパラメータ
  param.nu = 0.5;             // nu-SVM, nu-SVR, one-class-SVM で使われるパラメータ

  // nr_weight, weight_label, weight は いくつかのクラスにペナルティを与えるパラメータ
  // unbalanced input をや 誤分類のコストに変化を付けたい場合に使う
  // readmeには for C-SVC と書いてある
  param.nr_weight = 0;        // weight_label の数
  param.weight_label = nullptr; // 重みつけるラベルの配列？
  param.weight = nullptr;     // 重み

  // 学習
  std::cout << "Ready to train ..." << std::endl;
  svm_model *model = svm_train(&problem, &param);
  std::cout << "Finished ..." << std::endl;

  // テスト
  int correct_count = 0;
  int wrong_count = 0;
  std::cout << "predict training samples ..." << std::endl;
  for (auto i = 0; i < samples.size(); ++i) {
    svm_node test[3];
    test[0].index = 1;
    test[0].value = samples[i].x_;
    test[1].index = 2;
    test[1].value = samples[i].y_;
    test[2].index = -1;
    // このテストデータ（ここでは学習データsamplesそのもの）
    const auto kPredictedLabel = static_cast<int>(svm_predict(model, test));
    // 分類結果の集計
    if (kPredictedLabel == samples[i].label_) {
      ++correct_count;
    }
    else {
      ++wrong_count;
    }
  }
  std::cout << "done" << std::endl;
  std::cout << "RESULT : correct = " << correct_count << ": wrong = " << wrong_count << std::endl;
  std::cout << "Accuracy[%] = " << (static_cast<double>(correct_count)
                                    / static_cast<double>(correct_count + wrong_count)*100.0) << std::endl;
  // OPENCVによる表示（おまけ
  const auto kHeight = 640;
  const auto kWidth = 640;
  cv::Mat img(kHeight, kWidth, CV_8UC3);
  img = cv::Scalar(255, 255, 255); // 白でぬりつぶし
  std::cout << "Rendering Result ..." << std::endl;
  // 画像の作成
  for (auto y = 0; y < kHeight; ++y) {
    for (auto x = 0; x < kWidth; ++x) {
      svm_node test[3];
      test[0].index = 1;
      test[0].value = static_cast<double>(x) / static_cast<double>(kWidth);
      test[1].index = 2;
      test[1].value = static_cast<double>(y) / static_cast<double>(kHeight);
      test[2].index = -1;
      const auto kPredictedLabel = static_cast<int>(svm_predict(model, test));
      if (kPredictedLabel == kClass1Label) {
        img.at<cv::Vec3b>(y, x) = cv::Vec3b(128, 128, 255);
      }
      else {
        img.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 128, 128);
      }
    }
  }
  std::cout << "Rendering background done ..." << std::endl;
  const auto kClass1Color = cv::Scalar(0, 0, 255);
  const auto kClass2Color = cv::Scalar(255, 0, 0);
  for (auto i = 0; i < samples.size(); ++i) {
    const auto kColor = (samples[i].label_ == kClass1Label ? kClass1Color : kClass2Color);
    cv::circle(img, cv::Point(samples[i].x_*kWidth, samples[i].y_*kHeight), 2, kColor, -1);
  }
  std::cout << "Rendering Sample data done ..." << std::endl;
  const auto kSupportVectorNum = svm_get_nr_sv(model);
  int * sv_indices = new int[kSupportVectorNum];
  svm_get_sv_indices(model, sv_indices);
  for (auto i = 0; i < kSupportVectorNum; ++i) {
    const auto kSampleIdx = sv_indices[i] - 1;
    const auto kColor = (samples[kSampleIdx].label_ == kClass1Label ? kClass1Color : kClass2Color);
    cv::circle(img, cv::Point(samples[kSampleIdx].x_*kWidth, samples[kSampleIdx].y_*kHeight), 4, kColor, -1);
  }
  std::cout << "Rendering support vectors done ..." << std::endl;
  // 表示
  cv::imshow("result", img);
  cv::waitKey();

  svm_free_and_destroy_model(&model);
  delete[] problem.x;
  delete[] problem.y;
  delete[] problem_vector;

  return 0;
}
