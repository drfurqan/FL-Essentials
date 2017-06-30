#pragma once
#ifndef Actors_h__
#define Actors_h__

/*********************************************************************************
created:	2017/06/12   010:27PM
filename: 	Actors.h
file base:	Actors
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Classes to render simplest OpenGL actors.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_AbstractOpenGLActor.h>

using namespace R3D;

/************************************************************************/
/* class for grid                                                       */
/************************************************************************/
class Grid2D : public Fle_AbstractOpenGLActor
{
public:
	Grid2D();

	// Description
	// Function to set the scale factor to resize the grid.
	void setScale(float _s) { m_scale = _s; }
	// Description
	// Function to get the scale factor.
	float getScale() const { return m_scale; }

	// Description
	// Function to set the number of grids to be rendered.
	void setNGrids(float _n) { m_ngrids = _n; }
	// Description
	// Function to get the number of grids.
	float getNGrids() const { return m_ngrids; }

private:
	void draw();	// overridden function that render grid.

	float m_scale;
	float m_ngrids;
};

/************************************************************************/
/* class for 3D axis                                                    */
/************************************************************************/
class Axis3D : public Fle_AbstractOpenGLActor
{
public:
	// Description
	// Default constructor.
	Axis3D();

	// Description
	// Function to set the axis size.
	void setSize(float _s) { m_size = _s; }
	// Description
	// Function to get the axis size.
	float getSize() const { return m_size; }

private:
	void draw();	// overridden function that render 3D axis.

	float m_size;
};

#endif // Actors_h__