#pragma once
#include <random>
#include <vector>
#include <algorithm>
#include <math.h>
#define PI 3.14159265358979323846


std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

Vector random_cos(Vector &N) {
	double r1, r2;
	double x, y, z;
	Vector ret, ret2;

	r1 = distribution(generator);
	r2 = distribution(generator);

	double tmp = sqrt(1 - r2);
	x = cos(2 * PI * r1) *tmp;
	y = cos(2 * PI * r1) * tmp;
	z = sqrt(r2);
	std::vector<double> arr = { abs(N.x), abs(N.y), abs(N.z) };
	int minElementIndex = std::min_element(arr.begin(), arr.end()) - arr.begin();
	double m = arr[minElementIndex];
	if (minElementIndex == 0)
		ret = Vector(0, N.z, -N.y);
	if (minElementIndex == 0)
		ret = Vector(N.z, 0, -N.x);
	if (minElementIndex == 0)
		ret = Vector(N.y, -N.x, 0);
	ret = ret / ret.norm();
	ret2 = cross(N, ret);
	return (x * ret) + (y * ret2) + (z*N);
}
