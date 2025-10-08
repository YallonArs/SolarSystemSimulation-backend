#pragma once

#include <string>
#include <filesystem>

#include "utils/Config.h"
#include "utils/Logger.h"

class Parser {
private:
	std::filesystem::path configPath;
	static Config parseFile(const std::filesystem::path &filename);
	static void parseFileIntoConfig(const std::filesystem::path &filename, Config &config, const std::string &root = "");

public:
	Parser(std::string config_path = ".config/") : configPath(config_path) {};

	Config load();
};
