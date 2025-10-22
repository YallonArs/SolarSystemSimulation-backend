#include "physics/PhysicsBody.h"
#include "CelestialProperties.h"

namespace CoordinateTransformer {
	PhysicsBody::State keplerToCartesian(const KeplerCoords &kepler, double mass);
	PhysicsBody::State vqToCartesian(const double v0, const double q, const double r, double mass);
};
