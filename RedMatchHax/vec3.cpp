#include "vec3.h"

vec3::vec3() = default;
vec3::vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
vec3::vec3(const vec3 & otherVec) : X(otherVec.X), Y(otherVec.Y), Z(otherVec.Z) {}

vec3::~vec3() = default;

//Vector addition
vec3 vec3::operator+(const vec3 & otherVec) {
	vec3 temp;
	temp.X = X + otherVec.X;
	temp.Y = Y + otherVec.Y;
	temp.Z = Z + otherVec.Z;
	return temp;
}

vec3& vec3::operator+=(const vec3 & otherVec) {
	X += otherVec.X;
	Y += otherVec.Y;
	Z += otherVec.Z;
	return *this;
}

vec3 vec3::operator+(float s) {
	vec3 temp;
	temp.X = X + s;
	temp.Y = Y + s;
	temp.Z = Z + s;
	return temp;
}

vec3& vec3::operator+=(float s) {
	X += s;
	Y += s;
	Z += s;
	return *this;
}


//Vector subtraction
vec3 vec3::operator-(const vec3 & otherVec) {
	vec3 temp;
	temp.X = X - otherVec.X;
	temp.Y = Y - otherVec.Y;
	temp.Z = Z - otherVec.Z;
	return temp;
}

vec3& vec3::operator-=(const vec3 & otherVec) {
	X -= otherVec.X;
	Y -= otherVec.Y;
	Z -= otherVec.Z;
	return *this;
}

vec3 vec3::operator-(float s) {
	vec3 temp;
	temp.X = X - s;
	temp.Y = Y - s;
	temp.Z = Z - s;
	return temp;
}

vec3& vec3::operator-=(float s) {
	X -= s;
	Y -= s;
	Z -= s;
	return *this;
}


//Vector multiplication
vec3 vec3::operator*(float s) {
	vec3 temp;
	temp.X = X * s;
	temp.Y = Y * s;
	temp.Z = Z * s;
	return temp;
}

vec3& vec3::operator*=(float s) {
	X *= s;
	Y *= s;
	Z *= s;
	return *this;
}


//Vector division
vec3 vec3::operator/(float s) {
	vec3 temp;
	temp.X = X / s;
	temp.Y = Y / s;
	temp.Z = Z / s;
	return temp;
}

vec3& vec3::operator/=(float s) {
	X /= s;
	Y /= s;
	Z /= s;
	return *this;
}

//Useful Vector Operations
float vec3::Length() const {
	return std::sqrt(X * X + Y * Y + Z * Z);
}

vec3& vec3::Normalize() {
	float magnitude = Length();
	if (magnitude == 0) return *this;
	return (*this) /= magnitude;
}

float vec3::Distance(vec3 otherVec) const {
	vec3 d(otherVec.X - X, otherVec.Y - Y, otherVec.Z - Z);
	return d.Length();
}

float vec3::Dot(vec3 v1, vec3 v2) {
	return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);
}

std::ostream& operator<<(std::ostream & os, const vec3 & v) {
	return os << "(" << v.X << ", " << v.Y << "," << v.Z << ")";
}


bool operator==(const vec3 & lhs, const vec3 & rhs) {
	return (lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == lhs.Z);
}

bool operator!=(const vec3 & lhs, const vec3 & rhs) {
	return !operator==(lhs, rhs);
}
