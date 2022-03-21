#pragma once

#include <iostream>
#include <cmath>

class vec3 {
public:
	float X;
	float Y;
	float Z;


	vec3();
	vec3(float x, float y, float z);
	vec3(const vec3& otherVec);

	~vec3();

	//Vector addition
	vec3 operator+(const vec3& otherVec);

	vec3& operator+=(const vec3& otherVec);

	vec3 operator+(float s);

	vec3& operator+=(float s);


	//Vector subtraction
	vec3 operator-(const vec3& otherVec);

	vec3& operator-=(const vec3& otherVec);

	vec3 operator-(float s);

	vec3& operator-=(float s);


	//Vector multiplication
	vec3 operator*(float s);

	vec3& operator*=(float s);


	//Vector division
	vec3 operator/(float s);

	vec3& operator/=(float s);

	//Useful Vector Operations
	float Length() const;

	vec3& Normalize();

	float Distance(vec3 otherVec) const;

	static float Dot(vec3 v1, vec3 v2);
};

std::ostream& operator<<(std::ostream& os, const vec3& v);

//Vector comperison operators
bool operator==(const vec3& lhs, const vec3& rhs);

bool operator!=(const vec3& lhs, const vec3& rhs);
