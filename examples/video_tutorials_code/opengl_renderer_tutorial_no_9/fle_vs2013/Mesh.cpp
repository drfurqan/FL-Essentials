/*********************************************************************************
created:	2017/06/09   03:27PM
filename: 	Mesh.cpp
file base:	Mesh
file ext:	cpp
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

#include "Mesh.h"

#include <FL/gl.h>
#include <FL/glu.h>

Mesh::Mesh() : is_flat_rendering(true)
{

}
Mesh::~Mesh()
{
	clear();
}

void Mesh::clear()
{
	vertices.clear();
	vert_normals.clear();
	texture_coord.clear();
	colors.clear();
	face_normals.clear();
	indices.clear();
}

void Mesh::computeFaceNormals()
{
	if (indices.empty() || vertices.empty()) return;

	Vector3D v1, v2, v3, n;
	face_normals.clear();
	face_normals.resize(indices.size());

	std::memset(face_normals.data(), 0, sizeof(Vector3D) * face_normals.size());
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		v1 = vertices[indices[i].V3()];
		v2 = vertices[indices[i].V2()];
		v3 = vertices[indices[i].V1()];
		n = (v3 - v2).cross(v1 - v2);
		n.normalize();
		face_normals[i].set(n);
	}
}

void Mesh::render()
{
	if (indices.empty() || vertices.empty()) return;

	glBegin(GL_TRIANGLES);

	for (std::size_t i = 0; i < indices.size(); i++)
	{
		unsigned int V1 = indices[i].v1;
		unsigned int V2 = indices[i].v2;
		unsigned int V3 = indices[i].v3;


		if (is_flat_rendering)
		{
			//if (!face_normals.empty()) glNormal3f(face_normals[i].x, face_normals[i].y, face_normals[i].z);
			//if (!texture_coord.empty()) glTexCoord2f(texture_coord[V1].x, texture_coord[V1].y);
			//glVertex3f(vertices[V1].x, vertices[V1].y, vertices[V1].z);
			//if (!texture_coord.empty()) glTexCoord2f(texture_coord[V2].x, texture_coord[V2].y);
			//glVertex3f(vertices[V2].x, vertices[V2].y, vertices[V2].z);
			//if (!texture_coord.empty()) glTexCoord2f(texture_coord[V3].x, texture_coord[V3].y);
			//glVertex3f(vertices[V3].x, vertices[V3].y, vertices[V3].z);

			// OR

			// face or triangle normal
			if (!face_normals.empty()) glNormal3fv((float*)&face_normals[i]);

			// face or triangle
			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V1]);
			if (!colors.empty()) glColor4fv((float*)&colors[V1]);
			glVertex3fv((float*)&vertices[V1]);

			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V2]);
			if (!colors.empty()) glColor4fv((float*)&colors[V2]);
			glVertex3fv((float*)&vertices[V2]);

			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V3]);
			if (!colors.empty()) glColor4fv((float*)&colors[V3]);
			glVertex3fv((float*)&vertices[V3]);
		}
		else
		{
			// each vertex of a face or triangle has a normal for smooth shading
			if (!vert_normals.empty()) glNormal3fv((float*)&vert_normals[V1]);
			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V1]);
			if (!colors.empty()) glColor4fv((float*)&colors[V1]);
			glVertex3fv((float*)&vertices[V1]);

			if (!vert_normals.empty()) glNormal3fv((float*)&vert_normals[V2]);
			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V2]);
			if (!colors.empty()) glColor4fv((float*)&colors[V2]);
			glVertex3fv((float*)&vertices[V2]);

			if (!vert_normals.empty()) glNormal3fv((float*)&vert_normals[V3]);
			if (!texture_coord.empty()) glTexCoord2fv((float*)&texture_coord[V3]);
			if (!colors.empty()) glColor4fv((float*)&colors[V3]);
			glVertex3fv((float*)&vertices[V3]);
		}
	}

	glEnd();
}