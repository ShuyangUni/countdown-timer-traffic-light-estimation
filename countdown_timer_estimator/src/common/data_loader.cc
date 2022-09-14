/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-14 23:38:46
 * @Description: 
 */
#include "include/common/data_loader.h"

namespace cttl {
namespace common {

bool DataLoader::LoadData(const std::string &str_folderpath,
                          Data *data_sequence) {
  std::string str_file_gt = str_folderpath + "/gt.txt";
  std::string str_file_observation = str_folderpath + "/classification.txt";
  std::string str_file_timestamp = str_folderpath + "/timestamp.txt";

  data_sequence->folderpath = str_folderpath;
  if (!LoadGroundTruth(str_file_gt, data_sequence)) {
    return false;
  }
  if (!LoadObservation(str_file_observation, data_sequence)) {
    return false;
  }
  if (!LoadTimestamp(str_file_timestamp, data_sequence)) {
    return false;
  }
  if (!DataCheck(*data_sequence)) {
    return false;
  }

  return true;
}

bool DataLoader::LoadGroundTruth(const std::string &str_filepath,
                                 Data *data_sequence) {
  data_sequence->groundtruths.clear();

  std::ifstream ifs;
  ifs.open(str_filepath.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "[Error]: DataLoader::LoadGroundTruth(): failed to open file:"
              << str_filepath.c_str() << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    int seq_id;
    int color;
    int value;
    std::stringstream ss(line);
    ss >> seq_id >> color >> value;

    State state;
    if (!EnumTransformer::GetState(color, value, &state)) {
      return false;
    }
    data_sequence->groundtruths.push_back(state);
  }
  ifs.close();
  data_sequence->volumn = data_sequence->groundtruths.size();
  return true;
}

bool DataLoader::LoadObservation(const std::string &str_filepath,
                                 Data *data_sequence) {
  data_sequence->observations.clear();

  std::ifstream ifs;
  ifs.open(str_filepath.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "[Error]: DataLoader::LoadObservation(): failed to open file:"
              << str_filepath.c_str() << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    int seq_id;
    int color;
    int value_tens;
    int value_ones;
    std::stringstream ss(line);
    ss >> seq_id >> color >> value_tens >> value_ones;

    Observation obs;
    if (!EnumTransformer::GetObservation(color, value_tens, value_ones, &obs)) {
      return false;
    }
    data_sequence->observations.push_back(obs);
  }
  ifs.close();
  data_sequence->volumn = data_sequence->observations.size();
  return true;
}

bool DataLoader::LoadTimestamp(const std::string &str_filepath,
                               Data *data_sequence) {
  data_sequence->timestamps.clear();
  data_sequence->sequences.clear();

  std::ifstream ifs;
  ifs.open(str_filepath.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "[Error]: DataLoader::LoadTimestamp(): failed to open file:"
              << str_filepath.c_str() << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    int seq_id;
    double timestamp;
    std::stringstream ss(line);
    ss >> seq_id >> timestamp;
    data_sequence->timestamps.push_back(timestamp);
    data_sequence->sequences.push_back(seq_id);
  }
  ifs.close();
  data_sequence->volumn = data_sequence->timestamps.size();
  return true;
}

bool DataLoader::DataCheck(const Data &data_sequence) {
  if (data_sequence.sequences.size() != data_sequence.volumn) {
    std::cout << "[Error]: DataLoader::DataCheck(): inequal size: "
                 "data_sequence.volumn: "
              << data_sequence.volumn << " data_sequence.sequences.size(): "
              << data_sequence.sequences.size() << std::endl;
    return false;
  }
  if (data_sequence.timestamps.size() != data_sequence.volumn) {
    std::cout << "[Error]: DataLoader::DataCheck(): inequal size: "
                 "data_sequence.volumn: "
              << data_sequence.volumn << " data_sequence.timestamps.size(): "
              << data_sequence.timestamps.size() << std::endl;
    return false;
  }
  if (data_sequence.groundtruths.size() != data_sequence.volumn) {
    std::cout << "[Error]: DataLoader::DataCheck(): inequal size: "
                 "data_sequence.volumn: "
              << data_sequence.volumn << " data_sequence.groundtruths.size(): "
              << data_sequence.groundtruths.size() << std::endl;
    return false;
  }
  if (data_sequence.observations.size() != data_sequence.volumn) {
    std::cout << "[Error]: DataLoader::DataCheck(): inequal size: "
                 "data_sequence.volumn: "
              << data_sequence.volumn << " data_sequence.observations.size(): "
              << data_sequence.observations.size() << std::endl;
    return false;
  }
  return true;
}

void DataLoader::Display(const Data &data_sequence) {
  std::cout << "--------------------------------------------------"
            << std::endl;
  std::cout << "Basic Info:" << std::endl;
  std::cout << "    Folder Path: " << data_sequence.folderpath.c_str()
            << std::endl;
  std::cout << "    Sequence Lenght: " << data_sequence.volumn << std::endl;
  std::cout << "--------------------------------------------------"
            << std::endl;
  std::cout << "Data:" << std::endl;
  for (size_t i = 0; i < data_sequence.sequences.size(); ++i) {
    printf(
        "    %5d, %.3f, gt: <%7s, %2s, %2s >, obz: <%7s, %2s, %2s >\n",
        data_sequence.sequences.at(i), data_sequence.timestamps.at(i),
        EnumTransformer::Enum2StrColorState(data_sequence.groundtruths.at(i).c)
            .c_str(),
        EnumTransformer::Enum2StrValueState(
            data_sequence.groundtruths.at(i).v_tens)
            .c_str(),
        EnumTransformer::Enum2StrValueState(
            data_sequence.groundtruths.at(i).v_ones)
            .c_str(),
        EnumTransformer::Enum2StrColorObservation(
            data_sequence.observations.at(i).c)
            .c_str(),
        EnumTransformer::Enum2StrValueObservation(
            data_sequence.observations.at(i).v_tens)
            .c_str(),
        EnumTransformer::Enum2StrValueObservation(
            data_sequence.observations.at(i).v_ones)
            .c_str());
  }
  std::cout << "--------------------------------------------------"
            << std::endl;
}

}  // namespace common
}  // namespace cttl
