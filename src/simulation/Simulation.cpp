#include <string>

#include "simulation/Simulation.h"
#include "physics/PhysicsBody.h"
#include "parser/Parser.h"

Simulator::Simulator(SolarSystem& system, Integrator& integrator)
	: _solar_system(system)
	, _integrator(integrator)
	, _total_simulation_time(0.0) {}

Simulator::Simulator() {
	Parser parser;
	Config config = parser.load();

	SolarSystem solarSystem;
	Integrator integrator;

	// init Sun
	std::string central_body_name = config.settings["system"]["central_body"].value_or("Sun");
	CelestialProperties central_body_props = *config.getBodyByName(central_body_name);
	CelestialBody central_body(central_body_props);

	std::vector<CelestialBody*> bodies_all;
	for (auto *body_props : config.bodies) {
		CelestialBody* body = new CelestialBody(*body_props);

		for (auto *sat_props : body_props->satellites) {
			CelestialBody *satellite = new CelestialBody(*sat_props);
			body->addSatellite(satellite);			
			bodies_all.emplace_back(satellite);
		}

		bodies_all.emplace_back(body);
	}

	// Set states for all bodies except central body (Sun)
	for (auto *body : bodies_all) {
		if (body->name() == central_body_name) continue;
		
		double parent_mass = central_body_props.mass;
		if (!body->getParentName().empty()) {
			CelestialProperties *parent_props = config.getBodyByName(body->getParentName());
			if (parent_props)
				parent_mass = parent_props->mass;
		}
		body->setStateFromKepler(body->getKepler(), parent_mass);
	}

	for (auto *body : bodies_all){
		body->shiftToParentReference();
		solarSystem.addBody(body);
	}

	solarSystem.setCentralBody(central_body_name);
	solarSystem.shiftToCentralBodyReference();

	_solar_system = solarSystem;
	_integrator = integrator;
	setTimeStep(config.settings["simulation"]["time_step"].value_or(100.0));
}

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
