#pragma once

#include<math.h>
#include<stdlib.h>
#include<iostream>

class Vec3
{
public:
	Vec3() {};
	Vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	};
	inline float x() { return e[0]; }
	inline float y() { return e[1]; }
	inline float z() { return e[2]; }
	inline float r() { return e[0]; }
	inline float g() { return e[1]; }
	inline float b() { return e[2]; }


	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() { return Vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline Vec3& operator+=(const Vec3 &v2);
	inline Vec3& operator-=(const Vec3 &v2);
	inline Vec3& operator*=(const Vec3 &v2);
	inline Vec3& operator/=(const Vec3 &v2);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	void make_unit_vector();

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float squared_length() const  
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	float e[3];
};


inline Vec3 & Vec3::operator+=(const Vec3 & v2)
{
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];

	return *this;
}

inline Vec3 & Vec3::operator-=(const Vec3 & v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];

	return *this;
}

inline Vec3 & Vec3::operator*=(const Vec3 & v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];

	return *this;
}

inline Vec3 & Vec3::operator/=(const Vec3 & v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];

	return *this;
}

inline Vec3 & Vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;

	return *this;
}

inline Vec3 & Vec3::operator/=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;

	return *this;
}


// Not Vec3:: because for operators in class that 
// instance but here v1 and v2 both are used


inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator- (const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/ (const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline float dot (const Vec3 &v1, const Vec3 &v2)
{
	return (v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) 
{
	return Vec3(
		v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0],
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
	);
}

inline Vec3 operator*(const Vec3 &v1, float t) {
	return Vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline Vec3 operator*(float t, const Vec3 &v1) {
	return Vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline Vec3 operator/(const Vec3 v1, float t) {
	return Vec3(v1.e[0] / t, v1.e[1] / t, v1.e[2] / t);
}

inline void Vec3::make_unit_vector()
{
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline Vec3 unit_vector(Vec3 v)
{
	return v / v.length();
}