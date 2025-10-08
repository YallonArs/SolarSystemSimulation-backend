#pragma once

#include <memory>
#include <chrono>

#include "celestial/SolarSystem.h"
#include "simulation/Integrator.h"
#include "utils/Logger.h"

class Simulator {
public:
	enum class State {
		STOPPED,
		RUNNING,
		PAUSED
	};

private:
	SolarSystem _solar_system;
	Integrator _integrator;
	State _simulation_state;
	double _time_step;
	double _total_simulation_time;
	std::chrono::high_resolution_clock::time_point _last_step_time;

public:
	Simulator(SolarSystem& system, Integrator& integrator);

	void start();
	void pause();
	void stop();
	void resume();
	bool step();
	void run(double duration);

	State getState() const { return _simulation_state; };
	double getCurrentTime() const { return _total_simulation_time; };
	double getTimeStep() const { return _time_step; };
	SolarSystem& getSolarSystem() { return _solar_system; };

	void setTimeStep(double step) { _time_step = step; };

private:
	std::vector<CelestialBody*> getAllBodies() { return _solar_system.getBodies(); };
};
