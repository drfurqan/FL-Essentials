#pragma once
#ifndef Fle_ImageWidget_h__
#define Fle_ImageWidget_h__

/*********************************************************************************
created:	2017/01/30   12:51AM
filename: 	Fle_ImageWidget.h
file base:	Fle_ImageWidget
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image widget with load, save, zoom/pan support.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageUtil.h>
#include <FL/Fl_Widget.H>

#include <opencv2/opencv.hpp>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ImageWidget : public Fl_Widget
{
public:
	// Description:
	// Constructor to create a image widget inside the parent window.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_ImageWidget(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_ImageWidget();

	// Description:
	// Function to set background as an image of the given color.
	void clear(Fl_Color _color);

	// Description:
	// Function to set an image as background.
	void setImage(const cv::Mat& _image);
	// Description:
	// Function to get a clone of the background image.
	cv::Mat getImage() const;
	// Description:
	// Function to load an image from the given file path.
	// _filename should a file name plus extension.
	// Region of Interest (ROI) will be reset to the loaded image size if
	// the second argument is true, otherwise previous ROI will be used to
	// draw the image.
	// Default ROI is Rect(0, 0, 0, 0) means the full image size.
	bool loadImage(const std::string& _filename, bool _reset_roi = true);
	// Description:
	// Function to load an image from the path specified by setFilePath();
	bool loadImage(bool _reset_roi = true);
	// Description:
	// Function to save the current image to disk.
	// example:
	// vector<int> compression_params;
	// compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	// compression_params.push_back(9);
	// saveImage("D:\\a.png", compression_params);
	bool saveImage(const std::string& _filename, const std::vector<int>& _compression_params = std::vector<int>());
	// Description:
	// Function to save the current loaded image to disk.
	// example:
	// vector<int> compression_params;
	// compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	// compression_params.push_back(9);
	// saveImage(compression_params);
	bool saveImage(const std::vector<int>& _compression_params = std::vector<int>());

	// Description:
	// Function to set the file path used for loadImage().
	// _filename should a file name plus extension.
	void setFileLocation(const std::string& _filename) { m_filename = _filename; }
	// Description:
	// Function to get the file path used for loadImage().
	std::string getFileLocation() const { return m_filename; }

	// Description:
	// Function to get the loaded image size.
	cv::Size getImageSize() const;

	// Description:
	// Function to set the region of interest for the image to be displayed.
	void setRoi(const cv::Rect& _roi);
	// Description:
	// Function to get the region of interest.
	cv::Rect getRoi() const;
	// Description:
	// Function to reset the region of interest to display the full image size.
	void resetRoi();

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// drawing FLTK widgets such as 
	void draw() override;
	// Description:
	// Overloaded function that is being called inside the draw() function.
	void drawImage(const int _x, const int _y, const int _w, const int _h);

	std::string m_filename;
	cv::Mat m_image;
	cv::Rect m_roi;
};

}

#endif // Fle_ImageWidget_h__