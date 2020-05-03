#include "Vector.h"

Vector operator+(const Vector& a, const Vector& b) {
	return Vector(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

Vector operator-(const Vector& a, const Vector& b) {
	return Vector(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

double dot(const Vector& a, const Vector& b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

Vector operator*(const Vector& a, const double b) {
	return Vector(a[0] * b, a[1] * b, a[2] * b);
}

Vector operator/(const Vector& a, const double b) {
	return Vector(a[0] / b, a[1] / b, a[2] / b);
}

Vector operator*(const double b, const Vector& a) {
	return Vector(a[0] * b, a[1] * b, a[2] * b);
}


double operator*(const Vector& a, const Vector& b) {
	return dot(a, b);
}

Vector cross(const Vector& a, const Vector& b) {
	return Vector((a[1] * b[2]) - (a[2] * b[1]), (a[2] * b[0]) - (a[0] * b[2]), (a[0] * b[1]) - (a[1] * b[0]));
}

std::ostream & operator << (std::ostream &out, const Vector& a) {
	out << "[" << a.x << ", " << a.y << ", " << a.z << "]";
	return out;
}
