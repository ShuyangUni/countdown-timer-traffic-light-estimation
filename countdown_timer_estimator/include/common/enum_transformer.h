// Copyright 2021.12.28 <Shuyang>
#pragma once

#include <iostream>
#include <string>

#include "include/common/structure.h"

namespace cttl {
namespace common {
class EnumTransformer {
 public:
  static bool Int2EnumColorState(const int &int_color, ColorState *enum_color);
  static bool Int2EnumColorObservation(const int &int_color,
                                       ColorObservation *enum_color);
  static bool Int2EnumValueState(const int &int_value, ValueState *enum_value);
  static bool Int2EnumValueObservation(const int &int_value,
                                       ValueObservation *enum_value);
  static bool GetState(const int &int_color, const int &int_value,
                       State *state);
  static bool GetObservation(const int &int_color, const int &int_value_tens,
                             const int &int_value_ones, Observation *obs);
  static std::string Enum2StrColorState(const ColorState &enum_color);
  static std::string Enum2StrColorObservation(
      const ColorObservation &enum_color);
  static std::string Enum2StrValueState(const ValueState &enum_value);
  static std::string Enum2StrValueObservation(
      const ValueObservation &enum_value);
};

}  // namespace common
}  // namespace cttl
