#pragma once

#include <ostream>

class Logger {
  std::ostream *Out;

public:
  Logger() = delete;

  Logger(std::ostream &OutIn);
  operator std::ostream &();
  Logger &set(std::ostream &OutIn);
  std::ostream &setOnce(std::ostream &OutIn) const;

  template <typename T> Logger &operator<<(T &&V) {
    *Out << V;
    return *this;
  }
};

Logger &log();
