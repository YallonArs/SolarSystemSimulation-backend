#include "celestial/Comet.h"
#include "celestial/CoordinateTransformer.h"

Comet::Comet(const CometProperties &props, CelestialBody* centralBody)
	: CelestialBody(CelestialProperties()), _props(props), _central_body(centralBody) {
	setName(props.name);
	setMass(props.mass);
	setParent(centralBody);
	setState(CoordinateTransformer::vqToCartesian(_props.v, _props.q, _props.r_start, centralBody->mass()));
}
