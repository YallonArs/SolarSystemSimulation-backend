#include <iostream>
#include <chrono>

#include "Logger.h"

Logger::~Logger() {
	if (_file_stream && _file_stream.is_open())
		_file_stream.close();
}

void Logger::debug(const std::string &message) {
	write(message, Logger::LogLevel::DEBUG);
}

void Logger::info(const std::string &message) {
	write(message, Logger::LogLevel::INFO);
}

void Logger::warning(const std::string &message) {
	write(message, Logger::LogLevel::WARNING);
}

void Logger::error(const std::string &message) {
	write(message, Logger::LogLevel::ERROR);
}

void Logger::write(const std::string &message, Logger::LogLevel level) {
	auto now = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	// example output: [2023-10-05 14:23:45.123] [INFO] Message
	std::ostringstream log_stream;
	log_stream << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
	log_stream << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";
	log_stream << "[" << levelToString(level) << "] ";
	log_stream << message << std::endl;

	std::string log_line = log_stream.str();

	std::cout << log_line;

	_file_stream << log_line;
	_file_stream.flush();
}

std::string Logger::levelToString(Logger::LogLevel level) {
	switch (level) {
	case Logger::LogLevel::DEBUG: return "DEBUG";
	case Logger::LogLevel::INFO: return "INFO";
	case Logger::LogLevel::WARNING: return "WARNING";
	case Logger::LogLevel::ERROR: return "ERROR";
	default: return "UNKNOWN";
	}
}
