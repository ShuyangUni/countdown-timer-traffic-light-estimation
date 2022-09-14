// Copyright 2021.12.28 <Shuyang>
#pragma once

#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  void Display();
  bool IsValid();

 private:
  bool flag_valid;
  void GenerateBColor();
  void GenerateBValue();
  void GenerateAConnections();
  bool LoadDistributions();
  void InitBasics();
};

}  // namespace hsmm
}  // namespace cttl
