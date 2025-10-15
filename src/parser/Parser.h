#pragma once

#include <string>
#include <filesystem>

#include "utils/Config.h"
#include "utils/Logger.h"

class Parser {
private:
	std::string configPath;

	CelestialProperties* loadBody(const toml::table& table);
	std::vector<CelestialProperties *> &loadPlanets(const toml::table &table, const std::string &central_body_name);
	std::vector<CelestialProperties *> &loadSatellites(const toml::table &table, const std::string &central_body_name);

	Config loadFromTable(const toml::table& table);

public:
	Parser(std::string config_path = ".config/config.toml") : configPath(config_path) {};

	Config load();
};
