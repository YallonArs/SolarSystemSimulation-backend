#include <stdexcept>

#include "utils/Config.h"

Config::Config() {
	setDefaults();
}

template <typename T>
void Config::set(const std::string &key, const T &value) {
	settings_[key] = value;
}

template <typename T>
T Config::get(const std::string &key) const {
	auto it = settings_.find(key);
	if (it != settings_.end()) {
		return std::get<T>(it->second);
	}
	throw std::runtime_error("Configuration key not found: " + key);
}

template <typename T>
T Config::get(const std::string &key, const T &defaultValue) const {
	auto it = settings_.find(key);
	if (it != settings_.end()) {
		try {
			return std::get<T>(it->second);
		} catch (const std::bad_variant_access &) {
			return defaultValue;
		}
	}
	return defaultValue;
}

bool Config::has(const std::string &key) const {
	return settings_.find(key) != settings_.end();
}

void Config::remove(const std::string &key) {
	settings_.erase(key);
}

void Config::clear() {
	settings_.clear();
	setDefaults();
}

void Config::saveToFile(const std::string& filename) const {
	// TODO: implement saving to file
}

void Config::loadFromFile(const std::string& filename) {
	// TODO: implement loading from file
}

void Config::setDefaults() {
	// Simulation parameters
	set("simulation.time_step", 86400.0); // 1 day in seconds
	set("simulation.max_time", 3.154e10); // ~1000 years in seconds

	// Logging parameters
	set("logging.level", std::string("info"));
	set("logging.console_output", true);
	set("logging.file_output", false);
	set("logging.filename", std::string("simulation.log"));

	// Rendering parameters (for future GUI)
	set("render.window_width", 1024);
	set("render.window_height", 768);
	set("render.fps_limit", 60);
	set("render.show_orbits", true);
	set("render.show_velocity_vectors", false);

	// Analysis parameters
	set("analysis.save_trajectory_data", false);
	set("analysis.trajectory_sample_interval", 86400.0); // 1 day
	set("analysis.collision_detection", true);
	set("analysis.escape_velocity_detection", true);
}
