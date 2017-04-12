/*********************************************************************************
created:	2014/01/24   02:06AM
filename: 	Fle_Vector4D.cpp
file base:	Fle_Vector4D
file ext:	cpp
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

#include "Fle_Vector4D.h"

using namespace R3D;

Vector4D::Vector4D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}
Vector4D::Vector4D(int xx, int yy, int zz, int ww)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
	w = static_cast<float>(ww);
}
Vector4D::Vector4D(float xx, float yy, float zz, float ww)
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}
Vector4D::Vector4D(double xx, double yy, double zz, double ww)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
	w = static_cast<float>(ww);
}
Vector4D::Vector4D(const int f[4])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
	w = static_cast<float>(f[3]);
}
Vector4D::Vector4D(const float f[4])
{
	x = f[0];
	y = f[1];
	z = f[2];
	w = f[3];
}
Vector4D::Vector4D(const double f[4])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
	w = static_cast<float>(f[3]);
}
Vector4D::Vector4D(const Vector4D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

void Vector4D::setX(float xx) { x = xx; }
void Vector4D::setY(float yy) { y = yy; }
void Vector4D::setZ(float zz) { z = zz; }
void Vector4D::setW(float ww) { w = ww; }

void Vector4D::set(int xx, int yy, int zz, int ww)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
	w = static_cast<float>(ww);
}
void Vector4D::set(float xx, float yy, float zz, float ww)
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}
void Vector4D::set(double xx, double yy, double zz, double ww)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
	w = static_cast<float>(ww);
}
void Vector4D::set(const int f[4])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
	w = static_cast<float>(f[3]);
}
void Vector4D::set(const float f[4])
{
	x = f[0];
	y = f[1];
	z = f[2];
	w = f[3];
}
void Vector4D::set(const double f[4])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
	w = static_cast<float>(f[3]);
}
void Vector4D::set(const Vector4D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}
void Vector4D::setZero()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

void Vector4D::get(float& xx, float& yy, float& zz, float& ww) const
{
	xx = x;
	yy = y;
	zz = z;
	ww = w;
}
void Vector4D::get(float f[4])
{
	f[0] = x;
	f[1] = y;
	f[2] = z;
	f[3] = w;
}

const float& Vector4D::X() const { return x; }
const float& Vector4D::Y() const { return y; }
const float& Vector4D::Z() const { return z; }
const float& Vector4D::W() const { return w; }

const float& Vector4D::getX() const { return x; }
const float& Vector4D::getY() const { return y; }
const float& Vector4D::getZ() const { return z; }
const float& Vector4D::getW() const { return w; }

/************************************************************************/
/* Operators                                                            */
/************************************************************************/
const Vector4D Vector4D::operator * (const Vector4D &c) const
{
	Vector4D a;
	a.x = this->x * c.x;
	a.y = this->y * c.y;
	a.z = this->z * c.z;
	a.w = this->w * c.w;
	return a;
}
const Vector4D Vector4D::operator + (const Vector4D &c) const
{
	Vector4D a;
	a.x = this->x + c.x;
	a.y = this->y + c.y;
	a.z = this->z + c.z;
	a.w = this->w + c.w;
	return a;
}
const Vector4D Vector4D::operator - (const Vector4D &c) const
{
	Vector4D a;
	a.x = this->x - c.x;
	a.y = this->y - c.y;
	a.z = this->z - c.z;
	a.w = this->w - c.w;
	return a;
}
const Vector4D Vector4D::operator / (const Vector4D &c) const
{
	Vector4D a;
	a.x = this->x / c.x;
	a.y = this->y / c.y;
	a.z = this->z / c.z;
	a.w = this->w / c.w;
	return a;
}
const bool Vector4D::operator == (const Vector4D& v) const
{
	return ((std::abs(v.x - x) < 0.000001f) && (std::abs(v.y - y) < 0.000001f) && (std::abs(v.z - z) < 0.000001f) && (std::abs(v.w - w) < 0.000001f));
}
const bool Vector4D::operator < (const Vector4D& v) const
{
	if (x < v.x && y < v.y && z < v.z && w < v.w)
		return true;
	return false;
}
const bool Vector4D::operator > (const Vector4D& v) const
{
	if (x > v.x && y > v.y && z > v.z && w > v.w)
		return true;
	return false;
}
const bool Vector4D::operator >= (const Vector4D& v) const
{
	if (x >= v.x && y >= v.y && z >= v.z && w >= v.w)
		return true;
	return false;
}
const bool Vector4D::operator <= (const Vector4D& v) const
{
	if (x <= v.x && y <= v.y && z <= v.z && w <= v.w)
		return true;
	return false;
}
const bool Vector4D::operator != (const Vector4D& v) const
{
	return !(v == *this);
}

const Vector4D& Vector4D::operator = (const Vector4D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
const Vector4D& Vector4D::operator += (const Vector4D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
const Vector4D& Vector4D::operator -= (const Vector4D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}
const Vector4D& Vector4D::operator *= (const float& s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}
const Vector4D& Vector4D::operator /= (const float& s)
{
	const float r = 1.f / s;
	x *= r;
	y *= r;
	z *= r;
	w *= r;
	return *this;
}
const Vector4D Vector4D::operator * (const float s) const
{
	Vector4D a;
	a.x = x*s;
	a.y = y*s;
	a.z = z*s;
	a.w = w*s;
	return a;
}
const Vector4D Vector4D::operator + (const float s) const
{
	Vector4D a;
	a.x = x + s;
	a.y = y + s;
	a.z = z + s;
	a.w = w + s;
	return a;
}
const Vector4D Vector4D::operator - (const float s) const
{
	Vector4D a;
	a.x = x - s;
	a.y = y - s;
	a.z = z - s;
	a.w = w - s;
	return a;
}
const Vector4D Vector4D::operator / (float s) const
{
	s = 1.f / s;
	Vector4D a;
	a.x = x*s;
	a.y = y*s;
	a.z = z*s;
	a.w = w*s;
	return a;
}

const bool Vector4D::operator >= (float s) const
{
	if (x >= s && y >= s && z >= s && w >= s)
		return true;
	return false;
}
const bool Vector4D::operator <= (float s) const
{
	if (x <= s && y <= s && z <= s && w <= s)
		return true;
	return false;
}
const bool Vector4D::operator == (float s) const
{
	//if( x == s && y == s && z == s )
	if ((std::abs(s - x) < 0.000001f) && (std::abs(s - y) < 0.000001f) && (std::abs(s - z) < 0.000001f) && (std::abs(s - w) < 0.000001f))
		return true;
	return false;
}
const bool Vector4D::operator > (float s) const
{
	if (x > s && y > s && z > s && w > s)
		return true;
	return false;
}const bool Vector4D::operator < (float s) const
{
	if (x < s && y < s && z < s && w < s)
		return true;
	return false;
}
void Vector4D::scale(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;
}
const Vector4D Vector4D::cross(const Vector4D& v) const
{
	Vector4D a;
	a.x = y*v.z - z*v.y;
	a.y = z*v.x - x*v.z;
	a.z = x*v.y - y*v.x;
	return a;
}
const float Vector4D::dot(const Vector4D& v) const
{
	return x*v.x + y*v.y + z*v.z;
}
const float Vector4D::length() const
{
	return std::sqrt(this->dot(*this));
}
const float Vector4D::squaredlength() const
{
	return static_cast<float>(x*x + y*y + z*z);
}
const float Vector4D::getDistance(const Vector4D& v) const
{
	const Vector4D dif = v - *this;
	return dif.length();
}
const Vector4D Vector4D::getNormalized() const
{
	return (*this) / length();
}
const Vector4D Vector4D::reflect(const Vector4D& normal) const
{
	return Vector4D(*this - (normal * 2 * (*this).dot(normal)));
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
const float Vector4D::getAngleBetween(const Vector4D& dest) const
{
	float lenProduct = length() * dest.length();
	if (lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float f = (*this).dot(dest) / lenProduct;
	f = __Clamp(f, (float)-1.0, (float)1.0);
	return acos(f);
}
const Vector4D Vector4D::abs() const
{
	Vector4D a;
	a.x = std::abs((*this).x);
	a.y = std::abs((*this).y);
	a.z = std::abs((*this).z);
	a.w = std::abs((*this).w);
	return a;
}
const Vector4D Vector4D::negate() const
{
	Vector4D a;
	a.x = -((*this).x);
	a.y = -((*this).y);
	a.z = -((*this).z);
	a.w = -((*this).w);
	return a;
}
void Vector4D::normalize()
{
	(*this) /= length();
}
void Vector4D::squaredNormalize()
{
	(*this) /= squaredlength();
}
const bool Vector4D::nearlyEquals(const Vector4D& v, const float e) const
{
	return std::abs(x - v.x) < e && std::abs(y - v.y) < e && std::abs(z - v.z) < e;
}
void Vector4D::reverseDirection()
{
	(*this) = (*this) * -1.0f;
}
const bool Vector4D::isSameDirection(const Vector4D& Vector) const
{
	return (((*this).getNormalized()).dot(Vector.getNormalized()) > 0.0f);
}
const Vector4D Vector4D::getMaxFromTwo(const Vector4D& pnt0, const Vector4D& pnt1)
{
	Vector4D result;
	result.x = (pnt0.x > pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y > pnt1.y) ? pnt0.y : pnt1.y;
	result.z = (pnt0.z > pnt1.z) ? pnt0.z : pnt1.z;
	result.w = (pnt0.w > pnt1.w) ? pnt0.w : pnt1.w;
	return result;
}
const Vector4D Vector4D::getMinFromTwo(const Vector4D& pnt0, const Vector4D& pnt1)
{
	Vector4D result;
	result.x = (pnt0.x < pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y < pnt1.y) ? pnt0.y : pnt1.y;
	result.z = (pnt0.z < pnt1.z) ? pnt0.z : pnt1.z;
	result.w = (pnt0.w < pnt1.w) ? pnt0.w : pnt1.w;
	return result;
}
const float Vector4D::getMaxAxis() const
{
	float result = 0;
	result = (x > y) ? x : y;
	result = (z > result) ? z : result;
	return result;
}
const float Vector4D::getMinAxis() const
{
	float result = 0;
	result = (x < y) ? x : y;
	result = (z < result) ? z : result;
	return result;
}

Vector4D& Vector4D::rotateAboutX(float degres)
{
	if (degres == 0.0f) return (*this);

	float s = std::sin(degres * 0.01745329251994329576923690768489f);
	float c = std::cos(degres * 0.01745329251994329576923690768489f);

	float ny = c * y - s * z;
	float nz = c * z + s * y;

	y = ny;
	z = nz;
	return (*this);
}
Vector4D& Vector4D::rotateAboutY(float degres)
{
	if (degres == 0.0f) return (*this);

	float s = std::sin(degres * 0.01745329251994329576923690768489f);
	float c = std::cos(degres * 0.01745329251994329576923690768489f);

	float nx = c * x + s * z;
	float nz = c * z - s * x;

	x = nx;
	z = nz;
	return (*this);
}
Vector4D& Vector4D::rotateAboutZ(float degres)
{
	if (degres == 0.0f) return (*this);

	float s = std::sin(degres * 0.01745329251994329576923690768489f);
	float c = std::cos(degres * 0.01745329251994329576923690768489f);

	float nx = c * x - s * y;
	float ny = c * y + s * x;

	x = nx;
	y = ny;
	return (*this);
}

Vector4D& Vector4D::rotateAboutAxis(float degres, const Vector4D& axis)
{
	if (degres == 0.0f) return (*this);

	float s = std::sin(degres * 0.01745329251994329576923690768489f);
	float c = std::cos(degres * 0.01745329251994329576923690768489f);
	float k = 1.0F - c;

	float nx = x * (c + k * axis.x * axis.x) + y * (k * axis.x * axis.y - s * axis.z)
		+ z * (k * axis.x * axis.z + s * axis.y);
	float ny = x * (k * axis.x * axis.y + s * axis.z) + y * (c + k * axis.y * axis.y)
		+ z * (k * axis.y * axis.z - s * axis.x);
	float nz = x * (k * axis.x * axis.z - s * axis.y) + y * (k * axis.y * axis.z + s * axis.x)
		+ z * (c + k * axis.z * axis.z);

	x = nx;
	y = ny;
	z = nz;
	return (*this);
}

Vector4D& Vector4D::vectorMatrixMultiply(double M[16], float v[4])
{
	float res[4];
	res[0] = static_cast<float>(M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3]);
	res[1] = static_cast<float>(M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3]);
	res[2] = static_cast<float>(M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3]);
	res[3] = static_cast<float>(M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3]);
	x = res[0];
	y = res[1];
	z = res[2];
	w = res[3];
	return (*this);
}

Vector4D& Vector4D::vectorMatrixMultiply(float M[16], float v[4])
{
	float res[4];
	res[0] = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
	res[1] = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
	res[2] = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
	res[3] = M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3];
	x = res[0];
	y = res[1];
	z = res[2];
	w = res[3];
	return (*this);
}

Vector4D& Vector4D::vectorMatrixMultiply(float M[16], const Vector4D& p)
{
	x = M[0] * p.x + M[4] * p.y + M[8] * p.z + M[12] * 1;
	y = M[1] * p.x + M[5] * p.y + M[9] * p.z + M[13] * 1;
	z = M[2] * p.x + M[6] * p.y + M[10] * p.z + M[14] * 1;
	w = M[3] * p.x + M[7] * p.y + M[11] * p.z + M[15] * 1;
	return (*this);
}
Vector4D& Vector4D::vectorMatrixMultiply(double M[16], const Vector4D& p)
{
	x = static_cast<float>(M[0] * p.x + M[4] * p.y + M[8] * p.z + M[12] * 1);
	y = static_cast<float>(M[1] * p.x + M[5] * p.y + M[9] * p.z + M[13] * 1);
	z = static_cast<float>(M[2] * p.x + M[6] * p.y + M[10] * p.z + M[14] * 1);
	w = static_cast<float>(M[3] * p.x + M[7] * p.y + M[11] * p.z + M[15] * 1);
	return (*this);
}