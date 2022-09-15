/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-14 23:39:35
 * @Description: 
 */
#include "include/hsmm/hsmm_worker.h"

#ifdef USE_OPENMP
#include <omp.h>
#endif

namespace cttl {
namespace hsmm {
HSMMWorker::HSMMWorker(const HSMMParameter &param) {
  param_.reset(new HSMMParameter());
  *param_ = param;
  pair_size_ = param_->n_d_sample_ * param_->n_state_;

#ifdef USE_OPENMP
  omp_set_num_threads(1);
#endif
}

bool HSMMWorker::Process(const common::Data &data, const double &drop_ratio,
                         const int &drop_frames, common::Results *results) {
  // system init
  InitPairs();
  InitProbability();

  int start_i = rand() % data.observations.size();  // NOLINT
  if (start_i == 0) {
    start_i = 1;
  }
  int end_i = start_i + drop_frames;

  // loop
  common::Result result;
  double t_cur, t_pre;
  for (size_t i = 0; i < data.observations.size(); ++i) {
    if (i != 0) {
      double r = (static_cast<double>(rand()) / (RAND_MAX));  // NOLINT
      if (r < drop_ratio) {
        continue;
      }
    }

    if (i >= start_i && i < end_i) {
      continue;
    }

    auto t_s = std::chrono::high_resolution_clock::now();
    cttl::common::Observation obz = data.observations.at(i);
    t_cur = data.timestamps.at(i);
    int obz_c = obz.c;
    int obz_v2 = obz.v_tens;
    int obz_v1 = obz.v_ones;

    // initial frame
    if (i == 0) {
      Eigen::VectorXd log_vecb;
      CalculateB(obz_c, obz_v2, obz_v1, &log_vecb);
      log_probs_ += log_vecb;

    } else {
      // other frames
      Iteration(t_cur, t_pre, obz_c, obz_v2, obz_v1);
    }

    // update results
    results->volumn++;
    results->timestamps.push_back(data.timestamps.at(i));
    results->sequences.push_back(data.sequences.at(i));
    results->observations.push_back(data.observations.at(i));
    results->groundtruths.push_back(data.groundtruths.at(i));

    int idx_max = 0;
    log_probs_.maxCoeff(&idx_max);
    result.best_state.c = (common::ColorState)pairs_(idx_max, 0);
    result.best_state.v_tens = (common::ValueState)pairs_(idx_max, 1);
    result.best_state.v_ones = (common::ValueState)pairs_(idx_max, 2);
    result.best_d_sample = pairs_(idx_max, 3);
    results->results.push_back(result);
    t_pre = t_cur;

    auto t_e = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t_e - t_s);
    double millseconds = static_cast<double>(duration.count()) / 1000.0;

    // display
    printf(
        "seq: %6d, comsumption: %.3fms, gt: <%7s, %2s, %2s >, obz: <%7s, %2s, "
        "%2s >, result: <%7s, "
        "%2s, %2s >, %d\n",
        data.sequences.at(i), millseconds,
        common::EnumTransformer::Enum2StrColorState(data.groundtruths.at(i).c)
            .c_str(),
        common::EnumTransformer::Enum2StrValueState(
            data.groundtruths.at(i).v_tens)
            .c_str(),
        common::EnumTransformer::Enum2StrValueState(
            data.groundtruths.at(i).v_ones)
            .c_str(),
        common::EnumTransformer::Enum2StrColorObservation(
            data.observations.at(i).c)
            .c_str(),
        common::EnumTransformer::Enum2StrValueObservation(
            data.observations.at(i).v_tens)
            .c_str(),
        common::EnumTransformer::Enum2StrValueObservation(
            data.observations.at(i).v_ones)
            .c_str(),
        common::EnumTransformer::Enum2StrColorState(result.best_state.c)
            .c_str(),
        common::EnumTransformer::Enum2StrValueState(result.best_state.v_tens)
            .c_str(),
        common::EnumTransformer::Enum2StrValueState(result.best_state.v_ones)
            .c_str(),
        result.best_d_sample);
  }
  return true;
}

void HSMMWorker::CalculateB(const int &obz_c, const int &obz_v2,
                            const int &obz_v1, Eigen::VectorXd *log_vecb) {
  *log_vecb = Eigen::VectorXd::Zero(pair_size_);
  for (size_t i = 0; i < pair_size_; ++i) {
    int state_c = pairs_(i, 0);
    int state_v2 = pairs_(i, 1);
    int state_v1 = pairs_(i, 2);

    (*log_vecb)(i) += param_->mat_logb_c_(state_c, obz_c);
    (*log_vecb)(i) += param_->mat_logb_v2_(state_v2, obz_v2);
    (*log_vecb)(i) += param_->mat_logb_v1_(state_v1, obz_v1);
  }
}

void HSMMWorker::CalculateA(const double &t_cur, const double &t_pre,
                            Eigen::MatrixXd *log_mata) {
  double dt = t_cur - t_pre;
  *log_mata = -std::numeric_limits<double>::infinity() *
              Eigen::MatrixXd::Ones(pair_size_, pair_size_);

  size_t state_size = param_->n_state_;
  size_t idx_state_cur = 0;
  size_t idx_pair_cur = 0;
  double d_gap_max = 0.0;
  double d_gap_min = 0.0;
  int idx_max = 0;
  int idx_min = 0;
  double prob = 0.0;

  double range_min = param_->range_distribution_(0);
  double range_max =
      param_->range_distribution_(param_->range_distribution_.size() - 1);

#ifdef USE_OPENMP
#pragma omp parallel
  {
#pragma omp for
#endif
    for (size_t idx_pair_pre = 0; idx_pair_pre < pair_size_; ++idx_pair_pre) {
      // for each row
      Eigen::VectorXd value = Eigen::VectorXd::Zero(pair_size_);
      size_t idx_state_pre = idx_pair_pre % param_->n_state_;
      for (size_t idx_jump = 0; idx_jump < param_->mat_a_connections_.size();
           ++idx_jump) {
        // for each jump
        for (Eigen::SparseMatrix<int>::InnerIterator it(
                 param_->mat_a_connections_.at(idx_jump), idx_state_pre);
             it; ++it) {
          idx_state_cur = it.row();
          // connected
          for (size_t idx_d = 0; idx_d < param_->n_d_sample_; ++idx_d) {
            // for different d_sample
            idx_pair_cur = idx_state_cur + idx_d * state_size;
            d_gap_max =
                dt + (pairs_(idx_pair_pre, 3) - pairs_(idx_pair_cur, 3)) *
                         param_->interval_;
            d_gap_min = d_gap_max - param_->interval_;

            if (d_gap_min >= range_min && d_gap_max <= range_max) {
              idx_max =
                  static_cast<int>((d_gap_max - range_min) / param_->res_);
              idx_min =
                  static_cast<int>((d_gap_min - range_min) / param_->res_);
              prob = param_->distributions_.col(idx_jump)(idx_max) -
                     param_->distributions_.col(idx_jump)(idx_min);
              if (prob > value(idx_pair_cur)) {
                value(idx_pair_cur) = prob;
              }
            }
          }  // end of idx_d
        }    // end of it
      }      // end of idx_jump
      double sum_value = value.sum();
      for (size_t i = 0; i < pair_size_; ++i) {
        if (value(i) > epsilon_) {
          (*log_mata)(idx_pair_pre, i) = log(value(i) / sum_value);
        }
      }
    }  // end of idx_pair_pre
#ifdef USE_OPENMP
  }
#endif
}

void HSMMWorker::Iteration(const double &t_cur, const double &t_pre,
                           const int &obz_c, const int &obz_v2,
                           const int &obz_v1) {
  Eigen::VectorXd log_vecb;
  CalculateB(obz_c, obz_v2, obz_v1, &log_vecb);

  Eigen::MatrixXd log_mata;
  CalculateA(t_cur, t_pre, &log_mata);

  Eigen::VectorXd tmp_log_probs = Eigen::VectorXd::Zero(pair_size_);
  for (size_t i = 0; i < tmp_log_probs.size(); ++i) {
    Eigen::VectorXd tmp_logp = log_probs_ + log_mata.col(i);
    double max_logp = tmp_logp.maxCoeff();
    tmp_log_probs(i) = max_logp + log_vecb(i);
  }
  log_probs_ = tmp_log_probs;
}

void HSMMWorker::InitPairs() {
  pairs_ = Eigen::MatrixXi::Zero(pair_size_, 4);
  size_t count = 0;
  for (int d = 0; d < param_->n_d_sample_; ++d) {
    for (int c = 0; c < 3; ++c) {
      for (int v2 = 9; v2 >= 0; --v2) {
        for (int v1 = 9; v1 >= 0; --v1) {
          pairs_(count, 0) = c;
          pairs_(count, 1) = v2;
          pairs_(count, 2) = v1;
          pairs_(count, 3) = d + 1;
          ++count;
        }
      }
    }
  }
}

void HSMMWorker::InitProbability() {
  log_probs_ = Eigen::VectorXd::Ones(pair_size_);
  log_probs_ /= log_probs_.sum();
  log_probs_ = log_probs_.array().log().eval();
}

void HSMMWorker::EvaluateResults(const common::Results &results,
                                 const bool &bdisplay,
                                 common::Evaluation *evaluation) {
  for (size_t i = 0; i < results.volumn; ++i) {
    // data
    int gt_c = results.groundtruths.at(i).c;
    int gt_v2 = results.groundtruths.at(i).v_tens;
    int gt_v1 = results.groundtruths.at(i).v_ones;
    int obz_c = results.observations.at(i).c;
    int obz_v2 = results.observations.at(i).v_tens;
    int obz_v1 = results.observations.at(i).v_ones;
    int est_c = results.results.at(i).best_state.c;
    int est_v2 = results.results.at(i).best_state.v_tens;
    int est_v1 = results.results.at(i).best_state.v_ones;

    evaluation->n_frames++;
    // observation
    if (obz_c == gt_c) {
      evaluation->obz_n_color_pos++;
    }
    if (obz_v1 == gt_v1 && obz_v2 == gt_v2) {
      evaluation->obz_n_value_pos++;
    }
    if (obz_v1 == gt_v1 && obz_v2 == 10 && gt_v2 == 0) {
      evaluation->obz_n_value_pos++;
    }
    if (obz_c == gt_c && obz_v1 == gt_v1 && obz_v2 == gt_v2) {
      evaluation->obz_n_pos++;
    }
    if (obz_c == gt_c && obz_v1 == gt_v1 && obz_v2 == 10 && gt_v2 == 0) {
      evaluation->obz_n_pos++;
    }
    // estimation
    if (est_c == gt_c) {
      evaluation->est_n_color_pos++;
    }
    if (est_v1 == gt_v1 && est_v2 == gt_v2) {
      evaluation->est_n_value_pos++;
    }
    if (est_c == gt_c && est_v1 == gt_v1 && est_v2 == gt_v2) {
      evaluation->est_n_pos++;
    }

    // confusion matrix
    // obz
    if (obz_c != 3) {
      evaluation->obz_n_colors(gt_c)++;
      evaluation->obz_confusion_color(gt_c, obz_c)++;
    }
    if (obz_v1 != 10) {
      evaluation->obz_n_digits(gt_v1)++;
      evaluation->obz_confusion_digit(gt_v1, obz_v1)++;
    }
    if (obz_v2 != 10) {
      evaluation->obz_n_digits(gt_v2)++;
      evaluation->obz_confusion_digit(gt_v2, obz_v2)++;
    } else {
      evaluation->obz_n_digits(gt_v2)++;
      evaluation->obz_confusion_digit(gt_v2, 0)++;
    }

    // est
    if (est_c != 3) {
      evaluation->est_n_colors(gt_c)++;
      evaluation->est_confusion_color(gt_c, est_c)++;
    }
    if (est_v1 != 10) {
      evaluation->est_n_digits(gt_v1)++;
      evaluation->est_confusion_digit(gt_v1, est_v1)++;
    }
    if (est_v2 != 10) {
      evaluation->est_n_digits(gt_v2)++;
      evaluation->est_confusion_digit(gt_v2, est_v2)++;
    } else {
      evaluation->est_n_digits(gt_v2)++;
      evaluation->est_confusion_digit(gt_v2, 0)++;
    }

    // key
    if (gt_v2 == 0 && gt_v1 <= 5) {
      evaluation->n_key++;
      if (obz_c == gt_c) {
        evaluation->obz_n_key_color_pos++;
      }
      if (obz_v1 == gt_v1 && obz_v2 == gt_v2) {
        evaluation->obz_n_key_value_pos++;
      }
      if (obz_v1 == gt_v1 && obz_v2 == 10 && gt_v2 == 0) {
        evaluation->obz_n_key_value_pos++;
      }
      if (obz_c == gt_c && obz_v1 == gt_v1 && obz_v2 == gt_v2) {
        evaluation->obz_n_key_pos++;
      }
      if (obz_c == gt_c && obz_v1 == gt_v1 && obz_v2 == 10 && gt_v2 == 0) {
        evaluation->obz_n_key_pos++;
      }
      if (est_c == gt_c) {
        evaluation->est_n_key_color_pos++;
      }
      if (est_v1 == gt_v1 && est_v2 == gt_v2) {
        evaluation->est_n_key_value_pos++;
      }
      if (est_c == gt_c && est_v1 == gt_v1 && est_v2 == gt_v2) {
        evaluation->est_n_key_pos++;
      }
    }
  }

  evaluation->obz_r_color_pos =
      static_cast<double>(evaluation->obz_n_color_pos) /
      static_cast<double>(evaluation->n_frames);
  evaluation->obz_r_value_pos =
      static_cast<double>(evaluation->obz_n_value_pos) /
      static_cast<double>(evaluation->n_frames);
  evaluation->obz_r_pos = static_cast<double>(evaluation->obz_n_pos) /
                          static_cast<double>(evaluation->n_frames);
  evaluation->obz_r_key_color_pos =
      static_cast<double>(evaluation->obz_n_key_color_pos) /
      static_cast<double>(evaluation->n_key);
  evaluation->obz_r_key_value_pos =
      static_cast<double>(evaluation->obz_n_key_value_pos) /
      static_cast<double>(evaluation->n_key);
  evaluation->obz_r_key_pos = static_cast<double>(evaluation->obz_n_key_pos) /
                              static_cast<double>(evaluation->n_key);

  evaluation->est_r_color_pos =
      static_cast<double>(evaluation->est_n_color_pos) /
      static_cast<double>(evaluation->n_frames);
  evaluation->est_r_value_pos =
      static_cast<double>(evaluation->est_n_value_pos) /
      static_cast<double>(evaluation->n_frames);
  evaluation->est_r_pos = static_cast<double>(evaluation->est_n_pos) /
                          static_cast<double>(evaluation->n_frames);
  evaluation->est_r_key_color_pos =
      static_cast<double>(evaluation->est_n_key_color_pos) /
      static_cast<double>(evaluation->n_key);
  evaluation->est_r_key_value_pos =
      static_cast<double>(evaluation->est_n_key_value_pos) /
      static_cast<double>(evaluation->n_key);
  evaluation->est_r_key_pos = static_cast<double>(evaluation->est_n_key_pos) /
                              static_cast<double>(evaluation->n_key);

  if (bdisplay) {
    std::cout << "--------------------------------------------------"
              << std::endl;
    std::cout << "Total sequence number: " << evaluation->n_frames << std::endl;
    std::cout << "Classification:" << std::endl;
    printf("    color: %d/%.3f, value: %d/%.3f, total: %d/%.3f.\n",
           evaluation->obz_n_color_pos, evaluation->obz_r_color_pos,
           evaluation->obz_n_value_pos, evaluation->obz_r_value_pos,
           evaluation->obz_n_pos, evaluation->obz_r_pos);
    printf("    color: %d/%.3f, value: %d/%.3f, total: %d/%.3f.\n",
           evaluation->obz_n_key_color_pos, evaluation->obz_r_key_color_pos,
           evaluation->obz_n_key_value_pos, evaluation->obz_r_key_value_pos,
           evaluation->obz_n_key_pos, evaluation->obz_r_key_pos);

    std::cout << "Estimation:" << std::endl;
    printf("    color: %d/%.3f, value: %d/%.3f, total: %d/%.3f.\n",
           evaluation->est_n_color_pos, evaluation->est_r_color_pos,
           evaluation->est_n_value_pos, evaluation->est_r_value_pos,
           evaluation->est_n_pos, evaluation->est_r_pos);
    printf("    color: %d/%.3f, value: %d/%.3f, total: %d/%.3f.\n",
           evaluation->est_n_key_color_pos, evaluation->est_r_key_color_pos,
           evaluation->est_n_key_value_pos, evaluation->est_r_key_value_pos,
           evaluation->est_n_key_pos, evaluation->est_r_key_pos);

    std::cout << "Color input counting per class:" << std::endl;
    std::cout << evaluation->obz_n_colors.transpose() << std::endl;
    std::cout << "Confusion matrix of color input:" << std::endl;
    std::cout << evaluation->obz_confusion_color << std::endl;
    std::cout << "Digit input counting per class:" << std::endl;
    std::cout << evaluation->obz_n_digits.transpose() << std::endl;
    std::cout << "Confusion matrix of digit input:" << std::endl;
    std::cout << evaluation->obz_confusion_digit << std::endl;
    std::cout << "Color output counting per class:" << std::endl;
    std::cout << evaluation->est_n_colors.transpose() << std::endl;
    std::cout << "Confusion matrix of color output:" << std::endl;
    std::cout << evaluation->est_confusion_color << std::endl;
    std::cout << "Digit output counting per class:" << std::endl;
    std::cout << evaluation->est_n_digits.transpose() << std::endl;
    std::cout << "Confusion matrix of digit output:" << std::endl;
    std::cout << evaluation->est_confusion_digit << std::endl;
    std::cout << "--------------------------------------------------"
              << std::endl;
  }
}

}  // namespace hsmm
}  // namespace cttl
