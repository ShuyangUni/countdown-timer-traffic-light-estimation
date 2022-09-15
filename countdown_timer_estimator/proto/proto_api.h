/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-15 12:18:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-15 13:29:51
 * @Description: 
 */
// Copyright [2019] <Chengjie>
#pragma once

#include <fcntl.h>  // file descriptor
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

using google::protobuf::TextFormat;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::ZeroCopyInputStream;

template <typename MessageType>
static bool GetProtoFromASCIIFile(const std::string &file_name,
                                  MessageType *message) {
  int file_descriptor = open(file_name.c_str(), O_RDONLY);
  if (file_descriptor < 0) {
    std::cerr << "Failed to open file " << file_name << " in text mode.";
    // Failed to open;
    return false;
  }

  ZeroCopyInputStream *input = new FileInputStream(file_descriptor);
  bool success = TextFormat::Parse(input, message);
  if (!success) {
    std::cerr << "Failed to parse file " << file_name << " as text proto.";
  }
  delete input;
  close(file_descriptor);
  return success;
}

/**
 * @brief: write proto config file
 * @param: path and proto2 message type
 */
template <typename MessageType>
static bool SetProtoToASCIIFile(const MessageType &message,
                                const std::string &file_name) {
  int fd = open(file_name.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  if (fd < 0) {
    std::cerr << "Unable to open file " << file_name << " to write.";
    return false;
  }
  return SetProtoToASCIIFile(message, fd);
}

template <typename MessageType>
static bool SetProtoToASCIIFile(const MessageType &message,
                                int file_descriptor) {
  using google::protobuf::TextFormat;
  using google::protobuf::io::FileOutputStream;
  using google::protobuf::io::ZeroCopyOutputStream;
  if (file_descriptor < 0) {
    std::cerr << "Invalid file descriptor.";
    return false;
  }
  ZeroCopyOutputStream *output = new FileOutputStream(file_descriptor);
  bool success = TextFormat::Print(message, output);
  delete output;
  close(file_descriptor);
  return success;
}