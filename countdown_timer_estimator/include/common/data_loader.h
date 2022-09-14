// Copyright 2021.12.28 <Shuyang>
#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/common/enum_transformer.h"
#include "include/common/structure.h"

namespace cttl {
namespace common {
class DataLoader {
 public:
  bool LoadData(const std::string &str_folderpath, Data *data_sequence);
  static void Display(const Data &data_sequence);

 private:
  bool LoadGroundTruth(const std::string &str_filepath, Data *data_sequence);
  bool LoadObservation(const std::string &str_filepath, Data *data_sequence);
  bool LoadTimestamp(const std::string &str_filepath, Data *data_sequence);
  bool DataCheck(const Data &data_sequence);
};
}  // namespace common
}  // namespace cttl
