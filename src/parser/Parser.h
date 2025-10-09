#pragma once

#include <string>
#include <filesystem>

#include "utils/Config.h"
#include "utils/Logger.h"

class Parser {
private:
	std::string configPath;

public:
	Parser(std::string config_path = ".config/config.toml") : configPath(config_path) {};

	Config load();
};
