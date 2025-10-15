#include <iostream>

#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "celestial/SolarSystem.h"
#include "parser/Parser.h"
#include "simulation/Simulation.h"
#include "utils/Config.h"

std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::tolower(c); } // correct
	);
	return s;
}

int main() {
	Parser parser;
	Config config = parser.load();

	for (CelestialProperties *body_props : config.bodies) {
		std::cout << "Body: " << body_props->name << std::endl;
		std::cout << "  Mass: " << body_props->mass << std::endl;
		std::cout << "  Parent: " << (body_props->parentName.empty() ? "None" : body_props->parentName) << std::endl;
		std::cout << "  Kepler: a=" << body_props->kepler.a
				  << " e=" << body_props->kepler.e
				  << " omega=" << body_props->kepler.omega;
		// list satellites
		std::cout << "  Satellites: ";
		
		// list body_props->satellites;
		if (!body_props->satellites.empty()) {
			for (size_t i = 0; i < body_props->satellites.size(); ++i) {
				std::cout << body_props->satellites[i]->name;
			 std::cout << " (" << (body_props->satellites[i]->parentName.empty() ? "None" : body_props->satellites[i]->parentName) << ")";
				if (i != body_props->satellites.size() - 1)
					std::cout << ", ";
		 }
		} else {
			std::cout << "None";
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}

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
			// satellite->shiftToParentReference();
			
			bodies_all.emplace_back(satellite);
		}

		bodies_all.emplace_back(body);
	}

	// TODO: bug
	/*
	problem in shifting satellite to global coords
	when adding satellite to body at (line 61) the parent position/velocity aren't calculated yet, 
	both they are (0,0).

	do shifting after all keplerian to cartesian conversions are done

	FIXED!
	// TODO: remove this message
	*/

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
		// print body position and velocity
		std::cout << "Initialized body: " << body->name() << std::endl;
		std::cout << "  Position: (" << body->position().x() << ", " << body->position().y() << ")" << std::endl;
		std::cout << "  Velocity: (" << body->velocity().x() << ", " << body->velocity().y() << ")" << std::endl;
		std::cout << std::endl;
	}

	// Add all bodies to solarSystem in one pass
	for (auto *body : bodies_all){
		body->shiftToParentReference();
		solarSystem.addBody(body);

		// print body position and velocity
		std::cout << "INIT 2: " << body->name() << std::endl;
		std::cout << "  Position: (" << body->position().x() << ", " << body->position().y() << ")" << std::endl;
		std::cout << "  Velocity: (" << body->velocity().x() << ", " << body->velocity().y() << ")" << std::endl;
		std::cout << std::endl;

	}

	solarSystem.setCentralBody(central_body_name);

	// Convert all bodies' stored parent-relative states into global coordinates
	// using the SolarSystem helper (centralizes shifting logic).
	solarSystem.shiftToCentralBodyReference();

	// for each body print parent
	// also print coordinates and velocities
	// this is to verify that satellites are correctly assigned and positioned
	std::cout << "Solar System Bodies and their Parents:" << std::endl;
	for (const auto &body : solarSystem.getBodies()) {
		std::cout << "Body: " << body->name();
		if (body->getParent())
			std::cout << "  Parent: " << body->getParent()->name();
		else
			std::cout << "  No parent";
		std::cout << std::endl;

		// Print coordinates and velocities
		std::cout << "  Position: (" << body->position().x() << ", " << body->position().y() << ")";
		std::cout << "  Velocity: (" << body->velocity().x() << ", " << body->velocity().y() << ")";
		std::cout << std::endl;
	}

	Simulator simulator(solarSystem, integrator);
	simulator.setTimeStep(100); // 100 second time step

	// while time < one month do steps and print moon position to file
	simulator.start();

	// // benchmark loop
	// auto start = std::chrono::high_resolution_clock::now();
	// for (int i = 0; i < 1e6; ++i)
	// 	simulator.step();
	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsed = end - start;
	// std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
	// std::cout << "Steps per second: " << 1e6 / elapsed.count() << std::endl;
	// std::cout << "Ms per tick: " << elapsed.count() / 1e6 * 1000 << std::endl;
	
	std::vector<std::ofstream> files;
	for (const auto &body : solarSystem.getBodies()) {
		std::string filename = ".run/" + str_tolower(body->name()) + "_position.txt";
		files.emplace_back(filename);
	}
	for (int i = 0; i < 60 * 60 * 24 * 30. / 100; ++i) {
		simulator.step();
		
		for (size_t j = 0; j < solarSystem.getBodies().size(); ++j) {
			CelestialBody *body = solarSystem.getBodies()[j];
			files[j] << (int64_t)body->position().x() << " " << (int64_t)body->position().y() << std::endl;
		}
	}

	for (auto &file : files)
		file.close();
}
