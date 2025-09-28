#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "utils/Constants.h"

class Config {
public:
	using ConfigValue = std::variant<double, int, bool, std::string>;

private:
	std::unordered_map<std::string, ConfigValue> settings_;

public:
	Config();

	template<typename T>
	void set(const std::string& key, const T& value);

	template<typename T>
	T get(const std::string& key) const;
	
	template<typename T>
	T get(const std::string& key, const T& defaultValue) const;

	bool has(const std::string& key) const;
	void remove(const std::string& key);
	void clear();

	// dump/load configuration
	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename) const;

private:
	void setDefaults();
};
