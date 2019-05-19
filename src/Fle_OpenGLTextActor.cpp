/*********************************************************************************
created:	2017/04/27   03:21PM
filename: 	Fle_OpenGLTextActor.cpp
file base:	Fle_OpenGLTextActor
file ext:	cpp
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

#include <FLE/Fle_OpenGLTextActor.h>

#include <FL/gl.h>
#include <FL/glut.h>

using namespace R3D;

void __drawGlutText(char* _string, int _size)
{
	for (char* p = _string; *p; p++)
	{
		if (_size <= 10) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p);
		else if (_size == 12) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
		else if (_size > 12) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	}
}

void __draw2D(char* _text, int _x, int _y, int _fontsize)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glPushAttrib(GL_TRANSFORM_BIT | GL_VIEWPORT_BIT | GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		{
			glLoadIdentity();
			glOrtho(0, viewport[2], 0, viewport[3], -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			{
				glLoadIdentity();
				glDisable(GL_FOG);
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_TEXTURE_2D);

				glRasterPos2i(_x, _y);
				__drawGlutText(_text, _fontsize);
			}
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
		}
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopAttrib();
}

void __draw3D(char* _text, float _x, float _y, float _z, int _fontsize)
{
	glDisable(GL_FOG);
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);

	glRasterPos3f(_x, _y, _z);
	__drawGlutText(_text, _fontsize);
}

Fle_OpenGLTextActor::Fle_OpenGLTextActor() :
	m_text(""),
	m_type(THREE_DIM),
	m_fontsize(10)
{
	setLightingEnabled(false);
	setDepthTestEnabled(false);
}

void Fle_OpenGLTextActor::draw()
{
	if (m_text.empty()) 
		return;

	if (m_type == TWO_DIM)
		__draw2D(const_cast<char*>(m_text.c_str()), m_trans.x, m_trans.y, m_fontsize);
	else
		__draw3D(const_cast<char*>(m_text.c_str()), 0.f, 0.f, 0.f, m_fontsize);
}