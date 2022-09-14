/*
 * 
 * Copyright (c) [2022] <Shuyang ZHANG>, All Rights Reserved. 
 * @Author: Shuyang ZHANG
 * @Date: 2022-09-14 23:34:45
 * @LastEditors: Shuyang ZHANG
 * @LastEditTime: 2022-09-14 23:37:53
 * @Description: 
 */
#pragma once

namespace cttl {
namespace common {
enum ColorState { cs_red = 0, cs_green = 1, cs_yellow = 2 };

enum ColorObservation {
  cz_red = 0,
  cz_green = 1,
  cz_yellow = 2,
  cz_unknown = 3
};
enum ValueState {
  vs_0 = 0,
  vs_1 = 1,
  vs_2 = 2,
  vs_3 = 3,
  vs_4 = 4,
  vs_5 = 5,
  vs_6 = 6,
  vs_7 = 7,
  vs_8 = 8,
  vs_9 = 9
};
enum ValueObservation {
  vz_0 = 0,
  vz_1 = 1,
  vz_2 = 2,
  vz_3 = 3,
  vz_4 = 4,
  vz_5 = 5,
  vz_6 = 6,
  vz_7 = 7,
  vz_8 = 8,
  vz_9 = 9,
  vz_null = 10
};

}  // namespace common
}  // namespace cttl
