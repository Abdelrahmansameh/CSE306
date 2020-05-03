#pragma once
#include "Sphere.h"
#include "ray.h"
#include <memory>


std::shared_ptr<Intersection> Sphere::intersect(Ray r) {
	//std::cout << C << " " << R << std::endl;
	//std::cout << r.O << " " << r.u << std::endl;
	Vector V = r.O - C;
	auto delta =  dot(r.u, V)*dot(r.u, V)  - (dot(V,  V) - R*R ); 
	if (delta < 0)
		return nullptr;
	else {
		auto t1 = ( r.u * (C - r.O) ) - pow(delta, 0.5);
		auto t2 = ( r.u * (C - r.O) ) + pow(delta, 0.5);
		if (t2 < 0) {
			return nullptr;
		}
		if (t1 >= 0) {
			Vector* where = new Vector(r.O + (t1*r.u));
			return std::make_shared<Intersection> (this, where, t1);
		} 
		else {
			Vector* where = new Vector(r.O + (t2*r.u));
			return std::make_shared<Intersection>(this, where, t2);
		}
	}
}

double Sphere::isOn(Vector P) {
	return ((P.z - C.z)*(P.z - C.z) + (P.y - C.y)*(P.y - C.y) + (P.x - C.x)*(P.x - C.x) - R * R);
}