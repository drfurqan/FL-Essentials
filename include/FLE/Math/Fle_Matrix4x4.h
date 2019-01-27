#pragma once
#ifndef Fle_Matrix4x4_h__
#define Fle_Matrix4x4_h__

/*********************************************************************************
created:	2014/01/29   10:09PM
filename: 	Fle_Matrix4x4.h
file base:	Fle_Matrix4x4
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class for 4x4 matrices.

/**********************************************************************************
Copyright (c) 2006, Paul Baker
Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
http://www.paulsprojects.net/NewBSDLicense.txt

Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Vector3D.h"
#include "Fle_Vector4D.h"

namespace R3D
{

class FL_ESSENTIALS_EXPORT Matrix4x4
{
public:
	// Description:
	// Default constructor that initializes the identity matrix.
	Matrix4x4();
	// Description:
	// Constructor with 16 arguments.
	Matrix4x4(
		float e0, float e1, float e2, float e3,
		float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11,
		float e12, float e13, float e14, float e15);
	// Description:
	// Constructor that takes a pointer to float array.
	// The array must not be less than 16.
	Matrix4x4(const float* rhs);
	// Description:
	// Copy constructor.
	Matrix4x4(const Matrix4x4& rhs);

	// Description:
	// Function to set the given value at the given index [0 ~ 15].
	void set(int index, float value);

	// Description:
	// Function to set the given value at the given index [0 ~ 15].
	float get(int index) const;

	// Description:
	// Function to get the row at the given index [0 ~ 3]
	Vector4D getRow(int index) const;
	// Description:
	// Function to get the column at the given index [0 ~ 3]
	Vector4D getColumn(int index) const;
	// Description:
	// Function to get the row at the given index [0 ~ 3]
	Vector3D getRow3(int index) const;
	// Description:
	// Function to get the column at the given index [0 ~ 3]
	Vector3D getColumn3(int index) const;

	// Description:
	// Function to make this matrix as identity matrix.
	void loadIdentity();
	// Description:
	// Function to make this matrix as zero matrix.
	void loadZero();

	// Description:
	// Function to get a vector after multiplying the given vector with this matrix's rotated part.
	Vector3D getRotatedVector3D(const Vector3D& rhs) const;
	// Description:
	// Function to get a inverse vector after multiplying the given vector with this matrix rotated part.
	Vector3D getInverseRotatedVector3D(const Vector3D& rhs) const;

	// Description:
	// Function to get a vector after adding the given vector with this matrix's forth column.
	Vector3D getTranslatedVector3D(const Vector3D& rhs) const;
	// Description:
	// Function to get a inverse vector after adding the given vector with this matrix's forth column.
	Vector3D getInverseTranslatedVector3D(const Vector3D& rhs) const;

	// Description:
	// Function to get a inverse vector after adding the given vector with this matrix's forth column.
	Vector3D vectorMatrixMultiply(const Vector3D& v);			// Vector matrix multiply.
	Vector3D vectorMatrixMultiply3x3(const Vector3D& v);		// Vector matrix multiply 3x3 matrix.
	Vector3D inverseVectorMatrixMultiply3x3(const Vector3D& v);	// Vector inverse multiply.

	// Description:
	// Function to invert the matrix.
	void invert();
	// Description:
	// Function to get a inverse of this matrix.
	Matrix4x4 getInverse() const;
	// Description:
	// Function to make a transpose of this matrix. 
	void transpose();
	// Description:
	// Function to get a transpose of this matrix. 
	Matrix4x4 getTranspose() const;
	// Description:
	// Function to make invert transpose of this matrix. 
	void invertTranspose();
	// Description:
	// Function to get a inverse transpose of this matrix. 
	Matrix4x4 getInverseTranspose(void) const;

	// Description:
	// inverse of a rotation/translation only matrix
	void affineInvert();
	Matrix4x4 getAffineInverse() const;
	void affineInvertTranspose();
	Matrix4x4 getAffineInverseTranspose() const;

	// Function to print the matrix in console.
	void print_M4x4();

	// set to perform an operation on space - removes other entries
	void createTranslation(const Vector3D& translation);
	void createScale(const Vector3D& scaleFactor);
	void createUniformScale(const float scaleFactor);
	void createRotationAxis(const float angle, const Vector3D& axis);
	void createRotationX(const float angle);
	void createRotationY(const float angle);
	void createRotationZ(const float angle);
	void createRotationEuler(const float angleX, const float angleY, const float angleZ);
	void createPerspective(float left, float right, float bottom, float top, float near, float far_);
	void createPerspective(float fovy, float aspect, float n, float f);
	void createOrtho(float left, float right, float bottom, float top, float near, float far_);

	//set parts of the matrix
	void setTranslationColumn(const Vector3D& translation);
	void setRotationEuler(const float angleX, const float angleY, const float angleZ);
	void setRotationEuler(const Vector3D& rotations)
	{ setRotationEuler(rotations.x, rotations.y, rotations.z); }
	void createShadowMatrix(const Vector4D& planeNormal, const Vector4D& lightPos);  // Create a shadow matrix.

	// arithmetic operators
	Matrix4x4 operator+(const Matrix4x4& rhs) const;
	Matrix4x4 operator-(const Matrix4x4& rhs) const;
	Matrix4x4 operator*(const Matrix4x4& rhs) const;
	Matrix4x4 operator*(const float rhs) const;
	Matrix4x4 operator/(const float rhs) const;
	friend Matrix4x4 operator*(float scaleFactor, const Matrix4x4& rhs) { return rhs*scaleFactor; }

	// comparison operators
	bool operator==(const Matrix4x4& rhs) const;
	bool operator!=(const Matrix4x4& rhs) const;

	// assignment operators
	void operator+=(const Matrix4x4& rhs);
	void operator-=(const Matrix4x4& rhs);
	void operator*=(const Matrix4x4& rhs);
	void operator*=(const float rhs);
	void operator/=(const float rhs);

	Matrix4x4 operator-() const;
	Matrix4x4 operator+() const { return (*this); }

	Vector4D operator*(const Vector4D& rhs) const;

	// Operator that only multiply with the rotate part of the matrix, 
	// it doesn't include the translation part (forth column) of the matrix.
	// Meaning that, the given point will be only used to rotate and returned the rotated point.
	Vector3D operator*(const Vector3D& rhs) const;

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const { return (float*)this; }
	operator const float* () const { return (const float*)this; }

	// member variables
	float en[16];
};

};

#endif // Fle_Matrix4x4_h__