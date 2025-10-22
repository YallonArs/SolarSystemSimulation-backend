#include <iostream>

#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "celestial/SolarSystem.h"
#include "parser/Parser.h"
#include "simulation/Simulation.h"
#include "utils/Config.h"
#include "utils/other.h"

int main() {
	Simulator simulator;
	// simulator.getTimeStep();

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
	for (const auto &body : simulator.getSolarSystem().getBodies()) {
		std::string filename = ".run/" + str_tolower(body->name()) + "_position.txt";
		files.emplace_back(filename);
	}
	// while time < one month do steps and print moon position to files
	for (int i = 0; i < 60 * 60 * 24 * 30 * 3; ++i) {
		simulator.step();
		
		if (i % (60 * 60 * 24 * 30) == 0) {
			std::cout << "Month " << i / (60 * 60 * 24 * 30) << " completed." << std::endl;
		}
		
		if (i % 1000 != 0) continue;
		for (size_t j = 0; j < simulator.getSolarSystem().getBodies().size(); ++j) {
			CelestialBody *body = simulator.getSolarSystem().getBodies()[j];
			files[j] << (int64_t)body->position().x() << " " << (int64_t)body->position().y() << std::endl;
		}

	}

	for (auto &file : files)
		file.close();
}
