#include <filesystem>
#include <fstream>
#include <sstream>

#include "Parser.h"

Config Parser::parseFile(const std::filesystem::path &filename) {
	Config config;

	std::ifstream file_stream(filename);
	std::string line;
	while (std::getline(file_stream, line)) {
		// Skip empty lines and comments
		if (line.empty() || line[0] == '#') continue;
		std::istringstream iss(line);
		std::string key, type, eq, value_str;
		if (!(iss >> key >> type >> eq >> value_str)) continue;
		// Remove leading spaces from value_str
		value_str.erase(0, value_str.find_first_not_of(" "));
		
		if (type == "string") {
			config.set(key, value_str);
		} else if (type == "int") {
			try {
				int val = std::stoi(value_str);
				config.set(key, val);
			} catch (...) {
				Logger::error("expected int value for key: " + key);
			}
		} else if (type == "double") {
			try {
				double val = std::stod(value_str);
				config.set(key, val);
			} catch (...) {
				Logger::error("expected double value for key: " + key);
			}
		} else if (type == "bool") {
			bool val = (value_str == "true" || value_str == "1");
			config.set(key, val);
		}
	}
	return config;
}

void Parser::parseFileIntoConfig(const std::filesystem::path &filename, Config &config, const std::string &root) {
	Config fileConfig = parseFile(filename);
	// config.addConfig(root, fileConfig);
}

Config Parser::load() {
	// recursive walk
	Config config;

	for (const auto &entry : std::filesystem::directory_iterator(configPath)) {
		if (entry.is_regular_file()) {
			std::filesystem::path filepath = entry.path().filename().stem();

			parseFileIntoConfig(entry.path(), config, filepath.stem().string());
		}
	}

	Logger::info("Loaded configuration from directory: " + configPath.string());

	return config;

	// for (const auto& entry : std::filesystem::recursive_directory_iterator(configPath)) {
	// 	if (entry.is_regular_file()) {
	// 		// get entry path splitted
	// 		auto relativePath = std::filesystem::relative(entry.path(), configPath);
	// 		auto parts = relativePath.parent_path();
	// 		// Example: parse each file and add to config
	// 		// config.add(parseFile(entry.path()));
	// 	}
	// }
	// return config;
}
