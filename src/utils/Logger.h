#pragma once

#include <string>
#include <fstream>

class Logger {
public:
	enum class LogLevel {
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR
	};

private:
	static std::ofstream _file_stream;

public:
	Logger() = default;
	~Logger();

	static void debug(const std::string& message);
	static void info(const std::string& message);
	static void warning(const std::string& message);
	static void error(const std::string& message);

private:
	static void write(const std::string& message, Logger::LogLevel level);
	static std::string levelToString(Logger::LogLevel level);
};
