#include "vec2.h"

vec2::vec2() = default;
vec2::vec2(float x, float y) : X(x), Y(y) {}
vec2::vec2(const vec2 & otherVec) : X(otherVec.X), Y(otherVec.Y) {}

vec2::~vec2() = default;

//Vector addition
vec2 vec2::operator+(const vec2 & otherVec) {
	vec2 temp;
	temp.X = X + otherVec.X;
	temp.Y = Y + otherVec.Y;
	return temp;
}

vec2& vec2::operator+=(const vec2 & otherVec) {
	X += otherVec.X;
	Y += otherVec.Y;
	return *this;
}

vec2 vec2::operator+(float s) {
	vec2 temp;
	temp.X = X + s;
	temp.Y = Y + s;
	return temp;
}

vec2& vec2::operator+=(float s) {
	X += s;
	Y += s;
	return *this;
}


//Vector subtraction
vec2 vec2::operator-(const vec2 & otherVec) {
	vec2 temp;
	temp.X = X - otherVec.X;
	temp.Y = Y - otherVec.Y;
	return temp;
}

vec2& vec2::operator-=(const vec2 & otherVec) {
	X -= otherVec.X;
	Y -= otherVec.Y;
	return *this;
}

vec2 vec2::operator-(float s) {
	vec2 temp;
	temp.X = X - s;
	temp.Y = Y - s;
	return temp;
}

vec2& vec2::operator-=(float s) {
	X -= s;
	Y -= s;
	return *this;
}


//Vector multiplication
vec2 vec2::operator*(float s) {
	vec2 temp;
	temp.X = X * s;
	temp.Y = Y * s;
	return temp;
}

vec2& vec2::operator*=(float s) {
	X *= s;
	Y *= s;
	return *this;
}


//Vector division
vec2 vec2::operator/(float s) {
	vec2 temp;
	temp.X = X / s;
	temp.Y = Y / s;
	return temp;
}

vec2& vec2::operator/=(float s) {
	X /= s;
	Y /= s;
	return *this;
}

//Useful Vector Operations
float vec2::length() const {
	return std::sqrt(X * X + Y * Y);
}

vec2& vec2::normalize() {
	float magnitude = length();
	if (magnitude == 0) return *this;
	return (*this) /= magnitude;
}

float vec2::distance(vec2 otherVec) const {
	vec2 d(otherVec.X - X, otherVec.Y - Y);
	return d.length();
}

float vec2::dot(vec2 v1, vec2 v2) {
	return (v1.X * v2.X) + (v1.Y * v2.Y);
}

float vec2::cross(vec2 v1, vec2 v2) {
	return (v1.X * v2.Y) - (v1.Y * v2.X);
}

std::ostream& operator<<(std::ostream & os, const vec2 & v) {
	return os << "(" << v.X << ", " << v.Y << ")";
}

bool operator<(const vec2 & lhs, const vec2 & rhs) {
	return ((lhs.X < rhs.X) || (lhs.X == rhs.X && lhs.Y < rhs.Y));
}

bool operator>(const vec2 & lhs, const vec2 & rhs) {
	return operator<(rhs, lhs);
}

bool operator==(const vec2 & lhs, const vec2 & rhs) {
	return (lhs.X == rhs.X && lhs.Y == rhs.Y);
}

bool operator!=(const vec2 & lhs, const vec2 & rhs) {
	return !operator==(lhs, rhs);
}

bool operator<=(const vec2 & lhs, const vec2 & rhs) {
	return !operator>(lhs, rhs);
}

bool operator>=(const vec2 & lhs, const vec2 & rhs) {
	return !operator<(lhs, rhs);
}