#include <string>

#include "simulation/Simulation.h"
#include "physics/PhysicsBody.h"

Simulator::Simulator(SolarSystem& system, Integrator& integrator)
	: _solar_system(system)
	, _integrator(integrator)
	, _total_simulation_time(0.0) {}


void Simulator::step() {
	std::vector<PhysicsBody*> all_bodies;
	for (const auto& body : _solar_system.getBodies())
		all_bodies.push_back(static_cast<PhysicsBody*>(body));

	PhysicsEngine().calculateForces(all_bodies);

	for (auto body : all_bodies)
		body->updateAcceleration();

	_integrator.integrate(all_bodies, _time_step);

	_solar_system.shiftToCentralBodyReference();

	_total_simulation_time += _time_step;
}


void Simulator::run(uint32_t steps) {
	for (uint32_t i = 0; i < steps; ++i)
		step();
}
