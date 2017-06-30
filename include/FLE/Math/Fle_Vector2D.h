#pragma once
#ifndef Fle_Vector2D_h__
#define Fle_Vector2D_h__

/*********************************************************************************
created:	2014/01/22   08:06AM
filename: 	Fle_Vector2D.h
file base:	Fle_Vector2D
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for two dimensional vector.

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

class FL_ESSENTIALS_EXPORT Vector2D
{
public:
	float x, y;

	Vector2D();
	Vector2D(int xx, int yy);
	Vector2D(float xx, float yy);
	Vector2D(double xx, double yy);
	Vector2D(const int f[2]);
	Vector2D(const float f[2]);
	Vector2D(const double f[2]);
	Vector2D(const Vector2D &v);

	void setX(float xx);
	void setY(float yy);
	void set(int xx, int yy);
	void set(float xx, float yy);
	void set(double xx, double yy);
	void set(const int f[2]);
	void set(const float f[2]);
	void set(const double f[2]);
	void set(const Vector2D &v);
	void setZero();
	void get(float& xx, float& yy) const;
	void get(float f[2]);

	const float& X() const;
	const float& Y() const;
	const float& getX() const;
	const float& getY() const;

	void print();

	float& operator [](long k) { return ((&x)[k]); }
	const float& operator [](long k) const { return ((&x)[k]); }

	const Vector2D operator * (const Vector2D &c) const;
	const Vector2D operator + (const Vector2D &c) const;
	const Vector2D operator - (const Vector2D &c) const;
	const Vector2D operator / (const Vector2D &c) const;

	const bool operator == (const Vector2D& v) const;
	const bool operator <  (const Vector2D& v) const;
	const bool operator >  (const Vector2D& v) const;
	const bool operator >= (const Vector2D& v) const;
	const bool operator <= (const Vector2D& v) const;
	const bool operator != (const Vector2D& v) const;

	const Vector2D& operator =  (const Vector2D& v);
	const Vector2D& operator += (const Vector2D& v);
	const Vector2D& operator -= (const Vector2D& v);
	const Vector2D& operator *= (const float& s);
	const Vector2D& operator /= (const float& s);

	friend inline const Vector2D operator * (const float& s, const Vector2D& v) { return v * s; }
	const Vector2D operator * (const float s) const;
	const Vector2D operator + (const float s) const;
	const Vector2D operator - (const float s) const;
	const bool operator >= (float s) const;
	const bool operator <= (float s) const;
	const bool operator == (float s) const;
	const bool operator > (float s) const;
	const bool operator < (float s) const;
	const Vector2D operator / (float s) const;
	const float* ptr() const { return &x; }
	float* ptr() { return &x; }

	void scale(float v);

	Vector2D& rotate(float degres);

	const Vector2D reflect(const Vector2D& normal) const;
	const Vector2D getNormalized() const;
	const Vector2D abs() const;
	const Vector2D negate() const;
	const float dot(const Vector2D& v) const;
	const float getAngleBetween(const Vector2D& dest) const;
	const float length() const;
	const float squaredlength() const;
	const float getDistance(const Vector2D& v) const;
	void normalize();
	void squaredNormalize();
	void reverseDirection();
	const bool isSameDirection(const Vector2D& rVector) const;
	const bool nearlyEquals(const Vector2D& v, const float e = 0.000001f) const;
	static const Vector2D getMaxFromTwo(const Vector2D& pnt0, const Vector2D& pnt1);
	static const Vector2D getMinFromTwo(const Vector2D& pnt0, const Vector2D& pnt1);
	const float getMaxAxis() const;
	const float getMinAxis() const;

	friend std::ostream& operator << (std::ostream& out, const Vector2D& v)
	{
		out << "(" << v.x << ", " << v.y << ")" << std::endl; return out;
	}

};

}

#endif // Fle_Vector2D_h__