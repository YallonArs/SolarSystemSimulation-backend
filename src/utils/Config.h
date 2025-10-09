#pragma once

#include <vector>
#include "celestial/CelestialProperties.h"
#include "toml.hpp"

struct Config {
	std::vector<CelestialProperties*> bodies;
	toml::table settings;

	CelestialProperties* getBodyByName(const std::string& name) {
		for (const auto& body : bodies)
			if (body->name == name)
				return body;

		return nullptr;
	}
};
