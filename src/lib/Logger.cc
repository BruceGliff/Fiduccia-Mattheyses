#include "Logger.h"

#include <exception>
#include <iostream>

Logger Log{std::cout};

Logger::Logger(std::ostream &OutIn) : Out{&OutIn} {
  static int Instance = 0;
  if (Instance)
    throw std::runtime_error("Creating more then one Logger.");

  ++Instance;
}

Logger::operator std::ostream &() { return *Out; }

Logger &Logger::set(std::ostream &OutIn) {
  Out = &OutIn;
  return *this;
}

std::ostream &Logger::setOnce(std::ostream &OutIn) const { return OutIn; }

Logger &log() { return Log; }
