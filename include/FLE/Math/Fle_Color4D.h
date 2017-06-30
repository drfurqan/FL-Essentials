#pragma once
#ifndef Fle_Color4D_h__
#define Fle_Color4D_h__

/*********************************************************************************
created:	2014/01/21   10:06AM
filename: 	Fle_Color4D.h
file base:	Fle_Color4D
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for RGBA color.

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

class FL_ESSENTIALS_EXPORT Color4D
{
public:
	float r, g, b, a;

	Color4D();
	Color4D(int red, int green, int blue, int alpha = 1);
	Color4D(float red, float green, float blue, float alpha = 1.0f);
	Color4D(double red, double green, double blue, double alpha = 1.0);
	Color4D(const int f[4]);
	Color4D(const float f[4]);
	Color4D(const Color4D &v);

	void setR(float red);
	void setG(float green);
	void setB(float blue);
	void setA(float alpha);
	void set(int red, int green, int blue, int alpha = 1);
	void set(float red, float green, float blue, float alpha = 1.0f);
	void set(double red, double green, double blue, double alpha = 1.0);
	void set(const int f[4]);
	void set(const float f[4]);
	void set(const Color4D &v);
	void setBlack();
	void setWhite();
	void setRed();
	void setGreen();
	void setBlue();
	void setDeepSkyBlue();
	void setYellow();
	void setCyan();
	void setPurple();
	void setOrange();
	void setGrey(float shade);
	void get(float& red, float& green, float& blue, float& alpha) const;
	void get(float f[4]);

	const float& R() const;
	const float& G() const;
	const float& B() const;
	const float& A() const;
	const float& getR() const;
	const float& getG() const;
	const float& getB() const;
	const float& getA() const;

	void print();

	float& operator [](long k) { return ((&r)[k]); }
	const float& operator [](long k) const { return ((&r)[k]); }

	const Color4D operator * (const Color4D &c) const;
	const Color4D operator + (const Color4D &c) const;
	const Color4D operator - (const Color4D &c) const;
	const Color4D operator / (const Color4D &c) const;

	const bool operator == (const Color4D& v) const;
	const bool operator <  (const Color4D& v) const;
	const bool operator >  (const Color4D& v) const;
	const bool operator >= (const Color4D& v) const;
	const bool operator <= (const Color4D& v) const;
	const bool operator != (const Color4D& v) const;

	const Color4D& operator =  (const Color4D& v);
	const Color4D& operator += (const Color4D& v);
	const Color4D& operator -= (const Color4D& v);
	const Color4D& operator *= (const float& s);
	const Color4D& operator /= (const float& s);

	friend inline const Color4D operator * (const float& s, const Color4D& v) { return v * s; }
	const Color4D operator * (const float s) const;
	const Color4D operator + (const float s) const;
	const Color4D operator - (const float s) const;
	const bool operator >= (float s) const;
	const bool operator <= (float s) const;
	const bool operator == (float s) const;
	const bool operator > (float s) const;
	const bool operator < (float s) const;
	const Color4D operator / (float s) const;
	const float* ptr() const { return &r; }
	float* ptr() { return &r; }

	void scale(float v);

	const float dot(const Color4D& v) const;
	const bool nearlyEquals(const Color4D& v, const float e = 0.000001f) const;
	static const Color4D getMaxFromTwo(const Color4D& pnt0, const Color4D& pnt1);
	static const Color4D getMinFromTwo(const Color4D& pnt0, const Color4D& pnt1);
	const float getMax() const;
	const float getMin() const;

	Color4D lerp(const Color4D& c, float factor)
	{
		return (*this)*(1.0f - factor) + c*factor;
	}

	Color4D& Clamp0To1();

	friend std::ostream& operator << (std::ostream& out, const Color4D& v)
	{
		out << "(" << v.r << ", " << v.g << ", " << v.b << ", " << v.a << ")" << std::endl; return out;
	}
};

}

#endif // Fle_Color4D_h__