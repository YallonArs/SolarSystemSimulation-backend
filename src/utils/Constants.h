#pragma once

#include <cmath>
#include <limits>

namespace Constants {
	// Physical
	inline constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11;   // m^3 kg^-1 s^-2
	
	// Astronomical
	inline constexpr double ASTRONOMICAL_UNIT = 1.495978707e11;     // m
	inline constexpr double KILOMETER = 1000.0; 					// meters
	
	// Mathematical
	inline constexpr double PI = 3.141592653589793238462643383279502884;
	
	// Conversion
	inline constexpr double RAD_TO_DEG = 180.0 / PI;
	inline constexpr double DEG_TO_RAD = PI / 180;
	
	inline constexpr double EPSILON = std::numeric_limits<double>::epsilon();
};
