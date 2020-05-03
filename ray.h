#pragma once
#include "vector.h"

class Ray {
public:
	Ray(Vector origin, Vector dir) {
		this->O = origin;
		this->u = dir;
	}
	Vector O;
	Vector u;
};

