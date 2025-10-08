#include "Integrator.h"

void Integrator::integrate(std::vector<PhysicsBody *> &bodies, double deltaTime) {
	for (auto *body : bodies) {
		// body->setPosition(body->position() + body->velocity() * deltaTime);
		// body->setVelocity(body->velocity() + body->acceleration() * deltaTime);

		PhysicsBody::State initial_state{body->position(), body->velocity()};

		Derivative k1 = evaluate(*body, initial_state, 0, Derivative());
		Derivative k2 = evaluate(*body, initial_state, deltaTime * 0.5, k1);
		Derivative k3 = evaluate(*body, initial_state, deltaTime * 0.5, k2);
		Derivative k4 = evaluate(*body, initial_state, deltaTime, k3);

		Vector dxdt = (k1.dx + (k2.dx + k3.dx) * 2.0 + k4.dx) * (1. / 6);
		Vector dvdt = (k1.dv + (k2.dv + k3.dv) * 2.0 + k4.dv) * (1. / 6);

		Point new_position = body->position() + dxdt * deltaTime;
		Vector new_velocity = body->velocity() + dvdt * deltaTime;

		body->setPosition(new_position);
		body->setVelocity(new_velocity);
	}
}

Integrator::Derivative Integrator::evaluate(PhysicsBody &body, const PhysicsBody::State &initial_state, double dt, const Derivative &derivative) {
	PhysicsBody::State state;
	state.position = initial_state.position + derivative.dx * dt;
	state.velocity = initial_state.velocity + derivative.dv * dt;

	// temporarily set body state
	auto original_pos = body.position();
	auto original_vel = body.velocity();

	body.setPosition(state.position);
	body.setVelocity(state.velocity);
	body.updateAcceleration();

	Derivative output;
	output.dx = state.velocity;
	output.dv = body.acceleration();

	// restore original state
	body.setPosition(original_pos);
	body.setVelocity(original_vel);

	return output;
}
