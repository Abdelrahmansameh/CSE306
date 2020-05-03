#pragma once
#include "sphere.h"
#include <list>
#include <float.h>
#include <limits>
#include <algorithm>
#include "random.h"
#include <memory>

#define PI 3.14159265358979323846

class Scene {
public:
	Scene(std::list <Sphere> spheres) {
		this->spheres = spheres;
	}
	std::list<Sphere> spheres;

	std::shared_ptr<Intersection> intersect(Ray r) {
		std::shared_ptr<Intersection> ret = std::make_shared<Intersection>(nullptr, nullptr, std::numeric_limits<double>::max());
		for (auto& s : spheres) {
			std::shared_ptr<Intersection> i = s.intersect(r);
			if (i) {
				if (i->t < ret->t) {
					ret = i;
				}
			}
		}
		if (ret->S)
			return ret;
		return nullptr;
	}

	Vector getColor(Ray& ray, int ray_depth, Vector source, double I) {
		if (ray_depth < 0)
			return Vector(0, 0, 0);

		std::shared_ptr<Intersection> closest = this->intersect(ray);

		if (closest) {
			double epsilon = 0.001;
			if (closest->S->mirror) {
				Ray reflected = Ray(*(closest->P) + closest->N * epsilon, ray.u - (2 * (ray.u * closest->N)) * closest->N);
				return getColor(reflected, ray_depth - 1, source, I);
			}
			else if (closest->S->transparent) {
				double n1, n2;
				Vector N = closest->N;
				Vector P = *closest->P + N * epsilon;

				if (dot(ray.u, N) > 0) {
					N = -1 * N;
					n1 = 1.5;
					n2 = 1;
				}
				
				else {
					n1 = 1;
					n2 = 1.5;
				}

				auto k0 = pow((n1 - n2), 2) / pow((n1 + n2), 2);
				auto R = k0 + ((1 - k0)*pow(1 - abs(dot(N, ray.u)), 5));
				auto T = 1 - R;
				double u = distribution(generator);
				if (u < R) {
					Ray reflected = Ray(P, ray.u - 2 * dot(ray.u, N)*N);
					return getColor(reflected, ray_depth - 1, source, I);
				}

				Vector w_T = (n1 / n2) * (ray.u - dot(ray.u, N)*N);
				double tmp = 1 - pow(n1 / n2, 2)*(1 - pow((ray.u* N), 2));
				if (tmp < 0) {
					Ray ray = Ray(P, ray.u - 2 * dot(ray.u, N)*N);
					return getColor(ray, ray_depth - 1, source, I);
				}
				Vector w_N = (-1 * N) * sqrt(tmp);
				Vector w_t = (w_T + w_N);
				Ray refractRay = Ray(P - N * 0.02, w_t);
				return getColor(refractRay, ray_depth - 1, source, I);
			}
			else {
				double vis;
				Vector P = *closest->P;
				Vector N = closest->N;
				P = P + epsilon * N;
				double d = sqrt(dot(source - P, source - P));
				Vector omega = (source - P) / d;
				Ray r = Ray(source, Vector(0, 0, 0) - omega);
				auto exists = intersect(r);
				if (!exists) { vis = 1; }
				else {
					if (exists->t > d) {
						vis = 1;
					}
					else { vis = 0; }
				}

				Vector Lo =  (I / (4 * PI*PI*d*d)) * vis * std::max(dot(N, omega), 0.) * closest->S->albedo;
				Ray randomRay = Ray(P, random_cos(N));
				Vector tmp = getColor(randomRay, ray_depth - 1, source, I);
				Vector albedo = closest->S->albedo;
				Lo = Lo + Vector(albedo[0] * tmp[0], albedo[1] * tmp[1], albedo[2] * tmp[2]);
				return Lo;
			}
		}
		else {
			return Vector(0, 0, 0);
		}
	}
};