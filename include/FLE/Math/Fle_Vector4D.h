#pragma once
#ifndef Fle_Vector4D_h__
#define Fle_Vector4D_h__

/*********************************************************************************
created:	2014/01/24   02:06AM
filename: 	Fle_Vector4D.h
file base:	Fle_Vector4D
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for four dimensional vector.

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

class FL_ESSENTIALS_EXPORT Vector4D
{
public:
	float x, y, z, w;

	Vector4D();
	Vector4D(int xx, int yy, int zz, int ww);
	Vector4D(float xx, float yy, float zz, float ww);
	Vector4D(double xx, double yy, double zz, double ww);
	Vector4D(const int f[4]);
	Vector4D(const float f[4]);
	Vector4D(const double f[4]);
	Vector4D(const Vector4D &v);

	void setX(float xx);
	void setY(float yy);
	void setZ(float zz);
	void setW(float ww);
	void set(int xx, int yy, int zz, int ww);
	void set(float xx, float yy, float zz, float ww);
	void set(double xx, double yy, double zz, double ww);
	void set(const int f[4]);
	void set(const float f[4]);
	void set(const double f[4]);
	void set(const Vector4D &v);
	void setZero();
	void get(float& xx, float& yy, float& zz, float& ww) const;
	void get(float f[4]);

	const float& X() const;
	const float& Y() const;
	const float& Z() const;
	const float& W() const;
	const float& getX() const;
	const float& getY() const;
	const float& getZ() const;
	const float& getW() const;

	float& operator [](long k) { return ((&x)[k]); }
	const float& operator [](long k) const { return ((&x)[k]); }

	const Vector4D operator * (const Vector4D &c) const;
	const Vector4D operator + (const Vector4D &c) const;
	const Vector4D operator - (const Vector4D &c) const;
	const Vector4D operator / (const Vector4D &c) const;

	const bool operator == (const Vector4D& v) const;
	const bool operator <  (const Vector4D& v) const;
	const bool operator >  (const Vector4D& v) const;
	const bool operator >= (const Vector4D& v) const;
	const bool operator <= (const Vector4D& v) const;
	const bool operator != (const Vector4D& v) const;

	const Vector4D& operator =  (const Vector4D& v);
	const Vector4D& operator += (const Vector4D& v);
	const Vector4D& operator -= (const Vector4D& v);
	const Vector4D& operator *= (const float& s);
	const Vector4D& operator /= (const float& s);

	friend inline const Vector4D operator * (const float& s, const Vector4D& v)	{ return v * s; }
	const Vector4D operator * (const float s) const;
	const Vector4D operator + (const float s) const;
	const Vector4D operator - (const float s) const;
	const bool operator >= (float s) const;
	const bool operator <= (float s) const;
	const bool operator == (float s) const;
	const bool operator > (float s) const;
	const bool operator < (float s) const;
	const Vector4D operator / (float s) const;
	const float* ptr() const { return &x; }
	float* ptr() { return &x; }

	void scale(float v);

	const Vector4D cross(const Vector4D& v) const;
	const Vector4D reflect(const Vector4D& normal) const;
	const Vector4D getNormalized() const;
	const Vector4D abs() const;
	const Vector4D negate() const;
	const float dot(const Vector4D& v) const;
	const float getAngleBetween(const Vector4D& dest) const;
	const float length() const;
	const float squaredlength() const;
	const float getDistance(const Vector4D& v) const;
	void normalize();
	void squaredNormalize();
	void reverseDirection();
	const bool isSameDirection(const Vector4D& rVector) const;
	const bool nearlyEquals(const Vector4D& v, const float e = 0.000001f) const;
	static const Vector4D getMaxFromTwo(const Vector4D& pnt0, const Vector4D& pnt1);
	static const Vector4D getMinFromTwo(const Vector4D& pnt0, const Vector4D& pnt1);
	const float getMaxAxis() const;
	const float getMinAxis() const;

	Vector4D& rotateAboutX (float degres);
	Vector4D& rotateAboutY (float degres);
	Vector4D& rotateAboutZ (float degres);
	Vector4D& rotateAboutAxis(float degres, const Vector4D& axis);

	Vector4D& vectorMatrixMultiply(float M[16], float v[4]);
	Vector4D& vectorMatrixMultiply(double M[16], float v[4]);
	Vector4D& vectorMatrixMultiply(float M[16], const Vector4D& p);
	Vector4D& vectorMatrixMultiply(double M[16], const Vector4D& p);

	friend std::ostream& operator << (std::ostream& out, const Vector4D& v)
	{ out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" <<std::endl; return out; }
};

}

#endif // Fle_Vector4D_h__