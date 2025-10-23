#pragma once

#include <algorithm>
#include <initializer_list>
#include <string>
#include <algorithm>

// -------------- IN() --------------
inline bool in(const std::initializer_list<std::string> &list, const std::string &value) {
	return std::find(list.begin(), list.end(), value) != list.end();
}

template <typename T, typename U>
inline bool in(const T &list, const U &value) {
	return std::find(std::begin(list), std::end(list), value) != std::end(list);
}

// Overload for std::map to check keys
template <typename K, typename V>
inline bool in(const std::map<K, V> &m, const K &key) {
	return m.find(key) != m.end();
}

// ------------- ALLIN() -------------
template <typename T, typename U>
bool allin(const T &list, const U &values) {
	for (const auto &value : values)
		if (!in(list, value))
			return false;
	return true;
}

template <typename T>
bool allin(const T &list, const std::initializer_list<std::string> &values) {
	// Specialization for std::map<std::string, ...>
	for (const auto &key : values) {
		if (list.find(key) == list.end())
			return false;
	}
	return true;
}

// -------------- OTHER --------------

inline double clamp01(double v){ if(v>1) return 1; if(v<-1) return -1; return v; }

inline std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::tolower(c); }
	);
	return s;
}
