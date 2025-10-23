#pragma once

#include <vector>
#include "toml.hpp"

#include "celestial/Comet.h"
#include "celestial/CelestialProperties.h"

struct Config {
	std::vector<CelestialProperties*> bodies;
	std::vector<CometProperties*> comets;
	toml::table settings;

	CelestialProperties* getBodyByName(const std::string& name) {
		for (const auto& body : bodies)
			if (body->name == name)
				return body;

		return nullptr;
	}
};
