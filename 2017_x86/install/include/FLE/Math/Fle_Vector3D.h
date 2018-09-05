#pragma once
#ifndef Fle_Vector3D_h__
#define Fle_Vector3D_h__

/*********************************************************************************
created:	2014/01/23   01:06AM
filename: 	Fle_Vector3D.h
file base:	Fle_Vector3D
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for three dimensional vector.

/**********************************************************************************
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <ostream>
#include <iostream>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Vector3D
{
public:
	float x, y, z;

	Vector3D();
	Vector3D(const int xx, const int yy, const int zz);
	Vector3D(const float xx, const float yy, const float zz);
	Vector3D(const double xx, const double yy, const double zz);
	Vector3D(const int f[3]);
	Vector3D(const float f[3]);
	Vector3D(const double f[3]);
	Vector3D(const Vector3D& v);

	void setX(const float xx);
	void setY(const float yy);
	void setZ(const float zz);
	void set(const int xx, const int yy, const int zz);
	void set(const float xx, const float yy, const float zz);
	void set(const double xx, const double yy, const double zz);
	void set(const int f[3]);
	void set(const float f[3]);
	void set(const double f[3]);
	void set(const Vector3D& v);
	void setZero();
	void get(float& xx, float& yy, float& zz) const;
	void get(float f[3]) const;

	const float& X() const;
	const float& Y() const;
	const float& Z() const;
	const float& getX() const;
	const float& getY() const;
	const float& getZ() const;

	void print();

	float& operator [](long k) { return ((&x)[k]); }
	const float& operator [](long k) const { return ((&x)[k]); }

	const Vector3D operator * (const Vector3D& c) const;
	const Vector3D operator + (const Vector3D& c) const;
	const Vector3D operator - (const Vector3D& c) const;
	const Vector3D operator / (const Vector3D& c) const;

	const bool operator == (const Vector3D& v) const;
	const bool operator <  (const Vector3D& v) const;
	const bool operator >  (const Vector3D& v) const;
	const bool operator >= (const Vector3D& v) const;
	const bool operator <= (const Vector3D& v) const;
	const bool operator != (const Vector3D& v) const;

	const Vector3D& operator =  (const Vector3D& v);
	const Vector3D& operator += (const Vector3D& v);
	const Vector3D& operator -= (const Vector3D& v);
	const Vector3D& operator *= (const float& s);
	const Vector3D& operator /= (const float& s);

	friend inline const Vector3D operator * (const float& s, const Vector3D& v) { return v * s; }
	const Vector3D operator * (const float s) const;
	const Vector3D operator + (const float s) const;
	const Vector3D operator - (const float s) const;
	const bool operator >= (const float s) const;
	const bool operator <= (const float s) const;
	const bool operator == (const float s) const;
	const bool operator != (const float s) const;
	const bool operator > (const float s) const;
	const bool operator < (const float s) const;
	const Vector3D operator / (const float s) const;
	const float* ptr() const { return &x; }
	float* ptr() { return &x; }

	void scale(const float v);

	const Vector3D operator ^ (const Vector3D& v) const // cross product operator
	{
		return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
	}
	const Vector3D operator ~ () const
	{
		return (*this) * (1.0f / length());
	}

	const Vector3D cross(const Vector3D& v) const;
	const Vector3D reflect(const Vector3D& normal) const;
	const Vector3D getNormalized() const;
	const Vector3D abs() const;
	const Vector3D negate() const;
	const float dot(const Vector3D& v) const;
	const float getAngleBetween(const Vector3D& dest) const;
	const float length() const;
	const float squaredlength() const;
	const float getDistance(const Vector3D& v) const;
	void normalize();
	void squaredNormalize();
	void reverseDirection();
	const bool isSameDirection(const Vector3D& rVector) const;
	const bool nearlyEquals(const Vector3D& v, const float e = 0.000001f) const;
	static const Vector3D getMaxFromTwo(const Vector3D& pnt0, const Vector3D& pnt1);
	static const Vector3D getMinFromTwo(const Vector3D& pnt0, const Vector3D& pnt1);
	const float getMaxAxis() const;
	const float getMinAxis() const;

	Vector3D& rotateAboutX(const float degres);
	Vector3D& rotateAboutY(const float degres);
	Vector3D& rotateAboutZ(const float degres);
	Vector3D& rotateAboutAxis(const float degres, const Vector3D& axis);

	Vector3D& vectorMatrixMultiply(const float M[16], const float v[4]);
	Vector3D& vectorMatrixMultiply(const double M[16], const float v[4]);
	Vector3D& vectorMatrixMultiply(const float M[16], const Vector3D& p);
	Vector3D& vectorMatrixMultiply(const double M[16], const Vector3D& p);

	friend std::ostream& operator << (std::ostream& out, const Vector3D& v)
	{
		out << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl; return out;
	}
};

}

#endif // Fle_Vector3D_h__