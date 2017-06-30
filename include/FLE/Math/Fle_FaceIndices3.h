#pragma once
#ifndef Fle_FaceIndices3_h__
#define Fle_FaceIndices3_h__

/*********************************************************************************
created:	2017/04/12   01:06AM
filename: 	Fle_FaceIndices3.h
file base:	Fle_FaceIndices3
file ext:	h
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

#include <FLE/Fle_Export.h>

#include <ostream>
#include <iostream>

namespace R3D
{

class FL_ESSENTIALS_EXPORT FaceIndices3
{
public:
	unsigned int v1, v2, v3;

	FaceIndices3();
	FaceIndices3(const unsigned int _v1, const unsigned int _v2, const unsigned int _v3);
	FaceIndices3(const unsigned int _face[3]);
	FaceIndices3(const FaceIndices3& _face);

	void setV1(const unsigned int _v1);
	void setV2(const unsigned int _v2);
	void setV3(const unsigned int _v3);
	void set(const unsigned int _v1, const unsigned int _v2, const unsigned int _v3);
	void set(const unsigned int _face[3]);
	void set(const FaceIndices3& _face);
	void get(unsigned int _face[3]) const;

	const unsigned int& V1() const;
	const unsigned int& V2() const;
	const unsigned int& V3() const;
	const unsigned int& getV1() const;
	const unsigned int& getV2() const;
	const unsigned int& getV3() const;
	void reverse();

	void print();

	unsigned int& operator [](long k) { return ((&v1)[k]); }
	const unsigned int& operator [](long k) const { return ((&v1)[k]); }

	const FaceIndices3 operator * (const FaceIndices3& c) const;
	const FaceIndices3 operator + (const FaceIndices3& c) const;
	const FaceIndices3 operator - (const FaceIndices3& c) const;
	const FaceIndices3 operator / (const FaceIndices3& c) const;

	const bool operator == (const FaceIndices3& v) const;
	const bool operator <  (const FaceIndices3& v) const;
	const bool operator >  (const FaceIndices3& v) const;
	const bool operator >= (const FaceIndices3& v) const;
	const bool operator <= (const FaceIndices3& v) const;
	const bool operator != (const FaceIndices3& v) const;

	const FaceIndices3& operator =  (const FaceIndices3& v);
	const FaceIndices3& operator += (const FaceIndices3& v);
	const FaceIndices3& operator -= (const FaceIndices3& v);
	const unsigned int* ptr() const { return &v1; }
	unsigned int* ptr() { return &v1; }


	friend std::ostream& operator << (std::ostream& out, const FaceIndices3& _v)
	{
		out << "(" << _v.v1 << ", " << _v.v2 << ", " << _v.v3 << ")" << std::endl; return out;
	}
};

}

#endif // Fle_FaceIndices3_h__