#pragma once
#ifndef Fle_OpenGLTextActor_h__
#define Fle_OpenGLTextActor_h__

/*********************************************************************************
created:	2017/04/27   03:21PM
filename: 	Fle_OpenGLTextActor.h
file base:	Fle_OpenGLTextActor
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to create text actors in 2D/3D OpenGL scene.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_AbstractOpenGLActor.h"
#include <FLE/Fle_Export.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_Color4D.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_OpenGLTextActor : public Fle_AbstractOpenGLActor
{

public:
	// Description:
	// Constructor to create an actor for rendering.
	Fle_OpenGLTextActor();

	enum DrawType
	{
		TWO_DIM = 0,
		THREE_DIM
	};

	// Description:
	// Function to set the draw type to 2D or 3D.
	void setDrawType(DrawType _t) { m_type = _t; }
	// Description:
	// Function to get the draw type whether 2D or 3D.
	DrawType getDrawType() const { return m_type; }

	// Description:
	// Function to set the text string.
	void setText(const std::string& _s) { m_text = _s; }
	// Description:
	// Function to get the text string.
	std::string getText() const { return m_text; }

	// Description:
	// Function to set the font size (10, 12, 18).
	void setFontSize(int _s) { m_fontsize = _s; }
	// Description:
	// Function to get the font size.
	int setFontSize() const { return m_fontsize; }

private:
	// Description:
	// Virtual function that is expected to be overridden in the derived class for
	// drawing models/shapes.
	void draw() override;

	std::string m_text;
	DrawType m_type;
	int m_fontsize;
	Vector3D m_pos;
};

}

#endif // Fle_OpenGLTextActor_h__