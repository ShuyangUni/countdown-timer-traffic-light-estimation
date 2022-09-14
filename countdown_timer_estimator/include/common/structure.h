// Copyright 2021.12.28 <Shuyang>
#pragma once

#include <Eigen/Dense>
#include <string>
#include <vector>

#include "include/common/enum.h"

namespace cttl {
namespace common {

struct Observation {
  ColorObservation c;
  ValueObservation v_tens;
  ValueObservation v_ones;
};

struct State {
  ColorState c;
  ValueState v_tens;
  ValueState v_ones;
};

struct Result {
  State best_state;
  int best_d_sample;
  // std::vector<double> probs;

  // std::vector<State> best_n_states;
  // std::vector<double> best_n_probs;
};

struct Evaluation {
  Evaluation() {
    est_n_digits = Eigen::VectorXi::Zero(10);
    est_n_colors = Eigen::VectorXi::Zero(3);
    est_confusion_digit = Eigen::MatrixXi::Zero(10, 10);
    est_confusion_color = Eigen::MatrixXi::Zero(3, 3);

    obz_n_digits = Eigen::VectorXi::Zero(10);
    obz_n_colors = Eigen::VectorXi::Zero(3);
    obz_confusion_digit = Eigen::MatrixXi::Zero(10, 10);
    obz_confusion_color = Eigen::MatrixXi::Zero(3, 3);
  }

  // num of frames
  int n_frames = 0;
  int n_key = 0;
  // estimation
  int est_n_pos = 0;
  int est_n_color_pos = 0;
  int est_n_value_pos = 0;
  int est_n_key_pos = 0;
  int est_n_key_color_pos = 0;
  int est_n_key_value_pos = 0;
  double est_r_pos = 0;
  double est_r_color_pos = 0;
  double est_r_value_pos = 0;
  double est_r_key_pos = 0;
  double est_r_key_color_pos = 0;
  double est_r_key_value_pos = 0;
  Eigen::VectorXi est_n_digits;
  Eigen::VectorXi est_n_colors;
  Eigen::MatrixXi est_confusion_digit;
  Eigen::MatrixXi est_confusion_color;
  // observation
  int obz_n_pos = 0;
  int obz_n_color_pos = 0;
  int obz_n_value_pos = 0;
  int obz_n_key_pos = 0;
  int obz_n_key_color_pos = 0;
  int obz_n_key_value_pos = 0;
  double obz_r_pos = 0;
  double obz_r_color_pos = 0;
  double obz_r_value_pos = 0;
  double obz_r_key_pos = 0;
  double obz_r_key_color_pos = 0;
  double obz_r_key_value_pos = 0;
  Eigen::VectorXi obz_n_digits;
  Eigen::VectorXi obz_n_colors;
  Eigen::MatrixXi obz_confusion_digit;
  Eigen::MatrixXi obz_confusion_color;
};

struct Data {
  std::string folderpath;
  int volumn;
  std::vector<int> sequences;
  std::vector<double> timestamps;
  std::vector<Observation> observations;
  std::vector<State> groundtruths;
};

struct Results {
  int volumn;
  std::vector<int> sequences;
  std::vector<double> timestamps;
  std::vector<Observation> observations;
  std::vector<State> groundtruths;
  std::vector<Result> results;

  Results() {
    volumn = 0;
    sequences.clear();
    timestamps.clear();
    observations.clear();
    groundtruths.clear();
    results.clear();
  }
};

}  // namespace common
}  // namespace cttl
