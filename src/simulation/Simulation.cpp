#include <string>
#include <iostream>

#include "simulation/Simulation.h"
#include "physics/PhysicsBody.h"
#include "parser/Parser.h"
#include "utils/other.h"
#include "celestial/CoordinateTransformer.h"

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

	// load planets and moons into flattened list
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

	// load comets
	for (auto *comet_props : config.comets) {
		std::cout << "Comet: " << comet_props->name << std::endl;
		comet_props->v *= 1000; // km/s to m/s
		comet_props->q *= Constants::ASTRONOMICAL_UNIT; // AU to m
		comet_props->r_start *= Constants::ASTRONOMICAL_UNIT; // AU to m

		Comet* comet = new Comet(*comet_props, &central_body);

		PhysicsBody::State state = CoordinateTransformer::vqToCartesian(
			comet_props->v,
			comet_props->q,
			comet_props->r_start,
			central_body.mass()
		);

		comet->setState(state);
		comet->shiftToParentReference();
		solarSystem.addComet(comet);
	}

	// set initial states for planets and moons
	for (auto *body : bodies_all) {
		// skip Sun
		if (body->name() == central_body_name) continue;
		
		// set parent mass
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
	std::vector<PhysicsBody*> bodies;
	for (const auto& body : _solar_system.getBodies())
		bodies.push_back(static_cast<PhysicsBody*>(body));

	PhysicsEngine().calculateForces(bodies);

	for (auto body : bodies)
		body->updateAcceleration();

	_integrator.integrate(bodies, _time_step);

	_solar_system.shiftToCentralBodyReference();

	_total_simulation_time += _time_step;
}


void Simulator::run(uint32_t steps) {
	for (uint32_t i = 0; i < steps; ++i)
		step();
}
