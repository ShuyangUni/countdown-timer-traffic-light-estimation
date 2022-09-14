// Copyright 2021.12.28 <Shuyang>
#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <chrono>  // NOLINT
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "include/common/enum_transformer.h"
#include "include/common/structure.h"
#include "include/hsmm/hsmm_parameter.h"

namespace cttl {
namespace hsmm {
class HSMMWorker {
  const double epsilon_ = 1e-6;

 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  explicit HSMMWorker(const HSMMParameter &param);

  bool Process(const common::Data &data, const double &drop_ratio,
               const int &drop_frames, common::Results *results);

  void EvaluateResults(const common::Results &results, const bool &bdisplay,
                       common::Evaluation *evaluation);

 private:
  std::shared_ptr<HSMMParameter> param_;
  int pair_size_;

  Eigen::MatrixXi pairs_;
  Eigen::VectorXd log_probs_;

  void InitPairs();
  void InitProbability();

  void CalculateB(const int &obz_c, const int &obz_v2, const int &obz_v1,
                  Eigen::VectorXd *log_vecb);
  void Iteration(const double &t_cur, const double &t_pre, const int &obz_c,
                 const int &obz_v2, const int &obz_v1);
  void CalculateA(const double &t_cur, const double &t_pre,
                  Eigen::MatrixXd *log_mata);
};
}  // namespace hsmm
}  // namespace cttl
