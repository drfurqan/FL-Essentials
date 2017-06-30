/*********************************************************************************
created:	2017/06/12   10:12PM
filename: 	Texture.cpp
file base:	Texture
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to create and bind the OpenGL 2D texture.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Texture.h"

#include <FL/gl.h>
#include <FL/glu.h>

Texture2D::Texture2D() : texid(0)
{

}
Texture2D::~Texture2D()
{
	if (glIsTexture(texid))
		glDeleteTextures(1, (GLuint*)&texid);
	texid = 0;
}
bool Texture2D::create(const cv::Mat& _image)
{
	if (_image.empty()) return false;

	GLenum _format = GL_LUMINANCE;
	if (_image.channels() == 1) _format = GL_LUMINANCE;
	else if (_image.channels() == 3) _format = GL_RGB;
	else if (_image.channels() == 4) _format = GL_RGBA;

	if (glIsTexture(texid))
		glDeleteTextures(1, (GLuint*)&texid);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, _image.channels(), _image.cols, _image.rows, 0, _format, GL_UNSIGNED_BYTE, _image.data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, _image.channels(), _image.cols, _image.rows, _format, GL_UNSIGNED_BYTE, _image.data);
	// glGenerateMipmap(GL_TEXTURE_2D);		// new, OpenGL version >= 3.0

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, texid);
}
void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}