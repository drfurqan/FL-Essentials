/*********************************************************************************
created:	2017/04/27   03:21PM
filename: 	Fle_AbstractOpenGLActor.cpp
file base:	Fle_AbstractOpenGLActor
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class to create an actor in OpenGL scene.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_AbstractOpenGLActor.h>

#include <FL/gl.h>

using namespace R3D;

Fle_AbstractOpenGLActor::Fle_AbstractOpenGLActor() : 
	m_rendertype(RenderType::Fill),
	m_shininess(60.f),
	m_angle(0.f),
	m_pointsize(1.2f),
	m_linewidth(1.f),
	m_lighting(false),
	m_depthtest(true),
	m_cullface(true),
	m_enabled(true),
	m_selected(false)
{
	m_axis.set(0.f, 0.f, 0.f);
	m_trans.set(0.f, 0.f, 0.f);
	m_scale.set(1.f, 1.f, 1.f);

	m_ambi.set(0.2f, 0.2f, 0.2f, 1.f);
	m_diff.set(0.8f, 0.8f, 0.8f, 1.f);
	m_spec.set(0.3f, 0.3f, 0.3f, 1.f);
	m_emis.set(0.0f, 0.0f, 0.0f, 1.f);
}

Fle_AbstractOpenGLActor::~Fle_AbstractOpenGLActor()
{
}

void Fle_AbstractOpenGLActor::render() 
{
	if (!m_enabled)
		return;

	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT);
	{
		if (m_depthtest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		if (m_lighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);

		if (m_cullface)
		{
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}
		else
			glDisable(GL_CULL_FACE);

		glLineWidth(m_linewidth);
		glPointSize(m_pointsize);

		if(m_rendertype == Fle_AbstractOpenGLActor::RenderType::Fill)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// line/wireframe mode
		else if (m_rendertype == Fle_AbstractOpenGLActor::RenderType::Line)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// fill/solid mode
		else if (m_rendertype == Fle_AbstractOpenGLActor::RenderType::Point)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);		// fill/solid mode

		// apply material properties when lighting is enabled.
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &m_ambi[0]);	
		if (m_selected)
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &Color4D(1.f, 0.f, 0.f, m_diff.a)[0]);
		else
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &m_diff[0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &m_spec[0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &m_emis[0]);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

		// if lighting is disabled only then glColorf will work, otherwise it is ignored.
		if (m_selected)
			glColor4fv(&Color4D(1.f, 0.f, 0.f, m_diff.a)[0]);
		else
			glColor4fv(&m_diff[0]);

		if (m_diff.a < 1.f)	// check the alpha channel for transparency.
		{
			glEnable(GL_BLEND);	// enable blending for transparency.
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glPushMatrix();
		glTranslatef(m_trans.x, m_trans.y, m_trans.z);
		glRotatef(m_angle, m_axis.x, m_axis.y, m_axis.z);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		draw();
		glPopMatrix();
	}
	glPopAttrib();
}

void Fle_AbstractOpenGLActor::draw()
{
}