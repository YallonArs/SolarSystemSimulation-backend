#pragma once

#include <memory>
#include <chrono>

#include "celestial/SolarSystem.h"
#include "simulation/Integrator.h"
#include "utils/Logger.h"

class Simulator {
public:

private:
	SolarSystem _solar_system;
	Integrator _integrator;
	double _time_step;
	double _total_simulation_time;

public:
	Simulator(SolarSystem& system, Integrator& integrator);

	void step();
	void run(uint32_t steps);

	double getCurrentTime() const { return _total_simulation_time; };
	double getTimeStep() const { return _time_step; };
	SolarSystem& getSolarSystem() { return _solar_system; };

	void setTimeStep(double step) { _time_step = step; };

private:
	std::vector<CelestialBody*> getAllBodies() { return _solar_system.getBodies(); };
};
