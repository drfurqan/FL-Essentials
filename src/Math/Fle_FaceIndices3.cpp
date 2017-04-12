/*********************************************************************************
created:	2017/04/12   01:06AM
filename: 	Fle_FaceIndices3.cpp
file base:	Fle_FaceIndices3
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for three face/triangle indices.

/**********************************************************************************
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_FaceIndices3.h>

using namespace R3D;

FaceIndices3::FaceIndices3()
{
	v1 = std::numeric_limits<unsigned int>::max();
	v2 = std::numeric_limits<unsigned int>::max();
	v3 = std::numeric_limits<unsigned int>::max();
}
FaceIndices3::FaceIndices3(unsigned int _v1, unsigned int _v2, unsigned int _v3)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
}
FaceIndices3::FaceIndices3(const unsigned int _face[3])
{
	v1 = _face[0];
	v2 = _face[1];
	v3 = _face[2];
}
FaceIndices3::FaceIndices3(const FaceIndices3& _face)
{
	v1 = _face.v1;
	v2 = _face.v2;
	v3 = _face.v3;
}

void FaceIndices3::setV1(const unsigned int _v1) { v1 = _v1; }
void FaceIndices3::setV2(const unsigned int _v2) { v2 = _v2; }
void FaceIndices3::setV3(const unsigned int _v3) { v3 = _v3; }

void FaceIndices3::set(const unsigned int _v1, const unsigned int _v2, const unsigned int _v3)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
}
void FaceIndices3::set(const unsigned int _face[3])
{
	v1 = _face[0];
	v2 = _face[1];
	v3 = _face[2];
}
void FaceIndices3::set(const FaceIndices3& _face)
{
	v1 = _face.v1;
	v2 = _face.v2;
	v3 = _face.v3;
}
void FaceIndices3::get(unsigned int _face[3]) const
{
	_face[0] = v1;
	_face[1] = v2;
	_face[2] = v3;
}

const unsigned int& FaceIndices3::V1() const { return v1; }
const unsigned int& FaceIndices3::V2() const { return v2; }
const unsigned int& FaceIndices3::V3() const { return v3; }

const unsigned int& FaceIndices3::getV1() const { return v1; }
const unsigned int& FaceIndices3::getV2() const { return v2; }
const unsigned int& FaceIndices3::getV3() const { return v3; }


void FaceIndices3::print() { std::cout << "(" << v1 << ", " << v2 << ", " << v3 << ")" << std::endl; }

/************************************************************************/
/* Operators                                                            */
/************************************************************************/
const FaceIndices3 FaceIndices3::operator * (const FaceIndices3& c) const
{
	FaceIndices3 a;
	a.v1 = this->v1 * c.v1;
	a.v2 = this->v2 * c.v2;
	a.v3 = this->v3 * c.v3;
	return a;
}
const FaceIndices3 FaceIndices3::operator + (const FaceIndices3& c) const
{
	FaceIndices3 a;
	a.v1 = this->v1 + c.v1;
	a.v2 = this->v2 + c.v2;
	a.v3 = this->v3 + c.v3;
	return a;
}
const FaceIndices3 FaceIndices3::operator - (const FaceIndices3&c) const
{
	FaceIndices3 a;
	a.v1 = this->v1 - c.v1;
	a.v2 = this->v2 - c.v2;
	a.v3 = this->v3 - c.v3;
	return a;
}
const FaceIndices3 FaceIndices3::operator / (const FaceIndices3& c) const
{
	FaceIndices3 a;
	a.v1 = this->v1 / c.v1;
	a.v2 = this->v2 / c.v2;
	a.v3 = this->v3 / c.v3;
	return a;
}


const bool FaceIndices3::operator == (const FaceIndices3& _v) const
{
	if (_v.v1 == v1 && _v.v2 == v2 && _v.v3 == v3)
		return true;
	return false;
}
const bool FaceIndices3::operator < (const FaceIndices3& v) const
{
	if (v1 < v.v1 && v2 < v.v2 && v3 < v.v3)
		return true;
	return false;
}
const bool FaceIndices3::operator > (const FaceIndices3& v) const
{
	if (v1 > v.v1 && v2 > v.v2 && v3 > v.v3)
		return true;
	return false;
}
const bool FaceIndices3::operator >= (const FaceIndices3& v) const
{
	if (v1 >= v.v1 && v2 >= v.v2 && v3 >= v.v3)
		return true;
	return false;
}
const bool FaceIndices3::operator <= (const FaceIndices3& v) const
{
	if (v1 <= v.v1 && v2 <= v.v2 && v3 <= v.v3)
		return true;
	return false;
}
const bool FaceIndices3::operator != (const FaceIndices3& v) const
{
	return !(v == *this);
}

const FaceIndices3& FaceIndices3::operator = (const FaceIndices3& v)
{
	v1 = v.v1;
	v2 = v.v2;
	v3 = v.v3;
	return *this;
}
const FaceIndices3& FaceIndices3::operator += (const FaceIndices3& v)
{
	v1 += v.v1;
	v2 += v.v2;
	v3 += v.v3;
	return *this;
}
const FaceIndices3& FaceIndices3::operator -= (const FaceIndices3& v)
{
	v1 -= v.v1;
	v2 -= v.v2;
	v3 -= v.v3;
	return *this;
}
void FaceIndices3::reverse()
{
	std::swap(v1, v3);
}