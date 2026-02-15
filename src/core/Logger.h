#ifndef GAME_ENGINE_LOGGER_H
#define GAME_ENGINE_LOGGER_H

#include <iostream>
#include <ostream>
#include <string>

class Logger {
public:
  enum Level { DEBUG, INFO, WARNING, ERROR };

  static void log(Level level, const std::string& message) {
    const char* levelStr[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    std::cout << "[" << levelStr[level] << "] " << message << std::endl;
  }

  static void debug(const std::string& msg) { log(DEBUG, msg); }
  static void info(const std::string& msg) { log(INFO, msg); }
  static void warn(const std::string& msg) { log(WARNING, msg); }
  static void error(const std::string& msg) { log(ERROR, msg); }
};

#endif //GAME_ENGINE_LOGGER_H