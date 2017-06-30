#pragma once
#ifndef Texture_h__
#define Texture_h__

/*********************************************************************************
created:	2017/06/12   10:12PM
filename: 	Texture.h
file base:	Texture
file ext:	h
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

#include <opencv2/opencv.hpp>

class Texture2D
{
public:
	// Description:
	// Default constructor.
	Texture2D();
	// Description:
	// Destructor that destroys the texture.
	~Texture2D();

	// Description:
	// Function to create a 2D texture and upload to GPU.
	// _image is the input image/texture.
	// It returns true if texture is successfully created.
	bool create(const cv::Mat& _image);

	// Description:
	// Function to bind the texture.
	void bind();
	// Description:
	// Function to unbind the texture.
	void unbind();

	// Description:
	// Function that returns true if a texture has been created, otherwise false.
	bool hasTexture() const { return texid == 1 ? true : false; }

private:
	unsigned int texid;		// created texture id.
};

#endif // Texture_h__