#pragma once
#ifndef Fle_AbstractOpenGLActor_h__
#define Fle_AbstractOpenGLActor_h__

/*********************************************************************************
created:	2017/04/27   03:21PM
filename: 	Fle_AbstractOpenGLActor.h
file base:	Fle_AbstractOpenGLActor
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Abstract class to create an actor in OpenGL scene.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_Color4D.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_AbstractOpenGLActor
{

public:
	// Description:
	// Constructor to create an actor for rendering.
	Fle_AbstractOpenGLActor();
	// Description:
	// Default destructor.
	virtual ~Fle_AbstractOpenGLActor();

	// Description
	// Function to enable the rendering of this actor.
	void setEnabled(bool _b) { m_enabled = _b; }
	// Description
	// Function that returns true if the rendering of this actor is enabled.
	bool isEnabled() const { return m_enabled; }

	// Description
	// Function to enable the rendering of this actor.
	void setSelected(bool _b) { m_selected = _b; }
	// Description
	// Function that returns true if the rendering of this actor is enabled.
	bool isSelected() const { return m_selected; }

	/************************************************************************/
	/* Apply OpenGL states to this actor                                    */
	/************************************************************************/

	// Description
	// Function to enable or disable lighting for this actor.
	void setLightingEnabled(bool _b) { m_lighting = _b; }
	// Description
	// Function that returns true if lighting for this actor is enabled.
	bool isLightingEnabled() const { return m_lighting; }
	// Description
	// Function to enable or disable the depth test attribute for this actor.
	// If enabled, do depth comparisons and update the depth buffer.
	void setDepthTestEnabled(bool _b) { m_depthtest = _b; }
	// Description
	// Function that returns true if depth test attribute for this actor is enabled.
	bool isDepthTestEnabled() const { return m_depthtest; }
	// Description
	// Function to enable or disable the back-face culling attribute for this actor.
	// If enabled, back-facing polygons will be culled.
	void setBackFaceCullingEnabled(bool _b) { m_cullface = _b; }
	// Description
	// Function that returns true if back-face culling attribute for this actor is enabled.
	bool isBackFaceCullingEnabled() const { return m_cullface; }

	// Description
	// Function to set the point size for this actor.
	void setPointSize(float _ps) { m_pointsize = _ps; }
	// Description
	// Function to get the point size of this actor.
	float getPointSize() const { return m_pointsize; }
	// Description
	// Function to set the line width for this actor.
	void setLineWidth(float _lw) { m_linewidth = _lw; }
	// Description
	// Function to get the line width of this actor.
	float getLineWidth() const { return m_linewidth; }

	/************************************************************************/
	/* Apply transformation to this actor                                   */
	/************************************************************************/

	// Description
	// Function to set the rotation angle for this actor.
	void setRotAngle(float _ang) { m_angle = _ang; }
	// Description
	// Function to get the rotation angle of this actor.
	float getRotAngle() const { return m_angle; }
	// Description
	// Function to set the rotation axis for this actor.
	void setRotAxis(const Vector3D& _axis) { m_axis = _axis; }
	// Description
	// Function to set the rotation axis of this actor.
	Vector3D getRotAxis() const { return m_axis; }
	// Description
	// Function to set translation to this actor.
	void setPosition(const Vector3D& _trans) { m_trans = _trans; }
	// Description
	// Function to get translation of this actor.
	Vector3D getPosition() const { return m_trans; }
	// Description
	// Function to set scaling to this actor.
	void setScale(const Vector3D& _scale) { m_scale = _scale; }
	// Description
	// Function to set scaling of this actor.
	Vector3D getScale() const { return m_scale; }

	/************************************************************************/
	/* Set material properties to this actor                                */
	/************************************************************************/

	// Description
	// Function to set color to this actor.
	void setColor(const Color4D& _color) { setDiffuseColor(_color); }
	// Description
	// Function to get color of this actor.
	Color4D getColor() const { return getDiffuseColor(); }
	// Description
	// Function to set transparency level (in percentage) for this actor.
	void setTransparency(int _transp) { m_diff.setA((100.f - static_cast<float>(_transp)) / 100.f); }
	// Description
	// Function to get transparency level (in percentage) of this actor.
	int getTransparency() const { return (100 - static_cast<int>(m_diff.getA() * 100.f)); }
	// Description
	// Function to set ambient component to this actor.
	void setAmbientColor(const Color4D& _color) { m_ambi = _color; }
	// Description
	// Function to get ambient component of this actor.
	Color4D getAmbientColor() const { return m_ambi; }
	// Description
	// Function to set diffuse component to this actor.
	void setDiffuseColor(const Color4D& _color) { m_diff = _color; }
	// Description
	// Function to get diffuse component of this actor.
	Color4D getDiffuseColor() const { return m_diff; }
	// Description
	// Function to set specular component to this actor.
	void setSpecularColor(const Color4D& _color) { m_spec = _color; }
	// Description
	// Function to get specular component of this actor.
	Color4D getSpecularColor() const { return m_spec; }
	// Description
	// Function to set emission component to this actor.
	void setEmissionColor(const Color4D& _color) { m_emis = _color; }
	// Description
	// Function to get emission component of this actor.
	Color4D getEmissionColor() const { return m_emis; }
	// Description
	// Function to set specular glossiness/shininess.
	void setSpecularShininess(float _s) { m_shininess = _s; }
	// Description
	// Function to get specular glossiness/shininess.
	float getSpecularShininess() const { return m_shininess; }

	/************************************************************************/
	/* Rendering type of this actor.                                        */
	/************************************************************************/

	// Description
	// Rendering type of this actor.
	// What type of actor should be rendered.
	enum RenderType
	{
		Fill = 0,		// solid mode
		Line,			// wireframe mode
		Point			// points mode
	};
	// Description
	// Function to set the render type for this actor, it can be solid, wireframe, or points.
	void setRenderType(RenderType _type) { m_rendertype = _type; }
	// Description
	// Function that returns true if wireframe mode is enabled.
	RenderType getRenderType() const { return m_rendertype; }

	// Description
	// Function to render this actor.
	void render();

private:
	// Description:
	// Virtual function that is expected to be overridden in the derived class for
	// drawing models/shapes.
	virtual void draw() = 0;

protected:
	Vector3D m_axis;
	Vector3D m_trans;
	Vector3D m_scale;
	Color4D m_ambi;
	Color4D m_diff;
	Color4D m_spec;
	Color4D m_emis;
	RenderType m_rendertype;
	float m_shininess;
	float m_angle;
	float m_pointsize;
	float m_linewidth;
	bool m_lighting;
	bool m_depthtest;
	bool m_cullface;
	bool m_enabled;
	bool m_selected;
};

}

#endif // Fle_AbstractOpenGLActor_h__