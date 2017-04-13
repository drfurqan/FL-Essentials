/*********************************************************************************
created:	2017/04/13   06:37PM
filename: 	triangles_and_indexed_based_rendering.cpp
file base:	triangles_and_indexed_based_rendering
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	In this tutorial, I have described the importance of triangles in 3D Computer 
			Graphics and why we use triangles to model 3D objects in CG. Total seven properties are
			described and some of them are computed using mathematical equations and 3D math library.
			3D math library that provides by FLE, contains classes for 2D/3D/4D vectors,
			matrix4x4, triangle/face indices, and color4.

			This tutorial explains the indexed based rendering of a mesh in OpenGL. 
			A data structure for a triangular circle is created that has vertices/points,
			indices/faces, and normals. After that, the circle is rendered using the computed
			vertices, normals, and the assigned indices. Clockwise, and counter-clockwise
			triangles/faces are explained and visually implemented with OpenGL Lighting.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>

#include "triangles_and_indexed_based_rendering.h"

#include <iostream>

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	MyOpenGLWindow win(900, 500, "3D Model Manipulation in OpenGL");
	win.show();

	Vector3D P1(-2, 0, 0);
	Vector3D P3(0, 4, 0);
	Vector3D P2(2, 0, 0);

	Vector3D v1 = P2 - P1;
	Vector3D v2 = P3 - P1;

	Vector3D n = v1.cross(v2);
	n.normalize();
	n.print();

	float angle = v1.getAngleBetween(v2);
	std::cout << angle * 180/3.14 << std::endl;

	Vector3D area = v1.cross(v2) / 2;
	area.print();


	// execute the main loop.
	return Fle_Core::exec();
}