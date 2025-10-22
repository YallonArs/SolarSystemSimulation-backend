#pragma once

#include <algorithm>
#include <initializer_list>
#include <string>
#include <algorithm>

inline bool in(const std::initializer_list<std::string> &list, const std::string &value) {
	return std::find(list.begin(), list.end(), value) != list.end();
}

// for generic containers without template
template <typename T, typename U>
inline bool in(const T &list, const U &value) {
	using std::begin;
	using std::end;
	return std::find(begin(list), end(list), value) != end(list);
}

// Overload for std::map to check keys
template <typename K, typename V>
inline bool in(const std::map<K, V> &m, const K &key) {
	return m.find(key) != m.end();
}
/*
std::vector<int> numbers = {1, 2, 3, 4};
int value = 3;
if (in(numbers, value)) {
	// value is in the list
}
*/

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

inline double clamp01(double v){ if(v>1) return 1; if(v<-1) return -1; return v; }

inline std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::tolower(c); }
	);
	return s;
}
