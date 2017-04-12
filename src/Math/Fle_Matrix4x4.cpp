/*********************************************************************************
created:	2014/01/29   10:09PM
filename: 	Fle_Matrix4x4.cpp
file base:	Fle_Matrix4x4
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for 4x4 matrices.

/**********************************************************************************
Copyright (c) 2006, Paul Baker
Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
http://www.paulsprojects.net/NewBSDLicense.txt

Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Matrix4x4.h>

static const float M_PI = 3.1415926535897932384626433832795f;

using namespace R3D;

Matrix4x4::Matrix4x4()
{ 
	loadIdentity(); 
}
Matrix4x4::Matrix4x4(
	float e0, float e1, float e2, float e3,
	float e4, float e5, float e6, float e7,
	float e8, float e9, float e10, float e11,
	float e12, float e13, float e14, float e15)
{
	en[0] = e0;
	en[1] = e1;
	en[2] = e2;
	en[3] = e3;
	en[4] = e4;
	en[5] = e5;
	en[6] = e6;
	en[7] = e7;
	en[8] = e8;
	en[9] = e9;
	en[10] = e10;
	en[11] = e11;
	en[12] = e12;
	en[13] = e13;
	en[14] = e14;
	en[15] = e15;
}

void Matrix4x4::print_M4x4()
{
	for (int i = 0; i < 4; i++)
		printf(" %8.4f %8.3f %8.4f %8.4f\n", en[0 + i], en[4 + i], en[8 + i], en[12 + i]);
	std::cout << std::endl;		// insert a empty line
}

Matrix4x4::Matrix4x4(const Matrix4x4 & rhs)
{
	std::memcpy(en, rhs.en, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(const float * rhs)
{
	std::memcpy(en, rhs, 16 * sizeof(float));
}

void Matrix4x4::set(int index, float value)
{
	if (index >= 0 && index <= 15)
		en[index] = value;
}

float Matrix4x4::get(int index) const
{
	if (index >= 0 && index <= 15)
		return en[index];

	return 0.0f;
}

Vector4D Matrix4x4::getRow(int index) const
{
	if (index == 0)
		return Vector4D(en[0], en[4], en[8], en[12]);

	if (index == 1)
		return Vector4D(en[1], en[5], en[9], en[13]);

	if (index == 2)
		return Vector4D(en[2], en[6], en[10], en[14]);

	if (index == 3)
		return Vector4D(en[3], en[7], en[11], en[15]);

	return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4D Matrix4x4::getColumn(int index) const
{
	if (index == 0)
		return Vector4D(en[0], en[1], en[2], en[3]);

	if (index == 1)
		return Vector4D(en[4], en[5], en[6], en[7]);

	if (index == 2)
		return Vector4D(en[8], en[9], en[10], en[11]);

	if (index == 3)
		return Vector4D(en[12], en[13], en[14], en[15]);

	return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector3D Matrix4x4::getRow3(int index) const
{
	if (index == 0)
		return Vector3D(en[0], en[4], en[8]);

	if (index == 1)
		return Vector3D(en[1], en[5], en[9]);

	if (index == 2)
		return Vector3D(en[2], en[6], en[10]);

	if (index == 3)
		return Vector3D(en[3], en[7], en[11]);

	return Vector3D(0.0f, 0.0f, 0.0f);
}

Vector3D Matrix4x4::getColumn3(int index) const
{
	if (index == 0)
		return Vector3D(en[0], en[1], en[2]);

	if (index == 1)
		return Vector3D(en[4], en[5], en[6]);

	if (index == 2)
		return Vector3D(en[8], en[9], en[10]);

	if (index == 3)
		return Vector3D(en[12], en[13], en[14]);

	return Vector3D(0.0f, 0.0f, 0.0f);
}

void Matrix4x4::loadIdentity(void)
{
	memset(en, 0, 16 * sizeof(float));
	en[0] = 1.0f;
	en[5] = 1.0f;
	en[10] = 1.0f;
	en[15] = 1.0f;
}

void Matrix4x4::loadZero(void)
{
	memset(en, 0, 16 * sizeof(float));
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & rhs) const		//overloaded operators
{
	return Matrix4x4(en[0] + rhs.en[0],
		en[1] + rhs.en[1],
		en[2] + rhs.en[2],
		en[3] + rhs.en[3],
		en[4] + rhs.en[4],
		en[5] + rhs.en[5],
		en[6] + rhs.en[6],
		en[7] + rhs.en[7],
		en[8] + rhs.en[8],
		en[9] + rhs.en[9],
		en[10] + rhs.en[10],
		en[11] + rhs.en[11],
		en[12] + rhs.en[12],
		en[13] + rhs.en[13],
		en[14] + rhs.en[14],
		en[15] + rhs.en[15]);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & rhs) const		//overloaded operators
{
	return Matrix4x4(en[0] - rhs.en[0],
		en[1] - rhs.en[1],
		en[2] - rhs.en[2],
		en[3] - rhs.en[3],
		en[4] - rhs.en[4],
		en[5] - rhs.en[5],
		en[6] - rhs.en[6],
		en[7] - rhs.en[7],
		en[8] - rhs.en[8],
		en[9] - rhs.en[9],
		en[10] - rhs.en[10],
		en[11] - rhs.en[11],
		en[12] - rhs.en[12],
		en[13] - rhs.en[13],
		en[14] - rhs.en[14],
		en[15] - rhs.en[15]);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & rhs) const
{
	//Optimise for matrices in which bottom row is (0, 0, 0, 1) in both matrices
	if (en[3] == 0.0f && en[7] == 0.0f && en[11] == 0.0f && en[15] == 1.0f	&&
		rhs.en[3] == 0.0f && rhs.en[7] == 0.0f &&
		rhs.en[11] == 0.0f && rhs.en[15] == 1.0f)
	{
		return Matrix4x4(en[0] * rhs.en[0] + en[4] * rhs.en[1] + en[8] * rhs.en[2],
			en[1] * rhs.en[0] + en[5] * rhs.en[1] + en[9] * rhs.en[2],
			en[2] * rhs.en[0] + en[6] * rhs.en[1] + en[10] * rhs.en[2],
			0.0f,
			en[0] * rhs.en[4] + en[4] * rhs.en[5] + en[8] * rhs.en[6],
			en[1] * rhs.en[4] + en[5] * rhs.en[5] + en[9] * rhs.en[6],
			en[2] * rhs.en[4] + en[6] * rhs.en[5] + en[10] * rhs.en[6],
			0.0f,
			en[0] * rhs.en[8] + en[4] * rhs.en[9] + en[8] * rhs.en[10],
			en[1] * rhs.en[8] + en[5] * rhs.en[9] + en[9] * rhs.en[10],
			en[2] * rhs.en[8] + en[6] * rhs.en[9] + en[10] * rhs.en[10],
			0.0f,
			en[0] * rhs.en[12] + en[4] * rhs.en[13] + en[8] * rhs.en[14] + en[12],
			en[1] * rhs.en[12] + en[5] * rhs.en[13] + en[9] * rhs.en[14] + en[13],
			en[2] * rhs.en[12] + en[6] * rhs.en[13] + en[10] * rhs.en[14] + en[14],
			1.0f);
	}

	//Optimise for when bottom row of 1st matrix is (0, 0, 0, 1)
	if (en[3] == 0.0f && en[7] == 0.0f && en[11] == 0.0f && en[15] == 1.0f)
	{
		return Matrix4x4(en[0] * rhs.en[0] + en[4] * rhs.en[1] + en[8] * rhs.en[2] + en[12] * rhs.en[3],
			en[1] * rhs.en[0] + en[5] * rhs.en[1] + en[9] * rhs.en[2] + en[13] * rhs.en[3],
			en[2] * rhs.en[0] + en[6] * rhs.en[1] + en[10] * rhs.en[2] + en[14] * rhs.en[3],
			rhs.en[3],
			en[0] * rhs.en[4] + en[4] * rhs.en[5] + en[8] * rhs.en[6] + en[12] * rhs.en[7],
			en[1] * rhs.en[4] + en[5] * rhs.en[5] + en[9] * rhs.en[6] + en[13] * rhs.en[7],
			en[2] * rhs.en[4] + en[6] * rhs.en[5] + en[10] * rhs.en[6] + en[14] * rhs.en[7],
			rhs.en[7],
			en[0] * rhs.en[8] + en[4] * rhs.en[9] + en[8] * rhs.en[10] + en[12] * rhs.en[11],
			en[1] * rhs.en[8] + en[5] * rhs.en[9] + en[9] * rhs.en[10] + en[13] * rhs.en[11],
			en[2] * rhs.en[8] + en[6] * rhs.en[9] + en[10] * rhs.en[10] + en[14] * rhs.en[11],
			rhs.en[11],
			en[0] * rhs.en[12] + en[4] * rhs.en[13] + en[8] * rhs.en[14] + en[12] * rhs.en[15],
			en[1] * rhs.en[12] + en[5] * rhs.en[13] + en[9] * rhs.en[14] + en[13] * rhs.en[15],
			en[2] * rhs.en[12] + en[6] * rhs.en[13] + en[10] * rhs.en[14] + en[14] * rhs.en[15],
			rhs.en[15]);
	}

	//Optimise for when bottom row of 2nd matrix is (0, 0, 0, 1)
	if (rhs.en[3] == 0.0f && rhs.en[7] == 0.0f &&
		rhs.en[11] == 0.0f && rhs.en[15] == 1.0f)
	{
		return Matrix4x4(en[0] * rhs.en[0] + en[4] * rhs.en[1] + en[8] * rhs.en[2],
			en[1] * rhs.en[0] + en[5] * rhs.en[1] + en[9] * rhs.en[2],
			en[2] * rhs.en[0] + en[6] * rhs.en[1] + en[10] * rhs.en[2],
			en[3] * rhs.en[0] + en[7] * rhs.en[1] + en[11] * rhs.en[2],
			en[0] * rhs.en[4] + en[4] * rhs.en[5] + en[8] * rhs.en[6],
			en[1] * rhs.en[4] + en[5] * rhs.en[5] + en[9] * rhs.en[6],
			en[2] * rhs.en[4] + en[6] * rhs.en[5] + en[10] * rhs.en[6],
			en[3] * rhs.en[4] + en[7] * rhs.en[5] + en[11] * rhs.en[6],
			en[0] * rhs.en[8] + en[4] * rhs.en[9] + en[8] * rhs.en[10],
			en[1] * rhs.en[8] + en[5] * rhs.en[9] + en[9] * rhs.en[10],
			en[2] * rhs.en[8] + en[6] * rhs.en[9] + en[10] * rhs.en[10],
			en[3] * rhs.en[8] + en[7] * rhs.en[9] + en[11] * rhs.en[10],
			en[0] * rhs.en[12] + en[4] * rhs.en[13] + en[8] * rhs.en[14] + en[12],
			en[1] * rhs.en[12] + en[5] * rhs.en[13] + en[9] * rhs.en[14] + en[13],
			en[2] * rhs.en[12] + en[6] * rhs.en[13] + en[10] * rhs.en[14] + en[14],
			en[3] * rhs.en[12] + en[7] * rhs.en[13] + en[11] * rhs.en[14] + en[15]);
	}

	return Matrix4x4(en[0] * rhs.en[0] + en[4] * rhs.en[1] + en[8] * rhs.en[2] + en[12] * rhs.en[3],
		en[1] * rhs.en[0] + en[5] * rhs.en[1] + en[9] * rhs.en[2] + en[13] * rhs.en[3],
		en[2] * rhs.en[0] + en[6] * rhs.en[1] + en[10] * rhs.en[2] + en[14] * rhs.en[3],
		en[3] * rhs.en[0] + en[7] * rhs.en[1] + en[11] * rhs.en[2] + en[15] * rhs.en[3],
		en[0] * rhs.en[4] + en[4] * rhs.en[5] + en[8] * rhs.en[6] + en[12] * rhs.en[7],
		en[1] * rhs.en[4] + en[5] * rhs.en[5] + en[9] * rhs.en[6] + en[13] * rhs.en[7],
		en[2] * rhs.en[4] + en[6] * rhs.en[5] + en[10] * rhs.en[6] + en[14] * rhs.en[7],
		en[3] * rhs.en[4] + en[7] * rhs.en[5] + en[11] * rhs.en[6] + en[15] * rhs.en[7],
		en[0] * rhs.en[8] + en[4] * rhs.en[9] + en[8] * rhs.en[10] + en[12] * rhs.en[11],
		en[1] * rhs.en[8] + en[5] * rhs.en[9] + en[9] * rhs.en[10] + en[13] * rhs.en[11],
		en[2] * rhs.en[8] + en[6] * rhs.en[9] + en[10] * rhs.en[10] + en[14] * rhs.en[11],
		en[3] * rhs.en[8] + en[7] * rhs.en[9] + en[11] * rhs.en[10] + en[15] * rhs.en[11],
		en[0] * rhs.en[12] + en[4] * rhs.en[13] + en[8] * rhs.en[14] + en[12] * rhs.en[15],
		en[1] * rhs.en[12] + en[5] * rhs.en[13] + en[9] * rhs.en[14] + en[13] * rhs.en[15],
		en[2] * rhs.en[12] + en[6] * rhs.en[13] + en[10] * rhs.en[14] + en[14] * rhs.en[15],
		en[3] * rhs.en[12] + en[7] * rhs.en[13] + en[11] * rhs.en[14] + en[15] * rhs.en[15]);
}

Matrix4x4 Matrix4x4::operator*(const float rhs) const
{
	return Matrix4x4(en[0] * rhs,
		en[1] * rhs,
		en[2] * rhs,
		en[3] * rhs,
		en[4] * rhs,
		en[5] * rhs,
		en[6] * rhs,
		en[7] * rhs,
		en[8] * rhs,
		en[9] * rhs,
		en[10] * rhs,
		en[11] * rhs,
		en[12] * rhs,
		en[13] * rhs,
		en[14] * rhs,
		en[15] * rhs);
}

Matrix4x4 Matrix4x4::operator/(const float rhs) const
{
	if (rhs == 0.0f || rhs == 1.0f)
		return (*this);

	float temp = 1 / rhs;

	return (*this)*temp;
}

bool Matrix4x4::operator==(const Matrix4x4 & rhs) const
{
	for (int i = 0; i < 16; i++)
	{
		if (en[i] != rhs.en[i])
			return false;
	}
	return true;
}

bool Matrix4x4::operator!=(const Matrix4x4 & rhs) const
{
	return !((*this) == rhs);
}

void Matrix4x4::operator+=(const Matrix4x4 & rhs)
{
	(*this) = (*this) + rhs;
}

void Matrix4x4::operator-=(const Matrix4x4 & rhs)
{
	(*this) = (*this) - rhs;
}

void Matrix4x4::operator*=(const Matrix4x4 & rhs)
{
	(*this) = (*this)*rhs;
}

void Matrix4x4::operator*=(const float rhs)
{
	(*this) = (*this)*rhs;
}

void Matrix4x4::operator/=(const float rhs)
{
	(*this) = (*this) / rhs;
}

Matrix4x4 Matrix4x4::operator-(void) const
{
	Matrix4x4 result(*this);

	for (int i = 0; i < 16; i++)
		result.en[i] = -result.en[i];

	return result;
}

Vector4D Matrix4x4::operator*(const Vector4D& rhs) const
{
	// Optimize for matrices in which bottom row is (0, 0, 0, 1)
	if (en[3] == 0.0f && en[7] == 0.0f && en[11] == 0.0f && en[15] == 1.0f)
	{
		return Vector4D(
			en[0] * rhs.x
			+ en[4] * rhs.y
			+ en[8] * rhs.z
			+ en[12] * rhs.w,

			en[1] * rhs.x
			+ en[5] * rhs.y
			+ en[9] * rhs.z
			+ en[13] * rhs.w,

			en[2] * rhs.x
			+ en[6] * rhs.y
			+ en[10] * rhs.z
			+ en[14] * rhs.w,

			rhs.w);
	}

	return Vector4D(
		en[0] * rhs.x
		+ en[4] * rhs.y
		+ en[8] * rhs.z
		+ en[12] * rhs.w,

		en[1] * rhs.x
		+ en[5] * rhs.y
		+ en[9] * rhs.z
		+ en[13] * rhs.w,

		en[2] * rhs.x
		+ en[6] * rhs.y
		+ en[10] * rhs.z
		+ en[14] * rhs.w,

		en[3] * rhs.x
		+ en[7] * rhs.y
		+ en[11] * rhs.z
		+ en[15] * rhs.w);
}

Vector3D Matrix4x4::operator*(const Vector3D& r) const
{
	Vector4D rhs;
	rhs.set(r.x, r.y, r.z, 1.0f);

	// Optimize for matrices in which bottom row is (0, 0, 0, 1)
	if (en[3] == 0.0f && en[7] == 0.0f && en[11] == 0.0f && en[15] == 1.0f)
	{
		return Vector3D(
			en[0] * rhs.x
			+ en[4] * rhs.y
			+ en[8] * rhs.z
			+ en[12] * rhs.w,

			en[1] * rhs.x
			+ en[5] * rhs.y
			+ en[9] * rhs.z
			+ en[13] * rhs.w,

			en[2] * rhs.x
			+ en[6] * rhs.y
			+ en[10] * rhs.z
			+ en[14] * rhs.w);
	}

	return Vector3D(
		en[0] * rhs.x
		+ en[4] * rhs.y
		+ en[8] * rhs.z
		+ en[12] * rhs.w,

		en[1] * rhs.x
		+ en[5] * rhs.y
		+ en[9] * rhs.z
		+ en[13] * rhs.w,

		en[2] * rhs.x
		+ en[6] * rhs.y
		+ en[10] * rhs.z
		+ en[14] * rhs.w);
}

Vector3D Matrix4x4::getRotatedVector3D(const Vector3D & rhs) const
{
	return Vector3D(en[0] * rhs.x + en[4] * rhs.y + en[8] * rhs.z,
		en[1] * rhs.x + en[5] * rhs.y + en[9] * rhs.z,
		en[2] * rhs.x + en[6] * rhs.y + en[10] * rhs.z);
}

Vector3D Matrix4x4::getInverseRotatedVector3D(const Vector3D & rhs) const
{
	//rotate by transpose:
	return Vector3D(en[0] * rhs.x + en[1] * rhs.y + en[2] * rhs.z,
		en[4] * rhs.x + en[5] * rhs.y + en[6] * rhs.z,
		en[8] * rhs.x + en[9] * rhs.y + en[10] * rhs.z);
}

Vector3D Matrix4x4::getTranslatedVector3D(const Vector3D & rhs) const
{
	return Vector3D(rhs.x + en[12], rhs.y + en[13], rhs.z + en[14]);
}

Vector3D Matrix4x4::getInverseTranslatedVector3D(const Vector3D & rhs) const
{
	return Vector3D(rhs.x - en[12], rhs.y - en[13], rhs.z - en[14]);
}

Vector3D Matrix4x4::vectorMatrixMultiply(const Vector3D& v)
{
	Vector3D out;

	out.x = (v.x * en[0]) + (v.y * en[4]) + (v.z * en[8]) + en[12];
	out.y = (v.x * en[1]) + (v.y * en[5]) + (v.z * en[9]) + en[13];
	out.z = (v.x * en[2]) + (v.y * en[6]) + (v.z * en[10]) + en[14];

	return out;
}

Vector3D Matrix4x4::vectorMatrixMultiply3x3(const Vector3D& v)
{
	Vector3D out;

	out.x = (v.x * en[0]) + (v.y * en[4]) + (v.z * en[8]);
	out.y = (v.x * en[1]) + (v.y * en[5]) + (v.z * en[9]);
	out.z = (v.x * en[2]) + (v.y * en[6]) + (v.z * en[10]);

	return out;
}

Vector3D Matrix4x4::inverseVectorMatrixMultiply3x3(const Vector3D& v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	Vector3D out(v);

	out.x = x * en[0] +
		y * en[1] +
		z * en[2];

	out.y = x * en[4] +
		y * en[5] +
		z * en[6];

	out.z = x * en[8] +
		y * en[9] +
		z * en[10];

	return out;
}

void Matrix4x4::invert(void)
{
	*this = getInverse();
}

Matrix4x4 Matrix4x4::getInverse(void) const
{
	Matrix4x4 result = getInverseTranspose();

	result.transpose();

	return result;
}

void Matrix4x4::transpose(void)
{
	*this = getTranspose();
}

Matrix4x4 Matrix4x4::getTranspose(void) const
{
	return Matrix4x4(en[0], en[4], en[8], en[12],
		en[1], en[5], en[9], en[13],
		en[2], en[6], en[10], en[14],
		en[3], en[7], en[11], en[15]);
}

void Matrix4x4::invertTranspose(void)
{
	*this = getInverseTranspose();
}

Matrix4x4 Matrix4x4::getInverseTranspose(void) const
{
	Matrix4x4 result;

	float tmp[12];												//temporary pair storage
	float det;													//determinant

	//calculate pairs for first 8 elements (cofactors)
	tmp[0] = en[10] * en[15];
	tmp[1] = en[11] * en[14];
	tmp[2] = en[9] * en[15];
	tmp[3] = en[11] * en[13];
	tmp[4] = en[9] * en[14];
	tmp[5] = en[10] * en[13];
	tmp[6] = en[8] * en[15];
	tmp[7] = en[11] * en[12];
	tmp[8] = en[8] * en[14];
	tmp[9] = en[10] * en[12];
	tmp[10] = en[8] * en[13];
	tmp[11] = en[9] * en[12];

	//calculate first 8 elements (cofactors)
	result.set(0, tmp[0] * en[5] + tmp[3] * en[6] + tmp[4] * en[7]
		- tmp[1] * en[5] - tmp[2] * en[6] - tmp[5] * en[7]);

	result.set(1, tmp[1] * en[4] + tmp[6] * en[6] + tmp[9] * en[7]
		- tmp[0] * en[4] - tmp[7] * en[6] - tmp[8] * en[7]);

	result.set(2, tmp[2] * en[4] + tmp[7] * en[5] + tmp[10] * en[7]
		- tmp[3] * en[4] - tmp[6] * en[5] - tmp[11] * en[7]);

	result.set(3, tmp[5] * en[4] + tmp[8] * en[5] + tmp[11] * en[6]
		- tmp[4] * en[4] - tmp[9] * en[5] - tmp[10] * en[6]);

	result.set(4, tmp[1] * en[1] + tmp[2] * en[2] + tmp[5] * en[3]
		- tmp[0] * en[1] - tmp[3] * en[2] - tmp[4] * en[3]);

	result.set(5, tmp[0] * en[0] + tmp[7] * en[2] + tmp[8] * en[3]
		- tmp[1] * en[0] - tmp[6] * en[2] - tmp[9] * en[3]);

	result.set(6, tmp[3] * en[0] + tmp[6] * en[1] + tmp[11] * en[3]
		- tmp[2] * en[0] - tmp[7] * en[1] - tmp[10] * en[3]);

	result.set(7, tmp[4] * en[0] + tmp[9] * en[1] + tmp[10] * en[2]
		- tmp[5] * en[0] - tmp[8] * en[1] - tmp[11] * en[2]);

	//calculate pairs for second 8 elements (cofactors)
	tmp[0] = en[2] * en[7];
	tmp[1] = en[3] * en[6];
	tmp[2] = en[1] * en[7];
	tmp[3] = en[3] * en[5];
	tmp[4] = en[1] * en[6];
	tmp[5] = en[2] * en[5];
	tmp[6] = en[0] * en[7];
	tmp[7] = en[3] * en[4];
	tmp[8] = en[0] * en[6];
	tmp[9] = en[2] * en[4];
	tmp[10] = en[0] * en[5];
	tmp[11] = en[1] * en[4];

	//calculate second 8 elements (cofactors)
	result.set(8, tmp[0] * en[13] + tmp[3] * en[14] + tmp[4] * en[15]
		- tmp[1] * en[13] - tmp[2] * en[14] - tmp[5] * en[15]);

	result.set(9, tmp[1] * en[12] + tmp[6] * en[14] + tmp[9] * en[15]
		- tmp[0] * en[12] - tmp[7] * en[14] - tmp[8] * en[15]);

	result.set(10, tmp[2] * en[12] + tmp[7] * en[13] + tmp[10] * en[15]
		- tmp[3] * en[12] - tmp[6] * en[13] - tmp[11] * en[15]);

	result.set(11, tmp[5] * en[12] + tmp[8] * en[13] + tmp[11] * en[14]
		- tmp[4] * en[12] - tmp[9] * en[13] - tmp[10] * en[14]);

	result.set(12, tmp[2] * en[10] + tmp[5] * en[11] + tmp[1] * en[9]
		- tmp[4] * en[11] - tmp[0] * en[9] - tmp[3] * en[10]);

	result.set(13, tmp[8] * en[11] + tmp[0] * en[8] + tmp[7] * en[10]
		- tmp[6] * en[10] - tmp[9] * en[11] - tmp[1] * en[8]);

	result.set(14, tmp[6] * en[9] + tmp[11] * en[11] + tmp[3] * en[8]
		- tmp[10] * en[11] - tmp[2] * en[8] - tmp[7] * en[9]);

	result.set(15, tmp[10] * en[10] + tmp[4] * en[8] + tmp[9] * en[9]
		- tmp[8] * en[9] - tmp[11] * en[10] - tmp[5] * en[8]);

	// calculate determinant
	det = en[0] * result.get(0)
		+ en[1] * result.get(1)
		+ en[2] * result.get(2)
		+ en[3] * result.get(3);

	if (det == 0.0f)
	{
		Matrix4x4 id;
		return id;
	}

	result = result / det;

	return result;
}

//Invert if only composed of rotations & translations
void Matrix4x4::affineInvert(void)
{
	(*this) = getAffineInverse();
}

Matrix4x4 Matrix4x4::getAffineInverse(void) const
{
	//return the transpose of the rotation part
	//and the negative of the inverse rotated translation part
	return Matrix4x4(en[0],
		en[4],
		en[8],
		0.0f,
		en[1],
		en[5],
		en[9],
		0.0f,
		en[2],
		en[6],
		en[10],
		0.0f,
		-(en[0] * en[12] + en[1] * en[13] + en[2] * en[14]),
		-(en[4] * en[12] + en[5] * en[13] + en[6] * en[14]),
		-(en[8] * en[12] + en[9] * en[13] + en[10] * en[14]),
		1.0f);
}

void Matrix4x4::affineInvertTranspose(void)
{
	(*this) = getAffineInverseTranspose();
}

Matrix4x4 Matrix4x4::getAffineInverseTranspose(void) const
{
	//return the transpose of the rotation part
	//and the negative of the inverse rotated translation part
	//transposed
	return Matrix4x4(en[0],
		en[1],
		en[2],
		-(en[0] * en[12] + en[1] * en[13] + en[2] * en[14]),
		en[4],
		en[5],
		en[6],
		-(en[4] * en[12] + en[5] * en[13] + en[6] * en[14]),
		en[8],
		en[9],
		en[10],
		-(en[8] * en[12] + en[9] * en[13] + en[10] * en[14]),
		0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4x4::createTranslation(const Vector3D & translation)
{
	loadIdentity();
	setTranslationColumn(translation);
}

void Matrix4x4::createScale(const Vector3D & scaleFactor)
{
	loadIdentity();
	en[0] = scaleFactor.x;
	en[5] = scaleFactor.y;
	en[10] = scaleFactor.z;
}

void Matrix4x4::createUniformScale(const float scaleFactor)
{
	loadIdentity();
	en[0] = en[5] = en[10] = scaleFactor;
}

void Matrix4x4::createRotationAxis(const float angle, const Vector3D & axis)
{
	Vector3D u = axis.getNormalized();
	float sinAngle = std::sin(M_PI*angle / 180);
	float cosAngle = std::cos(M_PI*angle / 180);
	float oneMinusCosAngle = 1.0f - cosAngle;

	loadIdentity();

	en[0] = (u.x)*(u.x) + cosAngle*(1 - (u.x)*(u.x));
	en[4] = (u.x)*(u.y)*(oneMinusCosAngle)-sinAngle*u.z;
	en[8] = (u.x)*(u.z)*(oneMinusCosAngle)+sinAngle*u.y;

	en[1] = (u.x)*(u.y)*(oneMinusCosAngle)+sinAngle*u.z;
	en[5] = (u.y)*(u.y) + cosAngle*(1 - (u.y)*(u.y));
	en[9] = (u.y)*(u.z)*(oneMinusCosAngle)-sinAngle*u.x;

	en[2] = (u.x)*(u.z)*(oneMinusCosAngle)-sinAngle*u.y;
	en[6] = (u.y)*(u.z)*(oneMinusCosAngle)+sinAngle*u.x;
	en[10] = (u.z)*(u.z) + cosAngle*(1 - (u.z)*(u.z));
}

void Matrix4x4::createRotationX(const float angle)
{
	loadIdentity();
	en[5] = std::cos(M_PI*angle / 180);
	en[6] = std::sin(M_PI*angle / 180);

	en[9] = -en[6];
	en[10] = en[5];
}

void Matrix4x4::createRotationY(const float angle)
{
	loadIdentity();
	en[0] = std::cos(M_PI*angle / 180);
	en[2] = -std::sin(M_PI*angle / 180);

	en[8] = -en[2];
	en[10] = en[0];
}

void Matrix4x4::createRotationZ(const float angle)
{
	loadIdentity();
	en[0] = std::cos(M_PI*angle / 180.f);
	en[1] = std::sin(M_PI*angle / 180.f);

	en[4] = -en[1];
	en[5] = en[0];
}

void Matrix4x4::createRotationEuler(const float angleX, const float angleY, const float angleZ)
{
	loadIdentity();
	setRotationEuler(angleX, angleY, angleZ);
}

void Matrix4x4::createPerspective(float left, float right, float bottom, float top, float n, float f)
{
	float nudge = 0.999f;		//prevent artifacts with infinite far plane

	loadZero();

	//check for division by 0
	if (left == right || top == bottom || n == f)
		return;

	en[0] = (2 * n) / (right - left);

	en[5] = (2 * n) / (top - bottom);

	en[8] = (right + left) / (right - left);
	en[9] = (top + bottom) / (top - bottom);

	if (f != -1)
	{
		en[10] = -(f + n) / (f - n);
	}
	else		//if f==-1, use an infinite far plane
	{
		en[10] = -nudge;
	}

	en[11] = -1;

	if (f != -1)
	{
		en[14] = -(2 * f*n) / (f - n);
	}
	else		//if f==-1, use an infinite far plane
	{
		en[14] = -2 * n*nudge;
	}
}

void Matrix4x4::createPerspective(float fovy, float aspect, float n, float f)
{
	float left, right, top, bottom;

	//convert fov from degrees to radians
	fovy *= M_PI / 180.f;

	top = n * std::tan(fovy / 2.0f);
	bottom = -top;

	left = aspect*bottom;
	right = aspect*top;

	createPerspective(left, right, bottom, top, n, f);
}

void Matrix4x4::createOrtho(float left, float right, float bottom,
	float top, float n, float f)
{
	loadIdentity();

	en[0] = 2.0f / (right - left);

	en[5] = 2.0f / (top - bottom);

	en[10] = -2.0f / (f - n);

	en[12] = -(right + left) / (right - left);
	en[13] = -(top + bottom) / (top - bottom);
	en[14] = -(f + n) / (f - n);
}

void Matrix4x4::setTranslationColumn(const Vector3D& translation)
{
	en[12] = translation.x;
	en[13] = translation.y;
	en[14] = translation.z;
}

void Matrix4x4::setRotationEuler(const float angleX, const float angleY, const float angleZ)
{
	float cr = std::cos(M_PI*angleX / 180);
	float sr = std::sin(M_PI*angleX / 180);
	float cp = std::cos(M_PI*angleY / 180);
	float sp = std::sin(M_PI*angleY / 180);
	float cy = std::cos(M_PI*angleZ / 180);
	float sy = std::sin(M_PI*angleZ / 180);

	en[0] = (cp*cy);
	en[1] = (cp*sy);
	en[2] = (-sp);

	float srsp = sr*sp;
	float crsp = cr*sp;

	en[4] = (srsp*cy - cr*sy);
	en[5] = (srsp*sy + cr*cy);
	en[6] = (sr*cp);

	en[8] = (crsp*cy + sr*sy);
	en[9] = (crsp*sy - sr*cy);
	en[10] = (cr*cp);
}

void Matrix4x4::createShadowMatrix(const Vector4D& planeNormal, const Vector4D& lightPos)
{
	loadIdentity();

	// To create a shadow matrix we first need the dot product of the ground normal and
	// the light position.  We store the result in a float called dotProduct.  We use the
	// DotProduct function of our CVector4 class (doesn't this make the code look better?).
	float dotProduct = planeNormal.dot(lightPos);

	// Create the shadow matrix by adding our values like so...
	en[0] = dotProduct - lightPos.x * planeNormal.x;
	en[4] = 0.0f - lightPos.x * planeNormal.y;
	en[8] = 0.0f - lightPos.x * planeNormal.z;
	en[12] = 0.0f - lightPos.x * planeNormal.w;

	en[1] = 0.0f - lightPos.y * planeNormal.x;
	en[5] = dotProduct - lightPos.y * planeNormal.y;
	en[9] = 0.0f - lightPos.y * planeNormal.z;
	en[13] = 0.0f - lightPos.y * planeNormal.w;

	en[2] = 0.0f - lightPos.z * planeNormal.x;
	en[6] = 0.0f - lightPos.z * planeNormal.y;
	en[10] = dotProduct - lightPos.z * planeNormal.z;
	en[14] = 0.0f - lightPos.z * planeNormal.w;

	en[3] = 0.0f - lightPos.w * planeNormal.x;
	en[7] = 0.0f - lightPos.w * planeNormal.y;
	en[11] = 0.0f - lightPos.w * planeNormal.z;
	en[15] = dotProduct - lightPos.w * planeNormal.w;

	// Notice that the dotProuct is being subtracted from the light position and the plane
	// normal diagonally.  You will also notice that the x light position is used in the
	// first column, y for the second, and so on.  This is the math to create a shadow
	// projection matrix.  I wouldn't both taking out a pencil and paper and tracing this
	// on out.  Just know that this is how you set it up.
}
