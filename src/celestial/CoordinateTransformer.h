#include "physics/PhysicsBody.h"
#include "CelestialProperties.h"

namespace CoordinateTransformer {
	PhysicsBody::State keplerToCartesian(const KeplerCoords &kepler, double mass);
};
