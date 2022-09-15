/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-15 13:41:11
 * @Description: 
 */
#include "include/hsmm/hsmm_parameter.h"

namespace cttl {
namespace hsmm {

HSMMParameter::HSMMParameter() {}

// HSMMParameter::HSMMParameter() {
//   InitBasicsFromCode();
//   GenerateBColor();
//   GenerateBValue();
//   GenerateAConnections();
//   flag_valid = true;
//   if (!LoadDistributions()) {
//     flag_valid = false;
//   }
// }

HSMMParameter::HSMMParameter(const std::string &filepath_proto) {
  InitBasicsFromProto(filepath_proto);
  GenerateBColor();
  GenerateBValue();
  GenerateAConnections();
  flag_valid = true;
  if (!LoadDistributions()) {
    flag_valid = false;
  }
}

void HSMMParameter::InitBasicsFromCode() {
  hz_ = 10.0;
  res_ = 0.01;
  d_ = 1.0;
  sigma_ = 0.1;
  max_n_ = 5;
  n_state_ = 300;
  n_obs_ = 484;
  alpha_ = 4;
  str_file_distribution_ =
      "/home/uni/Documents/_project/countdown-timer-traffic-light-estimation/"
      "countdown_timer_estimator/config/distribution.txt";

  interval_ = 1.0 / hz_;
  n_d_sample_ = ceil((d_ + 3 * sigma_) / interval_);
}

void HSMMParameter::InitBasicsFromProto(const std::string &filepath_proto) {
  std::cout << "load hsmm parameter from Protobuf..." << std::endl;
  std::cout << "proto file filepath: " << filepath_proto.c_str() << std::endl;

  HSMMParameterProto proto;
  GetProtoFromASCIIFile<HSMMParameterProto>(filepath_proto, &proto);
  hz_ = proto.hz();
  res_ = proto.res();
  d_ = proto.d();
  sigma_ = proto.sigma();
  max_n_ = proto.max_n();
  n_state_ = proto.n_state();
  n_obs_ = proto.n_obs();
  alpha_ = proto.alpha();
  str_file_distribution_ = proto.str_file_distribution();

  interval_ = 1.0 / hz_;
  n_d_sample_ = ceil((d_ + 3 * sigma_) / interval_);
}

void HSMMParameter::GenerateBColor() {
  // mat_logb_c
  Eigen::MatrixXd mat_b_c(3, 4);
  mat_b_c << 0.85, 0.05, 0.05, 0.05,  // NOLINT
      0.05, 0.85, 0.05, 0.05,         // NOLINT
      0.05, 0.05, 0.85, 0.05;         // NOLINT
  mat_logb_c_ = mat_b_c.array().log().eval();
}

void HSMMParameter::GenerateBValue() {
  // mat_logb_v1
  Eigen::MatrixXd mat_h(10, 11);
  mat_h << 0, 4, 3, 3, 4, 3, 2, 3, 1, 2, 6,  // NOLINT
      4, 0, 5, 3, 2, 5, 6, 1, 5, 4, 2,       // NOLINT
      3, 5, 0, 2, 5, 4, 3, 4, 2, 3, 5,       // NOLINT
      3, 3, 2, 0, 3, 2, 3, 2, 2, 1, 5,       // NOLINT
      4, 2, 5, 3, 0, 3, 4, 3, 3, 2, 4,       // NOLINT
      3, 5, 4, 2, 3, 0, 1, 4, 2, 1, 5,       // NOLINT
      2, 6, 3, 3, 4, 1, 0, 5, 1, 2, 6,       // NOLINT
      3, 1, 4, 2, 3, 4, 5, 0, 4, 3, 3,       // NOLINT
      1, 5, 2, 2, 3, 2, 1, 4, 0, 1, 7,       // NOLINT
      2, 4, 3, 1, 2, 1, 2, 3, 1, 0, 6;       // NOLINT
  mat_logb_v1_ = (-alpha_) * mat_h;
  mat_logb_v1_ = mat_logb_v1_.array().exp().eval();
  for (size_t i = 0; i < mat_logb_v1_.rows(); ++i) {
    mat_logb_v1_.row(i) /= mat_logb_v1_.row(i).sum();
  }
  mat_logb_v1_ = mat_logb_v1_.array().log().eval();

  // mat_logb_v2
  mat_h(0, 10) = 0;
  mat_logb_v2_ = (-alpha_) * mat_h;
  mat_logb_v2_ = mat_logb_v2_.array().exp().eval();
  for (size_t i = 0; i < mat_logb_v2_.rows(); ++i) {
    mat_logb_v2_.row(i) /= mat_logb_v2_.row(i).sum();
  }
  mat_logb_v2_ = mat_logb_v2_.array().log().eval();
}

void HSMMParameter::GenerateAConnections() {
  // 0-jump connection
  Eigen::MatrixXi mat_a_0 = Eigen::MatrixXi::Identity(n_state_, n_state_);
  // 0-jump connection
  Eigen::MatrixXi mat_a_1 = Eigen::MatrixXi::Zero(n_state_, n_state_);
  for (size_t i = 0; i < n_state_; ++i) {
    if (i == n_state_ - 1) {
      mat_a_1(i, 0) = 1;
    } else {
      mat_a_1(i, i + 1) = 1;
    }
  }

  // red -> green
  mat_a_1.block<1, 101>(98, 99) = Eigen::MatrixXi::Ones(1, 101);
  mat_a_1.block<1, 100>(99, 100) = Eigen::MatrixXi::Ones(1, 100);

  // green -> yellow, red
  mat_a_1.block<1, 101>(198, 199) = Eigen::MatrixXi::Ones(1, 101);
  mat_a_1.block<1, 100>(199, 200) = Eigen::MatrixXi::Ones(1, 100);
  mat_a_1(198, 299) = 1;
  mat_a_1.block<1, 100>(198, 0) = Eigen::MatrixXi::Ones(1, 100);
  mat_a_1.block<1, 100>(199, 0) = Eigen::MatrixXi::Ones(1, 100);

  // yellow -> red
  mat_a_1(298, 299) = 1;
  mat_a_1.block<1, 100>(298, 0) = Eigen::MatrixXi::Ones(1, 100);
  mat_a_1.block<1, 100>(299, 0) = Eigen::MatrixXi::Ones(1, 100);

  // n-jump connection
  mat_a_connections_.clear();
  Eigen::MatrixXi mat_a_n = mat_a_1;
  // we use transpose here to ensure the outer loop is for previous state.
  // Eigen::SparseMatrix is ColMajor
  for (size_t i = 0; i < max_n_ + 1; ++i) {
    if (i == 0) {
      mat_a_connections_.push_back(mat_a_0.transpose().sparseView());
    } else {
      mat_a_connections_.push_back(mat_a_n.transpose().sparseView());
      mat_a_n *= mat_a_1;
    }
  }
}

bool HSMMParameter::LoadDistributions() {
  std::ifstream ifs;
  ifs.open(str_file_distribution_.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cout
        << "[Error]: HSMMParameter::LoadDistributions(): failed to open file:"
        << str_file_distribution_.c_str() << std::endl;
    return false;
  }

  std::vector<std::vector<double>> data;
  std::string line;
  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    std::vector<double> tmp_vector;
    tmp_vector.clear();
    double tmp;
    while (ss >> tmp) {
      tmp_vector.push_back(tmp);
    }
    data.push_back(tmp_vector);
  }
  ifs.close();

  range_distribution_ = Eigen::VectorXd::Zero(data.size());
  distributions_ = Eigen::MatrixXd::Zero(data.size(), data.at(0).size() - 1);
  for (size_t i = 0; i < data.size(); ++i) {
    std::vector<double> tmp_vector = data.at(i);
    for (size_t j = 0; j < data.at(0).size(); ++j) {
      if (j == 0) {
        range_distribution_(i) = tmp_vector.at(j);
      } else {
        distributions_(i, j - 1) = tmp_vector.at(j);
      }
    }
  }

  return true;
}

bool HSMMParameter::IsValid() { return flag_valid; }

void HSMMParameter::Display() {
  std::cout << "--------------------------------------------------"
            << std::endl;
  std::cout << "Basic Parameters:" << std::endl;
  std::cout << "    hz_:" << hz_ << std::endl;
  std::cout << "    interval_:" << interval_ << std::endl;
  std::cout << "    res_:" << res_ << std::endl;
  std::cout << "    d_:" << d_ << std::endl;
  std::cout << "    sigma_:" << sigma_ << std::endl;
  std::cout << "    max_n_:" << max_n_ << std::endl;
  std::cout << "    n_state_:" << n_state_ << std::endl;
  std::cout << "    n_obs_:" << n_obs_ << std::endl;
  std::cout << "    n_d_sample_:" << n_d_sample_ << std::endl;
  std::cout << "    alpha_:" << alpha_ << std::endl;
  // std::cout << "    mat_logb_c_:" << std::endl;
  // std::cout << mat_logb_c_ << std::endl;
  // std::cout << "    mat_logb_v1_:" << std::endl;
  // std::cout << mat_logb_v1_ << std::endl;
  // std::cout << "    mat_logb_v2_:" << std::endl;
  // std::cout << mat_logb_v2_ << std::endl;
  // std::cout << "    mat_logb_v2_:" << std::endl;
  // std::cout << mat_logb_v2_ << std::endl;
  // std::cout << std::endl;
  // std::cout << mat_a_connections_.at(5).block<5, 5>(96, 0) << std::endl;
  // std::cout << range_distribution_.block<10, 1>(400, 0) << std::endl;
  // std::cout << distributions_.block<10, 6>(400, 0) << std::endl;
  std::cout << "--------------------------------------------------"
            << std::endl;
}

}  // namespace hsmm
}  // namespace cttl
