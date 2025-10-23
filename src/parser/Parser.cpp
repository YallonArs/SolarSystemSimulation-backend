#include <filesystem>
#include <iostream>
#include <array>
#include "toml.hpp"

#include "Parser.h"
#include "celestial/CelestialProperties.h"
#include "utils/Config.h"
#include "utils/other.h"

Parser::Parser(const std::string config_path) {
	this->configPath = (std::filesystem::path(__FILE__).parent_path().parent_path().parent_path() / config_path).string();
}

Config Parser::loadFromTable(const toml::table &table) {
	const auto *system_table_ptr = table["system"].as_table();
	if (!system_table_ptr) {
		Logger::error("No 'system' table found in config.");
		return Config();
	}

	const auto *bodies_table_ptr = (*system_table_ptr)["bodies"].as_table();
	if (!bodies_table_ptr) {
		Logger::error("No 'bodies' table found in config.");
		return Config();
	}

	const auto *comets_table_ptr = (*system_table_ptr)["comets"].as_table();
	if (!comets_table_ptr) {
		Logger::error("No 'comets' table found in config.");
		return Config();
	}

	std::string central_body_name = (*system_table_ptr)["central_body"].value_or<std::string>("");
	std::cout << "FOUND CENTRAL BODY ENTRY: " << central_body_name << std::endl;
	if (central_body_name == "") {
		Logger::error("No 'central_body' found in config.");
		return Config();
	}

	std::vector<CelestialProperties *> props_all = loadPlanets(*bodies_table_ptr, central_body_name);
	std::vector<CometProperties *> comet_props = loadComets(*comets_table_ptr, central_body_name);
	
	toml::table table_copy = table;
	auto *system_table = table_copy["system"].as_table();

	if (system_table) {
		system_table->erase("bodies");
		system_table->erase("comets");
	}

	Config config;
	config.bodies = props_all;
	config.comets = comet_props;
	config.settings = table_copy;

	return config;
}

CelestialProperties *Parser::loadBody(const toml::table &table) {
	CelestialProperties *props = new CelestialProperties();

	props->mass = table["mass"].value_or(0.0);
	props->kepler.a = table["a"].value_or(0.0);
	props->kepler.e = table["e"].value_or(0.0);
	props->kepler.omega = table["omega"].value_or(0.0);
	props->kepler.phi = table["phi"].value_or(0.0);
	props->state = PhysicsBody::State();
	
	// set externally:
	// props->name
	// props->parentName
	// props->satellites

	return props;
}

// bodies_table: 		table["system"]["bodies"]
// central_body_name:   "Sun"
std::vector<CelestialProperties *> &Parser::loadPlanets(const toml::table &bodies_table, const std::string &central_body_name) {
	std::vector<CelestialProperties *> *props_all = new std::vector<CelestialProperties *>();

	// always load the central body first
	const auto *central_body_table = bodies_table[central_body_name].as_table();

	if (!central_body_table) {
		// table with central body name does not exist
		Logger::error("Central body '" + central_body_name + "' not found in bodies.");
		return *props_all;
	}

	// try to load central body
	CelestialProperties *central_body_props = loadBody(*central_body_table);
	central_body_props->name = central_body_name;
	Logger::debug("Loaded central body: " + central_body_props->name);
	props_all->push_back(central_body_props);

	// load other bodies except the central body
	for (const auto &[key, value] : bodies_table) {
		if (value.is_table()) {
			std::string body_name(key.str());
			if (body_name == central_body_name) continue; // central body already loaded

			CelestialProperties *props = loadBody(*value.as_table());
			props->name = body_name;
			props->convertAU();
			props->parentName = central_body_name;

			std::cout << "Loaded planet: " << props->name << std::endl;

			std::vector<CelestialProperties *> satellites = loadSatellites(*value.as_table(), body_name);
			props->satellites = std::move(satellites);

			props_all->push_back(props);
			// for (auto *satellite : props->satellites)
			// 	props_all->push_back(satellite);
		}
	}

	return *props_all;
}

std::vector<CelestialProperties *> &Parser::loadSatellites(const toml::table &table, const std::string &central_body_name) {
	std::vector<CelestialProperties *> *props_satellites = new std::vector<CelestialProperties *>();

	for (const auto &[key, value] : table) {
		if (value.is_table()) {
			std::string satellite_name(key.str());

			CelestialProperties *props = loadBody(*value.as_table());
			props->name = satellite_name;
			props->kepler.a *= Constants::KILOMETER;
			props->parentName = central_body_name;

			std::cout << "Loaded satellite: " << props->name << std::endl;

			props_satellites->push_back(props);
		}
	}

	return *props_satellites;
}

std::vector<CometProperties *> &Parser::loadComets(const toml::table &table, const std::string &central_body_name) {
	std::vector<CometProperties *> *comet_props = new std::vector<CometProperties *>();

	for (const auto &[key, value] : table) {
		if (value.is_table()) {
			std::string comet_name(key.str());

			auto comet_table = *value.as_table();
			double mass = comet_table["mass"].value_or(0.0);
			double q = comet_table["q"].value_or(0.0);
			double v = comet_table["v"].value_or(0.0);
			double r_start = comet_table["r_start"].value_or(10.0);

			CometProperties *props = new CometProperties(comet_name, mass, q, v, r_start);

			comet_props->push_back(props);
		}
	}

	return *comet_props;
}

Config Parser::load() {
	// if there is no config file
	if (!std::filesystem::exists(configPath)) {
		Logger::error("Config file not found: " + configPath);
		throw std::runtime_error("Config file not found: " + configPath);
	}

	// try to parse file
	toml::table table;
	try {
		table = toml::parse_file(configPath);
	} catch (const toml::parse_error &err) {
		Logger::error("Failed to parse config file: " + std::string(err.what()));
		throw std::runtime_error("Failed to parse config file: " + std::string(err.what()));
	}

	// de-serialize raw data into CelestialProperties
	return loadFromTable(table);
}
