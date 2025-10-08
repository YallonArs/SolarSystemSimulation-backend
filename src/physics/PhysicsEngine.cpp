#include <algorithm>
#include <execution>

#include "physics/PhysicsEngine.h"
#include "physics/PhysicsBody.h"

void PhysicsEngine::calculateForces(std::vector<PhysicsBody *> &bodies) {
	for (auto body: bodies)
		body->clearForces();

	// create index pairs for parallel processing
	std::vector<std::pair<uint16_t, uint16_t>> pairs;
	for (uint16_t i = 0; i < bodies.size(); ++i)
		for (uint16_t j = i + 1; j < bodies.size(); ++j)
			pairs.emplace_back(i, j);

	std::for_each(std::execution::par_unseq, pairs.begin(), pairs.end(),
				  [&](const auto &pair) {  // const std::pair<uint16_t, uint16_t> &pair
					  calculatePairwiseForce(bodies[pair.first], bodies[pair.second]);
				  });
}

void PhysicsEngine::calculatePairwiseForce(PhysicsBody *body1, PhysicsBody *body2) {
	auto force1 = Force(body2);
	auto force2 = Force(body1);

	body1->addForce(&force1);
	body2->addForce(&force2);
}
