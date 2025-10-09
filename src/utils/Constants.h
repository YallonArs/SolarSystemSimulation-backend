#pragma once

#include <cmath>

struct Constants {
	// Physical
	static constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11;     // m^3 kg^-1 s^-2
	
	// Astronomical
	static constexpr double ASTRONOMICAL_UNIT = 1.495978707e11;       // m
	
	// Mathematical
	static constexpr double PI = 3.141592653589793238462643383279502884;
	
	// Conversion
	static constexpr double RAD_TO_DEG = 180.0 / PI;
	static constexpr double DEG_TO_RAD = PI / 180;
	
	static constexpr double EPSILON = std::numeric_limits<double>::epsilon();
};
