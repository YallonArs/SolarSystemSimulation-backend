#pragma once

#include <cmath>

struct Constants {
    // Physical constants
    static constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11;     // m^3 kg^-1 s^-2
    static constexpr double SPEED_OF_LIGHT = 299792458;               // m/s
    static constexpr double PLANCK_CONSTANT = 6.62607015e-34;         // J⋅Hz^-1
    static constexpr double BOLTZMANN_CONSTANT = 1.380649e-23;        // J/K
    static constexpr double STEFAN_BOLTZMANN = 5.670374419e-8;        // W⋅m^-2⋅K^-4
    
    // Astronomical constants
    static constexpr double ASTRONOMICAL_UNIT = 1.495978707e11;       // m
    static constexpr double PARSEC = 3.0857e16;                       // m
    static constexpr double LIGHT_YEAR = 9.4607304725808e15;          // m
    static constexpr double SOLAR_MASS = 1.98847e30;                  // kg
    static constexpr double EARTH_MASS = 5.9722e24;                   // kg
    static constexpr double JUPITER_MASS = 1.8982e27;                 // kg
    static constexpr double SOLAR_RADIUS = 6.96e8;                    // m
    static constexpr double EARTH_RADIUS = 6.371e6;                   // m
    static constexpr double JUPITER_RADIUS = 6.9911e7;                // m
    
    // Time constants
    static constexpr double SECONDS_PER_MINUTE = 60;
    static constexpr double SECONDS_PER_HOUR = 3600;
    static constexpr double SECONDS_PER_DAY = 86400;
    static constexpr double SECONDS_PER_YEAR = 31557600;              // Julian year
    static constexpr double DAYS_PER_YEAR = 365.25;                   // Julian year
    
    // Mathematical constants
    static constexpr double PI = 3.141592653589793238462643383279502884;
    static constexpr double E = 2.718281828459045235360287471352662498;
    static constexpr double SQRT_2 = 1.414213562373095048801688724209698079;
    
    // Conversion factors
    static constexpr double RAD_TO_DEG = 180.0 / PI;
    static constexpr double DEG_TO_RAD = PI / 180;
    static constexpr double AU_TO_METERS = ASTRONOMICAL_UNIT;
    static constexpr double METERS_TO_AU = 1 / ASTRONOMICAL_UNIT;
    
    // Numerical precision
    static constexpr double EPSILON = std::numeric_limits<double>::epsilon();
};
