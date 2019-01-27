/*********************************************************************************
created:	2014/01/23   01:06AM
filename: 	Fle_Vector3D.cpp
file base:	Fle_Vector3D
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for three dimensional vector.

/**********************************************************************************
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Vector3D.h>
#include <cmath>

using namespace R3D;

Vector3D::Vector3D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3D::Vector3D(int xx, int yy, int zz)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
}
Vector3D::Vector3D(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}
Vector3D::Vector3D(double xx, double yy, double zz)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
}
Vector3D::Vector3D(const int f[3])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
}
Vector3D::Vector3D(const float f[3])
{
	x = f[0];
	y = f[1];
	z = f[2];
}
Vector3D::Vector3D(const double f[3])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
}
Vector3D::Vector3D(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3D::setX(float xx) { x = xx; }
void Vector3D::setY(float yy) { y = yy; }
void Vector3D::setZ(float zz) { z = zz; }

void Vector3D::set(int xx, int yy, int zz)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
}
void Vector3D::set(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}
void Vector3D::set(double xx, double yy, double zz)
{
	x = static_cast<float>(xx);
	y = static_cast<float>(yy);
	z = static_cast<float>(zz);
}
void Vector3D::set(const int f[3])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
}
void Vector3D::set(const float f[3])
{
	x = f[0];
	y = f[1];
	z = f[2];
}
void Vector3D::set(const double f[3])
{
	x = static_cast<float>(f[0]);
	y = static_cast<float>(f[1]);
	z = static_cast<float>(f[2]);
}
void Vector3D::set(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
void Vector3D::setZero()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

void Vector3D::get(float& xx, float& yy, float& zz) const
{
	xx = x;
	yy = y;
	zz = z;
}
void Vector3D::get(float f[3]) const
{
	f[0] = x;
	f[1] = y;
	f[2] = z;
}

const float& Vector3D::X() const { return x; }
const float& Vector3D::Y() const { return y; }
const float& Vector3D::Z() const { return z; }

const float& Vector3D::getX() const { return x; }
const float& Vector3D::getY() const { return y; }
const float& Vector3D::getZ() const { return z; }


void Vector3D::print() { std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl; }

/************************************************************************/
/* Operators                                                            */
/************************************************************************/
const Vector3D Vector3D::operator * (const Vector3D &c) const
{
	Vector3D a;
	a.x = this->x * c.x;
	a.y = this->y * c.y;
	a.z = this->z * c.z;
	return a;
}
const Vector3D Vector3D::operator + (const Vector3D &c) const
{
	Vector3D a;
	a.x = this->x + c.x;
	a.y = this->y + c.y;
	a.z = this->z + c.z;
	return a;
}
const Vector3D Vector3D::operator - (const Vector3D &c) const
{
	Vector3D a;
	a.x = this->x - c.x;
	a.y = this->y - c.y;
	a.z = this->z - c.z;
	return a;
}
const Vector3D Vector3D::operator / (const Vector3D &c) const
{
	Vector3D a;
	a.x = this->x / c.x;
	a.y = this->y / c.y;
	a.z = this->z / c.z;
	return a;
}



const bool Vector3D::operator == (const Vector3D& v) const
{
	return ((std::abs(v.x - x) < 0.000001f) && (std::abs(v.y - y) < 0.000001f) && (std::abs(v.z - z) < 0.000001f));
}
const bool Vector3D::operator < (const Vector3D& v) const
{
	if (x < v.x && y < v.y && z < v.z)
		return true;
	return false;
}
const bool Vector3D::operator > (const Vector3D& v) const
{
	if (x > v.x && y > v.y && z > v.z)
		return true;
	return false;
}
const bool Vector3D::operator >= (const Vector3D& v) const
{
	if (x >= v.x && y >= v.y && z >= v.z)
		return true;
	return false;
}
const bool Vector3D::operator <= (const Vector3D& v) const
{
	if (x <= v.x && y <= v.y && z <= v.z)
		return true;
	return false;
}
const bool Vector3D::operator != (const Vector3D& v) const
{
	return !(v == *this);
}

const Vector3D& Vector3D::operator = (const Vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
const Vector3D& Vector3D::operator += (const Vector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
const Vector3D& Vector3D::operator -= (const Vector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
const Vector3D& Vector3D::operator *= (const float& s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
const Vector3D& Vector3D::operator /= (const float& s)
{
	const float r = 1 / s;
	x *= r;
	y *= r;
	z *= r;
	return *this;
}
const Vector3D Vector3D::operator * (const float s) const
{
	Vector3D a;
	a.x = x*s;
	a.y = y*s;
	a.z = z*s;
	return a;
}
const Vector3D Vector3D::operator + (const float s) const
{
	Vector3D a;
	a.x = x + s;
	a.y = y + s;
	a.z = z + s;
	return a;
}
const Vector3D Vector3D::operator - (const float s) const
{
	Vector3D a;
	a.x = x - s;
	a.y = y - s;
	a.z = z - s;
	return a;
}
const Vector3D Vector3D::operator / (float s) const
{
	s = 1 / s;
	Vector3D a;
	a.x = x*s;
	a.y = y*s;
	a.z = z*s;
	return a;
}

const bool Vector3D::operator >= (float s) const
{
	if (x >= s && y >= s && z >= s)
		return true;
	return false;
}
const bool Vector3D::operator <= (float s) const
{
	if (x <= s && y <= s && z <= s)
		return true;
	return false;
}
const bool Vector3D::operator == (float s) const
{
	//if( x == s && y == s && z == s )
	if ((std::abs(s - x) < 0.000001f) && (std::abs(s - y) < 0.000001f) && (std::abs(s - z) < 0.000001f))
		return true;
	return false;
}
const bool Vector3D::operator != (float s) const
{
	if (((x != s) && (y != s) && (z != s)))
		return true;
	return false;
}
const bool Vector3D::operator > (float s) const
{
	if (x > s && y > s && z > s)
		return true;
	return false;
}
const bool Vector3D::operator < (float s) const
{
	if (x < s && y < s && z < s)
		return true;
	return false;
}
void Vector3D::scale(float v)
{
	x *= v;
	y *= v;
	z *= v;
}
const Vector3D Vector3D::cross(const Vector3D& v) const
{
	Vector3D a;
	a.x = y*v.z - z*v.y;
	a.y = z*v.x - x*v.z;
	a.z = x*v.y - y*v.x;
	return a;
}
const float Vector3D::dot(const Vector3D& v) const
{
	return x*v.x + y*v.y + z*v.z;
}
const float Vector3D::length() const
{
	return std::sqrt(this->dot(*this));
}
const float Vector3D::squaredlength() const
{
	return static_cast<float>(x*x + y*y + z*z);
}
const float Vector3D::getDistance(const Vector3D& v) const
{
	const Vector3D dif = v - *this;
	return dif.length();
}
const Vector3D Vector3D::getNormalized() const
{
	return (*this) / length();
}
const Vector3D Vector3D::reflect(const Vector3D& normal) const
{
	return Vector3D(*this - (2 * (*this).dot(normal) * normal));
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
const float Vector3D::getAngleBetween(const Vector3D& dest) const
{
	float lenProduct = length() * dest.length();
	if (lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float f = (*this).dot(dest) / lenProduct;
	f = __Clamp(f, -1.f, 1.f);
	return acos(f);
}
const Vector3D Vector3D::abs() const
{
	Vector3D a;
	a.x = std::abs((*this).x);
	a.y = std::abs((*this).y);
	a.z = std::abs((*this).z);
	return a;
}
const Vector3D Vector3D::negate() const
{
	Vector3D a;
	a.x = -x;
	a.y = -y;
	a.z = -z;
	return a;
}
void Vector3D::normalize()
{
	float l = length();
	if (l == 1.0f || l == 0.0f)
		return;
	(*this) /= l;
}
void Vector3D::squaredNormalize()
{
	(*this) /= squaredlength();
}
const bool Vector3D::nearlyEquals(const Vector3D& v, const float e) const
{
	return std::abs(x - v.x) < e && std::abs(y - v.y) < e && std::abs(z - v.z) < e;
}
void Vector3D::reverseDirection()
{
	(*this) = (*this) * -1.0f;
}
const bool Vector3D::isSameDirection(const Vector3D& Vector) const
{
	return (((*this).getNormalized()).dot(Vector.getNormalized()) > 0.0f);
}
const Vector3D Vector3D::getMaxFromTwo(const Vector3D& pnt0, const Vector3D& pnt1)
{
	Vector3D result;
	result.x = (pnt0.x > pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y > pnt1.y) ? pnt0.y : pnt1.y;
	result.z = (pnt0.z > pnt1.z) ? pnt0.z : pnt1.z;
	return result;
}
const Vector3D Vector3D::getMinFromTwo(const Vector3D& pnt0, const Vector3D& pnt1)
{
	Vector3D result;
	result.x = (pnt0.x < pnt1.x) ? pnt0.x : pnt1.x;
	result.y = (pnt0.y < pnt1.y) ? pnt0.y : pnt1.y;
	result.z = (pnt0.z < pnt1.z) ? pnt0.z : pnt1.z;
	return result;
}
const float Vector3D::getMaxAxis() const
{
	float result = 0.f;
	result = (x > y) ? x : y;
	result = (z > result) ? z : result;
	return result;
}
const float Vector3D::getMinAxis() const
{
	float result = 0.f;
	result = (x < y) ? x : y;
	result = (z < result) ? z : result;
	return result;
}

Vector3D& Vector3D::rotateAboutX(const float degres)
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
Vector3D& Vector3D::rotateAboutY(const float degres)
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
Vector3D& Vector3D::rotateAboutZ(const float degres)
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

Vector3D& Vector3D::rotateAboutAxis(const float degres, const Vector3D& axis)
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

Vector3D& Vector3D::vectorMatrixMultiply(const double M[16], const float v[4])
{
	x = static_cast<float>(M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3]);
	y = static_cast<float>(M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3]);
	z = static_cast<float>(M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3]);
	return (*this);
}

Vector3D& Vector3D::vectorMatrixMultiply(const float M[16], const float v[4])
{
	x = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
	y = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
	z = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
	return (*this);
}

Vector3D& Vector3D::vectorMatrixMultiply(const float M[16], const Vector3D& p)
{
	x = M[0] * p.x + M[4] * p.y + M[8] * p.z + M[12] * 1;
	y = M[1] * p.x + M[5] * p.y + M[9] * p.z + M[13] * 1;
	z = M[2] * p.x + M[6] * p.y + M[10] * p.z + M[14] * 1;
	return (*this);
}
Vector3D& Vector3D::vectorMatrixMultiply(const double M[16], const Vector3D& p)
{
	x = static_cast<float>(M[0] * p.x + M[4] * p.y + M[8] * p.z + M[12] * 1);
	y = static_cast<float>(M[1] * p.x + M[5] * p.y + M[9] * p.z + M[13] * 1);
	z = static_cast<float>(M[2] * p.x + M[6] * p.y + M[10] * p.z + M[14] * 1);
	return (*this);
}