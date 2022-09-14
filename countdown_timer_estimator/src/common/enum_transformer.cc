// Copyright 2021.12.28 <Shuyang>
#include "include/common/enum_transformer.h"

namespace cttl {
namespace common {
bool EnumTransformer::Int2EnumColorState(const int &int_color,
                                         ColorState *enum_color) {
  switch (int_color) {
    case 1:
      *enum_color = ColorState::cs_red;
      break;
    case 2:
      *enum_color = ColorState::cs_green;
      break;
    case 3:
      *enum_color = ColorState::cs_yellow;
      break;
    default:
      std::cout << "[Error]: Int2EnumColorState(): input int_color wrong: "
                << int_color << std::endl;
      return false;
  }
  return true;
}

bool EnumTransformer::Int2EnumColorObservation(const int &int_color,
                                               ColorObservation *enum_color) {
  switch (int_color) {
    case 1:
      *enum_color = ColorObservation::cz_red;
      break;
    case 2:
      *enum_color = ColorObservation::cz_green;
      break;
    case 3:
      *enum_color = ColorObservation::cz_yellow;
      break;
    case 4:
      *enum_color = ColorObservation::cz_unknown;
      break;
    default:
      std::cout
          << "[Error]: Int2EnumColorObservation(): input int_color wrong: "
          << int_color << std::endl;
      return false;
  }
  return true;
}

bool EnumTransformer::Int2EnumValueState(const int &int_value,
                                         ValueState *enum_value) {
  switch (int_value) {
    case 0 ... 9:
      *enum_value = (ValueState)int_value;
      break;
    default:
      std::cout << "[Error]: Int2EnumValueState(): input int_value wrong: "
                << int_value << std::endl;
      return false;
  }
  return true;
}

bool EnumTransformer::Int2EnumValueObservation(const int &int_value,
                                               ValueObservation *enum_value) {
  switch (int_value) {
    case 0 ... 9:
      *enum_value = (ValueObservation)int_value;
      break;
    case 10:
      *enum_value = ValueObservation::vz_null;
      break;
    default:
      std::cout
          << "[Error]: Int2EnumValueObservation(): input int_value wrong: "
          << int_value << std::endl;
      return false;
  }
  return true;
}

bool EnumTransformer::GetState(const int &int_color, const int &int_value,
                               State *state) {
  int int_value_tens = int_value / 10;
  int int_value_ones = int_value % 10;

  ColorState enum_color;
  if (!Int2EnumColorState(int_color, &enum_color)) {
    return false;
  }
  ValueState enum_value_tens;
  if (!Int2EnumValueState(int_value_tens, &enum_value_tens)) {
    return false;
  }
  ValueState enum_value_ones;
  if (!Int2EnumValueState(int_value_ones, &enum_value_ones)) {
    return false;
  }
  state->c = enum_color;
  state->v_tens = enum_value_tens;
  state->v_ones = enum_value_ones;
  return true;
}

bool EnumTransformer::GetObservation(const int &int_color,
                                     const int &int_value_tens,
                                     const int &int_value_ones,
                                     Observation *obs) {
  ColorObservation enum_color;
  if (!Int2EnumColorObservation(int_color, &enum_color)) {
    return false;
  }
  ValueObservation enum_value_tens;
  if (!Int2EnumValueObservation(int_value_tens, &enum_value_tens)) {
    return false;
  }
  ValueObservation enum_value_ones;
  if (!Int2EnumValueObservation(int_value_ones, &enum_value_ones)) {
    return false;
  }
  obs->c = enum_color;
  obs->v_tens = enum_value_tens;
  obs->v_ones = enum_value_ones;
  return true;
}

std::string EnumTransformer::Enum2StrColorState(const ColorState &enum_color) {
  switch (enum_color) {
    case ColorState::cs_red:
      return "red";
    case ColorState::cs_green:
      return "green";
    case ColorState::cs_yellow:
      return "yellow";
  }
}

std::string EnumTransformer::Enum2StrColorObservation(
    const ColorObservation &enum_color) {
  switch (enum_color) {
    case ColorObservation::cz_red:
      return "red";
    case ColorObservation::cz_green:
      return "green";
    case ColorObservation::cz_yellow:
      return "yellow";
    case ColorObservation::cz_unknown:
      return "unknown";
  }
}

std::string EnumTransformer::Enum2StrValueState(const ValueState &enum_value) {
  switch (enum_value) {
    case ValueState::vs_0:
      return "0";
    case ValueState::vs_1:
      return "1";
    case ValueState::vs_2:
      return "2";
    case ValueState::vs_3:
      return "3";
    case ValueState::vs_4:
      return "4";
    case ValueState::vs_5:
      return "5";
    case ValueState::vs_6:
      return "6";
    case ValueState::vs_7:
      return "7";
    case ValueState::vs_8:
      return "8";
    case ValueState::vs_9:
      return "9";
  }
}

std::string EnumTransformer::Enum2StrValueObservation(
    const ValueObservation &enum_value) {
  switch (enum_value) {
    case ValueObservation::vz_0:
      return "0";
    case ValueObservation::vz_1:
      return "1";
    case ValueObservation::vz_2:
      return "2";
    case ValueObservation::vz_3:
      return "3";
    case ValueObservation::vz_4:
      return "4";
    case ValueObservation::vz_5:
      return "5";
    case ValueObservation::vz_6:
      return "6";
    case ValueObservation::vz_7:
      return "7";
    case ValueObservation::vz_8:
      return "8";
    case ValueObservation::vz_9:
      return "9";
    case ValueObservation::vz_null:
      return "[]";
  }
}
}  // namespace common
}  // namespace cttl
