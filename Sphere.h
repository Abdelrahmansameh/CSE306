#pragma once
#include "vector.h"
#include "ray.h"
#include <math.h>
#include <memory>

class Intersection;

class Sphere {
public:
	Sphere(double radius = -1., 
		Vector Center = Vector(-1. , -1, -1.) , 
		Vector albedo = Vector(-1., -1, -1.),
		bool mirror = false,
		bool transparent = false) {
		this->R = radius;
		this->C = Center;
		this->albedo = albedo;
		this->mirror = mirror;
		this->transparent = transparent;
	}
	double R;
	Vector C;
	Vector albedo;
	std::shared_ptr<Intersection> intersect(Ray r);
	double isOn(Vector P);
	bool mirror;
	bool transparent;
};

class Intersection {
public:
	Intersection(
		Sphere* S ,
		Vector* where,
		double t = -1.)
	{
		this->P = where;
		this->S = S;
		if (where && S)
		this->N = (1. / (*P - S->C).norm()) * (*P - S->C);
		this->t = t;
	};
	~Intersection() {
		delete(P);
	}
	double t;
	Vector* P;
	Vector N;
	Sphere* S;
};


