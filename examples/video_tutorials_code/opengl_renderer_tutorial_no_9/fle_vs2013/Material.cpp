/*********************************************************************************
created:	2017/06/14   11:19PM
filename: 	Material.cpp
file base:	Material
file ext:	cpp
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

#include "Material.h"

#include <FL/gl.h>

Material::Material()
{
	ambient_color.set(0.05f, 0.05f, 0.05f, 1.0f);
	diffuse_color.set(0.6f, 0.6f, 0.6f, 1.0f);
	specular_color.set(0.0f, 0.0f, 0.0f, 1.0f);
	emission_color.set(0.0f, 0.0f, 0.0f, 1.0f);
	shininess = 128.0f;
}

void Material::render()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambient_color[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse_color[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular_color[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emission_color[0]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Material::reset()
{
	Color4D m_ambi(0.05f, 0.05f, 0.05f, 1.0f);
	Color4D m_diff(0.6f, 0.6f, 0.6f, 0.6f);
	Color4D m_spec(0.0f, 0.0f, 0.0f, 1.0f);
	Color4D m_emis(0.0f, 0.0f, 0.0f, 1.0f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &m_ambi[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &m_diff[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &m_spec[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &m_emis[0]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
}