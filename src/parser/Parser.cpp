#include <filesystem>
#include <iostream>
#include "toml.hpp"

#include "Parser.h"
#include "celestial/CelestialProperties.h"
#include "utils/Config.h"

Config Parser::load() {
	toml::table tbl = toml::parse_file(configPath);

	std::vector<CelestialProperties *> props_all;

	for (const auto &[key, value] : *tbl["system"]["bodies"].as_table()) {
		if (value.is_table()) {
			CelestialProperties *props = new CelestialProperties();
			const auto section = *value.as_table();

			props->name = key.str();
			props->mass = section["mass"].value_or(0.0);
			props->kepler.a = section["a"].value_or(0.0) * Constants::ASTRONOMICAL_UNIT;
			props->kepler.e = section["e"].value_or(0.0);
			props->kepler.omega = section["omega"].value_or(0.0);
			props->kepler.phi = section["phi"].value_or(0.0);
			props->state = PhysicsBody::State();

			props_all.push_back(props);
		}
	}

	tbl["system"].as_table()->erase("bodies");

	Config config;
	config.bodies = props_all;
	config.settings = tbl;

	return config;
}
