#include <string>

#include "simulation/Simulation.h"
#include "physics/PhysicsBody.h"

Simulator::Simulator(SolarSystem& system, Integrator& integrator)
	: _solar_system(system)
	, _integrator(integrator)
	, _simulation_state(State::STOPPED)
	, _total_simulation_time(0.0) {}


void Simulator::start() {
	if (_simulation_state == State::RUNNING) return;

	_simulation_state = State::RUNNING;
	Logger::info("Simulation started");
}


void Simulator::pause() {
	if (_simulation_state != State::RUNNING) return;

	_simulation_state = State::PAUSED;
	Logger::info("Simulation paused at time: " + std::to_string(_total_simulation_time));
}


void Simulator::stop() {
	_simulation_state = State::STOPPED;
	_total_simulation_time = 0.0;

	Logger::info("Simulation stopped and reset");
}


void Simulator::resume() {
	if (_simulation_state == State::PAUSED) {
		_simulation_state = State::RUNNING;
		Logger::info("Simulation resumed");
	}
}

bool Simulator::step() {
	if (_simulation_state != State::RUNNING) return false;

	std::vector<PhysicsBody*> all_bodies;
	for (const auto& body : _solar_system.getBodies())
		all_bodies.push_back(static_cast<PhysicsBody*>(body));

	PhysicsEngine().calculateForces(all_bodies);

	for (auto body : all_bodies)
		body->updateAcceleration();

	_integrator.integrate(all_bodies, _time_step);

	// Shift all bodies to central body reference frame after integration
	_solar_system.shiftToCentralBodyReference();

	_total_simulation_time += _time_step;

	return true;
}


void Simulator::run(double duration) {
	double end_time = _total_simulation_time + duration;
	start();

	while (_simulation_state == State::RUNNING &&
		_total_simulation_time < end_time) {
		if (!step()) break;
	}
}

// std::vector<PhysicsBody*> Simulator::getAllBodies() {
// 	std::vector<PhysicsBody*> all_bodies;

// 	for (const auto& body : _solar_system.getBodies())
// 		all_bodies.push_back(body);

// 	return all_bodies;
// }
