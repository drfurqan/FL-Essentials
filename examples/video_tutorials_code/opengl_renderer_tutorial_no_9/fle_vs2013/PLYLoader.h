#pragma once
#ifndef PLYLoader_h__
#define PLYLoader_h__

/*********************************************************************************
created:	2017/06/09   03:22PM
filename: 	PLYLoader.h
file base:	PLYLoader
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to load 3D PLY file format from the disk.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Math/Fle_Vector2D.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_Color4D.h>
#include <FLE/Math/Fle_FaceIndices3.h>

#include <vector>

using namespace R3D;

class PLYLoader
{
public:
	// Description
	// Static function to load the 3D PLY file.
	static bool load(
		const std::string& _filename,			// name of the file, i.e., "D:\\cube.ply"
		std::vector<Vector3D>& _vertices,		// vertices in x, y, z
		std::vector<Vector3D>& _normals,		// vertex normal in x, y, z
		std::vector<Vector2D>& _texcoord,		// texture coordinates in s, t
		std::vector<Color4D>& _colors,			// vertex color in r, g, b, a
		std::vector<FaceIndices3>& _indices);	// face indices in v1, v2, v3
};

#endif // PLYLoader_h__