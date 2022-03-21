#pragma once
#pragma once

#ifndef _VECTOR_2
#define _VECTOR_2

#include <iostream>
#include <cmath>

class vec2 {
public:
	float X;
	float Y;
	vec2();
	vec2(float x, float y);
	vec2(const vec2& otherVec);

	~vec2();

	//Vector addition
	vec2 operator+(const vec2& otherVec);

	vec2& operator+=(const vec2& otherVec);

	vec2 operator+(float s);

	vec2& operator+=(float s);


	//Vector subtraction
	vec2 operator-(const vec2& otherVec);

	vec2& operator-=(const vec2& otherVec);

	vec2 operator-(float s);

	vec2& operator-=(float s);


	//Vector multiplication
	vec2 operator*(float s);

	vec2& operator*=(float s);


	//Vector division
	vec2 operator/(float s);

	vec2& operator/=(float s);

	//Useful Vector Operations
	float length() const;

	vec2& normalize();

	float distance(vec2 otherVec) const;

	static float dot(vec2 v1, vec2 v2);

	static float cross(vec2 v1, vec2 v2);
};

std::ostream& operator<<(std::ostream& os, const vec2& v);

//Vector comperison operators
bool operator<(const vec2& lhs, const vec2& rhs);

bool operator==(const vec2& lhs, const vec2& rhs);

bool operator!=(const vec2& lhs, const vec2& rhs);

bool operator<=(const vec2& lhs, const vec2& rhs);

bool operator>(const vec2& lhs, const vec2& rhs);

bool operator>=(const vec2& lhs, const vec2& rhs);

#endif