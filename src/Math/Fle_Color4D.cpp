/*********************************************************************************
created:	2014/01/21   10:06AM
filename: 	Fle_Color4D.cpp
file base:	Fle_Color4D
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for RGBA color.

/**********************************************************************************
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Color4D.h>

using namespace R3D;

Color4D::Color4D()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}
Color4D::Color4D(int red, int green, int blue, int alpha)
{
	r = static_cast<float>(red);
	g = static_cast<float>(green);
	b = static_cast<float>(blue);
	a = static_cast<float>(alpha);
}
Color4D::Color4D(float red, float green, float blue, float alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
Color4D::Color4D(double red, double green, double blue, double alpha)
{
	r = static_cast<float>(red);
	g = static_cast<float>(green);
	b = static_cast<float>(blue);
	a = static_cast<float>(alpha);
}
Color4D::Color4D(const int f[4])
{
	r = static_cast<float>(f[0]);
	g = static_cast<float>(f[1]);
	b = static_cast<float>(f[2]);
	a = static_cast<float>(f[3]);
}
Color4D::Color4D(const float f[4])
{
	r = f[0];
	g = f[1];
	b = f[2];
	a = f[3];
}
Color4D::Color4D(const Color4D &v)
{
	r = v.r;
	g = v.g;
	b = v.b;
	a = v.a;
}

void Color4D::setR(float red) { r = red; }
void Color4D::setG(float green) { g = green; }
void Color4D::setB(float blue) { b = blue; }
void Color4D::setA(float alpha) { a = alpha; }

void Color4D::set(int red, int green, int blue, int alpha)
{
	r = static_cast<float>(red);
	g = static_cast<float>(green);
	b = static_cast<float>(blue);
	a = static_cast<float>(alpha);
}
void Color4D::set(float red, float green, float blue, float alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
void Color4D::set(double red, double green, double blue, double alpha)
{
	r = static_cast<float>(red);
	g = static_cast<float>(green);
	b = static_cast<float>(blue);
	a = static_cast<float>(alpha);
}
void Color4D::set(const int f[4])
{
	r = static_cast<float>(f[0]);
	g = static_cast<float>(f[1]);
	b = static_cast<float>(f[2]);
	a = static_cast<float>(f[3]);
}
void Color4D::set(const float f[4])
{
	r = f[0];
	g = f[1];
	b = f[2];
	a = f[3];
}
void Color4D::set(const Color4D &v)
{
	r = v.r;
	g = v.g;
	b = v.b;
	a = v.a;
}
void Color4D::setBlack()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}
void Color4D::setWhite()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}
void Color4D::setRed()
{
	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}
void Color4D::setGreen()
{
	r = 0.0f;
	g = 1.0f;
	b = 0.0f;
	a = 1.0f;
}
void Color4D::setBlue()
{
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	a = 1.0f;
}
void Color4D::setDeepSkyBlue()
{
	r = 0.0f;
	g = 0.749f;
	b = 1.0f;
	a = 1.0f;
}
void Color4D::setYellow()
{
	r = 1.0f;
	g = 1.0f;
	b = 0.0f;
	a = 1.0f;
}
void Color4D::setCyan()
{
	r = 0.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}
void Color4D::setPurple()
{
	r = 0.62745f;
	g = 0.12549f;
	b = 0.94117f;
	a = 1.0f;
}
void Color4D::setOrange()
{
	r = 1.0f;
	g = 0.64705f;
	b = 0.0f;
	a = 1.0f;
}

void Color4D::setGrey(float shade) { r = g = b = a = shade; }

void Color4D::get(float& red, float& green, float& blue, float& alpha) const
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void Color4D::get(float f[4])
{
	f[0] = r;
	f[1] = g;
	f[2] = b;
	f[3] = a;
}

const float& Color4D::R() const { return r; }
const float& Color4D::G() const { return g; }
const float& Color4D::B() const { return b; }
const float& Color4D::A() const { return a; }
const float& Color4D::getR() const { return r; }
const float& Color4D::getG() const { return g; }
const float& Color4D::getB() const { return b; }
const float& Color4D::getA() const { return a; }

void Color4D::print() { std::cout << "(" << r << ", " << g << ", " << b << ", " << a << ")" << std::endl; }

/************************************************************************/
/* Operators                                                            */
/************************************************************************/
const Color4D Color4D::operator * (const Color4D &c) const
{
	Color4D a;
	a.r = this->r * c.r;
	a.g = this->g * c.g;
	a.b = this->b * c.b;
	a.a = this->a * c.a;
	return a;
}
const Color4D Color4D::operator + (const Color4D &c) const
{
	Color4D a;
	a.r = this->r + c.r;
	a.g = this->g + c.g;
	a.b = this->b + c.b;
	a.a = this->a + c.a;
	return a;
}
const Color4D Color4D::operator - (const Color4D &c) const
{
	Color4D a;
	a.r = this->r - c.r;
	a.g = this->g - c.g;
	a.b = this->b - c.b;
	a.a = this->a - c.a;
	return a;
}
const Color4D Color4D::operator / (const Color4D &c) const
{
	Color4D a;
	a.r = this->r / c.r;
	a.g = this->g / c.g;
	a.b = this->b / c.b;
	a.a = this->a / c.a;
	return a;
}

const bool Color4D::operator == (const Color4D& v) const
{
	return ((std::abs(v.r - r) < 0.000001f) && (std::abs(v.g - g) < 0.000001f) && (std::abs(v.b - b) < 0.000001f) && (std::abs(v.a - a) < 0.000001f));
}
const bool Color4D::operator < (const Color4D& v) const
{
	if (r < v.r && g < v.g && b < v.b && a < v.a)
		return true;
	return false;
}
const bool Color4D::operator > (const Color4D& v) const
{
	if (r > v.r && g > v.g && b > v.b && a > v.a)
		return true;
	return false;
}
const bool Color4D::operator >= (const Color4D& v) const
{
	if (r >= v.r && g >= v.g && b >= v.b && a >= v.a)
		return true;
	return false;
}
const bool Color4D::operator <= (const Color4D& v) const
{
	if (r <= v.r && g <= v.g && b <= v.b && a <= v.a)
		return true;
	return false;
}
const bool Color4D::operator != (const Color4D& v) const
{
	return !(v == *this);
}

const Color4D& Color4D::operator = (const Color4D& v)
{
	r = v.r;
	g = v.g;
	b = v.b;
	a = v.a;
	return *this;
}
const Color4D& Color4D::operator += (const Color4D& v)
{
	r += v.r;
	g += v.g;
	b += v.b;
	a += v.a;
	return *this;
}
const Color4D& Color4D::operator -= (const Color4D& v)
{
	r -= v.r;
	g -= v.g;
	b -= v.b;
	a -= v.a;
	return *this;
}
const Color4D& Color4D::operator *= (const float& s)
{
	r *= s;
	g *= s;
	b *= s;
	a *= s;
	return *this;
}
const Color4D& Color4D::operator /= (const float& s)
{
	const float d = 1 / s;
	r *= d;
	g *= d;
	b *= d;
	a *= d;
	return *this;
}
const Color4D Color4D::operator * (const float s) const
{
	Color4D d;
	d.r = r*s;
	d.g = g*s;
	d.b = b*s;
	d.a = a*s;
	return d;
}
const Color4D Color4D::operator + (const float s) const
{
	Color4D d;
	d.r = r + s;
	d.g = g + s;
	d.b = b + s;
	d.a = a + s;
	return d;
}
const Color4D Color4D::operator - (const float s) const
{
	Color4D d;
	d.r = r - s;
	d.g = g - s;
	d.b = b - s;
	d.a = a - s;
	return d;
}
const Color4D Color4D::operator / (float s) const
{
	s = 1 / s;
	Color4D d;
	d.r = r*s;
	d.g = g*s;
	d.b = b*s;
	d.a = a*s;
	return d;
}

const bool Color4D::operator >= (float s) const
{
	if (r >= s && g >= s && b >= s && a >= s)
		return true;
	return false;
}
const bool Color4D::operator <= (float s) const
{
	if (r <= s && g <= s && b <= s && a <= s)
		return true;
	return false;
}
const bool Color4D::operator == (float s) const
{
	if ((std::abs(s - r) < 0.000001f) && (std::abs(s - g) < 0.000001f) && (std::abs(s - b) < 0.000001f) && (std::abs(s - a) < 0.000001f))
		return true;
	return false;
}
const bool Color4D::operator > (float s) const
{
	if (r > s && g > s && b > s && a > s)
		return true;
	return false;
}const bool Color4D::operator < (float s) const
{
	if (r < s && g < s && b < s && a < s)
		return true;
	return false;
}
void Color4D::scale(float v)
{
	r *= v;
	g *= v;
	b *= v;
	a *= v;
}

const float Color4D::dot(const Color4D& v) const
{
	return r*v.r + g*v.g + b*v.b + a*v.a;
}
const bool Color4D::nearlyEquals(const Color4D& v, const float e) const
{
	return std::abs(r - v.r) < e && std::abs(g - v.g) < e && std::abs(b - v.b) < e && std::abs(a - v.a) < e;
}
const Color4D Color4D::getMaxFromTwo(const Color4D& pnt0, const Color4D& pnt1)
{
	Color4D result;
	result.r = (pnt0.r > pnt1.r) ? pnt0.r : pnt1.r;
	result.g = (pnt0.g > pnt1.g) ? pnt0.g : pnt1.g;
	result.b = (pnt0.b > pnt1.b) ? pnt0.b : pnt1.b;
	result.a = (pnt0.a > pnt1.a) ? pnt0.a : pnt1.a;
	return result;
}
const Color4D Color4D::getMinFromTwo(const Color4D& pnt0, const Color4D& pnt1)
{
	Color4D result;
	result.r = (pnt0.r < pnt1.r) ? pnt0.r : pnt1.r;
	result.g = (pnt0.g < pnt1.g) ? pnt0.g : pnt1.g;
	result.b = (pnt0.b < pnt1.b) ? pnt0.b : pnt1.b;
	result.a = (pnt0.a < pnt1.a) ? pnt0.a : pnt1.a;
	return result;
}
const float Color4D::getMax() const
{
	float result = 0;
	result = (r > g) ? r : g;
	result = (b > result) ? b : result;
	return (float)result;
}
const float Color4D::getMin() const
{
	float result = 0;
	result = (r < g) ? r : g;
	result = (b < result) ? b : result;
	return (float)result;
}

Color4D& Color4D::Clamp0To1()
{
	if (r > 1.0f)
		r = 1.0f;
	if (r < 0.0f)
		r = 0.0f;

	if (g > 1.0f)
		g = 1.0f;
	if (g < 0.0f)
		g = 0.0f;

	if (b > 1.0f)
		b = 1.0f;
	if (b < 0.0f)
		b = 0.0f;

	if (a > 1.0f)
		a = 1.0f;
	if (a < 0.0f)
		a = 0.0f;

	return (*this);
}