#pragma once

#include <yaml-cpp/yaml.h>
#include <chrono>

template <typename T>
inline static T getValueByKey(const std::string& key,
                              YAML::const_iterator start,
                              YAML::const_iterator end,
                              T default_value = T{}) {
  for (; start != end; ++start) {
    const auto& v = *start;
    if (v.first.as<std::string>() == key) {
      return v.second.as<T>();
    }
  }

  return default_value;
}

template <class TimeDimension = std::chrono::milliseconds>
struct MeasureTime {
  std::chrono::steady_clock::time_point start;

  MeasureTime() : start(std::chrono::steady_clock::now()) {}

  /*
   * time in ms
   */
  auto measure() {
    const auto p = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<TimeDimension>(p - start).count();
  }

  void reset() { start = std::chrono::steady_clock::now(); }

  ~MeasureTime() {}
};
