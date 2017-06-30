/*********************************************************************************
created:	2017/06/12   010:27PM
filename: 	Actors.cpp
file base:	Actors
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	classes to render OpenGL actors.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Actors.h"

#include <FL/gl.h>

/************************************************************************/
/* class for grid                                                       */
/************************************************************************/
Grid2D::Grid2D() : m_ngrids(40.f), m_scale(50.f)
{
}
void Grid2D::draw()
{
	int half_size = int(m_ngrids / 2);
	glBegin(GL_LINES);
	for (int i = -half_size; i <= half_size; i++)
	{
		glVertex3f(float(i) * m_scale, 0.f, float(-half_size)* m_scale);
		glVertex3f(float(i) * m_scale, 0.f, float(half_size) * m_scale);

		glVertex3f(float(-half_size)* m_scale, 0.f, float(i) * m_scale);
		glVertex3f(float(half_size) * m_scale, 0.f, float(i) * m_scale);
	}
	glEnd();
}

/************************************************************************/
/* class for 3D axis                                                    */
/************************************************************************/
Axis3D::Axis3D() : m_size(20.0f)
{

}
void Axis3D::draw()
{
	glBegin(GL_LINES);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-m_size, 0.f, 0.f);
	glVertex3f(m_size, 0.f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, -m_size, 0.f);
	glVertex3f(0.f, m_size, 0.f);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, -m_size);
	glVertex3f(0.f, 0.f, m_size);

	glEnd();
}