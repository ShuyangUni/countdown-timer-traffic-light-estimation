/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-18 22:25:29
 * @Description: 
 */
#pragma once

#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// #include "proto/hsmm_parameter.pb.h"
// #include "proto/proto_api.h"

#include "3rdparty/yaml-cpp/include/yaml-cpp/yaml.h"

namespace cttl {
namespace hsmm {
class HSMMParameter {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  /**
   * basic info
   */
  // system standard frequency
  double hz_;
  // system sampling interval
  double interval_;
  // Gaussian parameters
  double d_;
  double sigma_;
  // maximum jump times
  int max_n_;
  // distribution sampling resolution
  double res_;
  // cardinality of state space
  int n_state_;
  int n_obs_;
  int n_d_sample_;

  /**
   * matrix
   */
  // hyper-parameter of hamming distance to probabilistic space
  double alpha_;
  // observation matrix
  Eigen::MatrixXd mat_logb_c_;
  Eigen::MatrixXd mat_logb_v1_;
  Eigen::MatrixXd mat_logb_v2_;

  // attention: Eigen::SparseMatrix is ColMajor
  std::vector<Eigen::SparseMatrix<int>> mat_a_connections_;

  /**
   * distribution
   */
  std::string str_file_distribution_;
  Eigen::VectorXd range_distribution_;
  Eigen::MatrixXd distributions_;

  HSMMParameter();
  explicit HSMMParameter(const std::string &filepath_proto);

  void Display();
  bool IsValid();

 private:
  bool flag_valid;
  void GenerateBColor();
  void GenerateBValue();
  void GenerateAConnections();
  bool LoadDistributions();
  void InitBasicsFromCode();
  // void InitBasicsFromProto(const std::string &filepath_proto);
  void InitBasicsFromYAML(const std::string &filepath_yaml);
};

}  // namespace hsmm
}  // namespace cttl
