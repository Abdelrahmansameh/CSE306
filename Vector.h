#pragma once
#include <iostream> 
#include <math.h> 

class Vector {
public:
	double x;
	double y;
	double z;

	explicit Vector(double x = 0., double y = 0., double z = 0.) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	const double& operator [] (int i) const {
		if (i == 0)
			return this->x;
		if (i == 1)
			return this->y;
		if (i == 2)
			return this->z;
		throw "Index out of range";
	}
	double& operator [] (int i) {
		if (i == 0)
			return this->x;
		if (i == 1)
			return this->y;
		if (i == 2)
			return this->z;
		throw "Index out of range";
	}

	double norm() {
		return pow( pow(x, 2) + pow(y, 2) +  pow(z, 2) , 0.5);
	}
};

Vector operator+(const Vector& a, const Vector& b);

Vector operator-(const Vector& a, const Vector& b);

double dot(const Vector& a, const Vector& b);

Vector operator*(const Vector& a, const double b);

Vector operator/(const Vector& a, const double b);

Vector operator*(const double b, const Vector& a);

double operator*(const Vector& a, const Vector& b);

std::ostream & operator << (std::ostream &out, const Vector& a);

Vector cross(const Vector& a, const Vector& b);