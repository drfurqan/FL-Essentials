/*********************************************************************************
created:	2014/01/22   08:06AM
filename: 	Fle_Vector2D.cpp
file base:	Fle_Vector2D
file ext:	cpp
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

#include <FLE/Math/Fle_Vector2D.h>

using namespace R3D;

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}
Vector2D::Vector2D(int xx, int yy)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
}
Vector2D::Vector2D(float xx, float yy)
{
	x = xx;
	y = yy;
}
Vector2D::Vector2D(double xx, double yy)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
}
Vector2D::Vector2D(const int f[2])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
}
Vector2D::Vector2D(const float f[2])
{
	x = f[0];
	y = f[1];
}
Vector2D::Vector2D(const double f[2])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
}
Vector2D::Vector2D(const Vector2D &v)
{
	x = v.x;
	y = v.y;
}

void Vector2D::setX(float xx) { x = xx; }
void Vector2D::setY(float yy) { y = yy; }

void Vector2D::set(int xx, int yy)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
}
void Vector2D::set(float xx, float yy)
{
	x = xx;
	y = yy;
}
void Vector2D::set(double xx, double yy)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
}
void Vector2D::set(const int f[2])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
}
void Vector2D::set(const float f[2])
{
	x = f[0];
	y = f[1];
}
void Vector2D::set(const double f[2])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
}
void Vector2D::set(const Vector2D &v)
{
	x = v.x;
	y = v.y;
}
void Vector2D::setZero()
{
	x = 0.0;
	y = 0.0;
}

void Vector2D::get(float& xx, float& yy) const
{
	xx = x;
	yy = y;
}
void Vector2D::get(float f[2])
{
	f[0] = x;
	f[1] = y;
}

const float& Vector2D::X() const { return x; }
const float& Vector2D::Y() const { return y; }
const float& Vector2D::getX() const { return x; }
const float& Vector2D::getY() const { return y; }

/************************************************************************/
/* Operators                                                            */
/************************************************************************/
const Vector2D Vector2D::operator * (const Vector2D &c) const
{
	Vector2D a;
	a.x = this->x * c.x;
	a.y = this->y * c.y;
	return a;
}
const Vector2D Vector2D::operator + (const Vector2D &c) const
{
	Vector2D a;
	a.x = this->x + c.x;
	a.y = this->y + c.y;
	return a;
}
const Vector2D Vector2D::operator - (const Vector2D &c) const
{
	Vector2D a;
	a.x = this->x - c.x;
	a.y = this->y - c.y;
	return a;
}
const Vector2D Vector2D::operator / (const Vector2D &c) const
{
	Vector2D a;
	a.x = this->x / c.x;
	a.y = this->y / c.y;
	return a;
}
const bool Vector2D::operator == (const Vector2D& v) const
{
	return ((std::abs(v.x - x) < 0.000001f) && (std::abs(v.y - y) < 0.000001f));
}
const bool Vector2D::operator < (const Vector2D& v) const
{
	if (x < v.x && y < v.y)
		return true;
	return false;
}
const bool Vector2D::operator > (const Vector2D& v) const
{
	if (x > v.x && y > v.y)
		return true;
	return false;
}
const bool Vector2D::operator >= (const Vector2D& v) const
{
	if (x >= v.x && y >= v.y)
		return true;
	return false;
}
const bool Vector2D::operator <= (const Vector2D& v) const
{
	if (x <= v.x && y <= v.y)
		return true;
	return false;
}
const bool Vector2D::operator != (const Vector2D& v) const
{
	return !(v == *this);
}

const Vector2D& Vector2D::operator = (const Vector2D& v)
{
	x = v.x;
	y = v.y;
	return *this;
}
const Vector2D& Vector2D::operator += (const Vector2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
const Vector2D& Vector2D::operator -= (const Vector2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
const Vector2D& Vector2D::operator *= (const float& s)
{
	x *= s;
	y *= s;
	return *this;
}
const Vector2D& Vector2D::operator /= (const float& s)
{
	const float r = 1.f / s;
	x *= r;
	y *= r;
	return *this;
}
const Vector2D Vector2D::operator * (const float s) const
{
	Vector2D a;
	a.x = x*s;
	a.y = y*s;
	return a;
}
const Vector2D Vector2D::operator + (const float s) const
{
	Vector2D a;
	a.x = x + s;
	a.y = y + s;
	return a;
}
const Vector2D Vector2D::operator - (const float s) const
{
	Vector2D a;
	a.x = x - s;
	a.y = y - s;
	return a;
}
const Vector2D Vector2D::operator / (float s) const
{
	s = 1.f / s;
	Vector2D a;
	a.x = x*s;
	a.y = y*s;
	return a;
}

const bool Vector2D::operator >= (float s) const
{
	if (x >= s && y >= s)
		return true;
	return false;
}
const bool Vector2D::operator <= (float s) const
{
	if (x <= s && y <= s)
		return true;
	return false;
}
const bool Vector2D::operator == (float s) const
{
	//if( x == s && y == s && z == s )
	if ((std::abs(s - x) < 0.000001f) && (std::abs(s - y) < 0.000001f))
		return true;
	return false;
}
const bool Vector2D::operator > (float s) const
{
	if (x > s && y > s)
		return true;
	return false;
}const bool Vector2D::operator < (float s) const
{
	if (x < s && y < s)
		return true;
	return false;
}
void Vector2D::scale(float v)
{
	x *= v;
	y *= v;
}

Vector2D& Vector2D::rotate(float degres)
{
	float s = std::sin(degres * 0.01745329251994329576923690768489f);
	float c = std::cos(degres * 0.01745329251994329576923690768489f);

	float nx = c * x - s * y;
	float ny = s * x + c * y;

	x = nx;
	y = ny;

	return (*this);
}

const Vector2D Vector2D::reflect(const Vector2D& normal) const
{
	return Vector2D(*this - (2.f * (*this).dot(normal) * normal));
}
const float Vector2D::dot(const Vector2D& v) const
{
	return x*v.x + y*v.y;
}
const float Vector2D::length() const
{
	return std::sqrt(this->dot(*this));
}
const float Vector2D::squaredlength() const
{
	return static_cast<float>(x*x + y*y);
}
const float Vector2D::getDistance(const Vector2D& v) const
{
	const Vector2D dif = v - *this;
	return dif.length();
}
const Vector2D Vector2D::getNormalized() const
{
	return (*this) / length();
}
static float __Clamp(float val, float min, float max)
{
	if (val <= min)
		return min;
	else if (val >= max)
		return max;
	else
		return val;
}
const float Vector2D::getAngleBetween(const Vector2D& dest) const
{
	float lenProduct = length() * dest.length();
	if (lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float f = (*this).dot(dest) / lenProduct;
	f = __Clamp(f, -1.f, 1.f);
	return acos(f);
}
const Vector2D Vector2D::abs() const
{
	Vector2D a;
	a.x = std::abs(x);
	a.y = std::abs(y);
	return a;
}
const Vector2D Vector2D::negate() const
{
	Vector2D a;
	a.x = -x;
	a.y = -y;
	return a;
}
void Vector2D::normalize()
{
	float l = length();
	if (l == 1.0f || l == 0.0f)
		return;
	(*this) /= l;
}
void Vector2D::squaredNormalize()
{
	(*this) /= squaredlength();
}

const bool Vector2D::nearlyEquals(const Vector2D& v, const float e) const
{
	return std::abs(x - v.x) < e && std::abs(y - v.y) < e;
}
void Vector2D::reverseDirection()
{
	(*this) = (*this) * -1.0f;
}
const bool Vector2D::isSameDirection(const Vector2D& Vector) const
{
	return (((*this).getNormalized()).dot(Vector.getNormalized()) > 0.0f);
}
const Vector2D Vector2D::getMaxFromTwo(const Vector2D& pnt0, const Vector2D& pnt1)
{
	Vector2D result;
	result.x = (pnt0.x > pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y > pnt1.y) ? pnt0.y : pnt1.y;
	return result;
}
const Vector2D Vector2D::getMinFromTwo(const Vector2D& pnt0, const Vector2D& pnt1)
{
	Vector2D result;
	result.x = (pnt0.x < pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y < pnt1.y) ? pnt0.y : pnt1.y;
	return result;
}

const float Vector2D::getMaxAxis() const
{
	float result = (x > y) ? x : y;
	return result;
}
const float Vector2D::getMinAxis() const
{
	float result = (x < y) ? x : y;
	return result;
}
