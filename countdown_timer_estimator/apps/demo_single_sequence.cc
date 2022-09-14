/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-14 23:36:51
 * @Description: 
 */
#include <chrono>  // NOLINT
#include <iostream>
#include <string>

#include "include/common/data_loader.h"
#include "include/hsmm/hsmm_parameter.h"
#include "include/hsmm/hsmm_worker.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "[Error]: main(): input parameters is incorrect." << std::endl;
    std::cout << "[Info] : main(): ./demo_single_sequence [folders] "
              << std::endl;
    return 0;
  }

  // init
  cttl::hsmm::HSMMParameter hsmm_parameter;
  // hsmm_parameter.Display();
  cttl::hsmm::HSMMWorker hsmm_worker(hsmm_parameter);

  cttl::common::DataLoader data_loader;
  cttl::common::Results results;
  cttl::common::Evaluation evaluation;

  for (size_t i = 1; i < argc; ++i) {
    std::string str_folder_test = argv[i];
    std::cout << "[Info]: main(): processing..." << str_folder_test.c_str()
              << std::endl;
    cttl::common::Data data_sequence;
    data_loader.LoadData(str_folder_test, &data_sequence);
    // data_loader.Display(data_sequence);
    hsmm_worker.Process(data_sequence, 0.0, 0, &results);
  }

  hsmm_worker.EvaluateResults(results, true, &evaluation);

  return 0;
}
