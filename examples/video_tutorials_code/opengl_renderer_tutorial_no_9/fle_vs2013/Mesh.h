#pragma once
#ifndef Mesh_h__
#define Mesh_h__

/*********************************************************************************
created:	2017/06/09   03:27PM
filename: 	Mesh.h
file base:	Mesh
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to render a 2D/3D meshes.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Vector2D.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_FaceIndices3.h>
#include <FLE/Math/Fle_Color4D.h>

#include "Material.h"
#include "Texture.h"

using namespace R3D;

class Mesh
{
public:
	Mesh();
	~Mesh();

	// Description:
	// Function to clear the mesh data.
	void clear();

	// Description:
	// Function to compute the face normals.
	void computeFaceNormals();

	// Description:
	// Function to render this mesh using the vertex and face attributes.
	void render();

	// Description:
	// vertex attributes.
	std::vector<Vector3D> vertices;			// vertices
	std::vector<Vector3D> vert_normals;		// vertices normals
	std::vector<Vector2D> texture_coord;	// texture coordinates
	std::vector<Color4D> colors;			// vertices color

	// Description:
	// face attributes.
	std::vector<Vector3D> face_normals;		// face normals
	std::vector<FaceIndices3> indices;		// face indices

	// Description:
	// mesh can have material color and a texture.
	Material material;
	Texture2D texture;

	bool is_flat_rendering;	 // if it is false, smooth/Gouraud rendering will be turned on, otherwise flat.
};

#endif // Mesh_h__