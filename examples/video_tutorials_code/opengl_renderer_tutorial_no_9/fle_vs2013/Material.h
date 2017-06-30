#pragma once
#ifndef Material_h__
#define Material_h__

/*********************************************************************************
created:	2017/06/14   11:19PM
filename: 	Material.h
file base:	Material
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class that can apply material properties to the mesh surface
when lighting is enabled.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Color4D.h>

using namespace R3D;

class Material
{
public:
	// Description:
	// Default constructor.
	Material();

	// Description:
	// Function to render the material.
	void render();

	// Description:
	// Function that resets the material properties to the default value of OpenGL.
	void reset();

	// Description:
	// data members/material components.
	Color4D ambient_color;	// ambient component / global illumination
	Color4D diffuse_color;	// diffuse component / color of the mesh surface
	Color4D specular_color;	// specular component that will create shininess/glossiness
	Color4D emission_color;	// emission component that will create glow effect
	float shininess;		// glossiness ranges [0 ~ 128], higher the number smaller the glossiness and vice versa.
};

#endif // Material_h__