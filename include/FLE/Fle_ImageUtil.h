#pragma once
#ifndef Fle_ImageUtil_h__
#define Fle_ImageUtil_h__

/*********************************************************************************
created:	2017/01/27   04:25AM
filename: 	Fle_ImageUtil.h
file base:	Fle_ImageUtil
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class with general functions for image processing.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_RGB_Image.H>

#include <opencv2/opencv.hpp>

namespace R3D
{
// Description:
// Image draw types.
enum class Fle_ImageDrawType
{
	Fit = 0,	// image will be fit to windows size.
	Stretch,	// image will be stretched to the window size.
	Center,		// image will be displayed at the center.
};

class FL_ESSENTIALS_EXPORT Fle_ImageUtil
{
public:
	// Description:
	// Function to return the pixel intensity (of a grayscale or black&white image) at _x, _y.
	static unsigned char getPixelGrayscale(cv::Mat& _image, int _x, int _y)
	{
		return _image.at<unsigned char>(cv::Point(_x, _y));
	}
	// Description:
	// Function to return the pixel intensity with alpha component
	// (of a grayscale or black&white image) at _x, _y.
	static cv::Vec2b getPixelGA(cv::Mat& _image, int _x, int _y)
	{
		return _image.at<cv::Vec2b>(cv::Point(_x, _y));
	}
	// Description:
	// Function to return the pixel intensity (of a color image) at _x, _y.
	static cv::Vec3b getPixelBGR(cv::Mat& _image, int _x, int _y)
	{
		return _image.at<cv::Vec3b>(cv::Point(_x, _y));
	}
	// Description:
	// Function to return the pixel intensity (of a color image with alpha component) at _x, _y.
	static cv::Vec4b getPixelBGRA(cv::Mat& _image, int _x, int _y)
	{
		return _image.at<cv::Vec4b>(cv::Point(_x, _y));
	}

	// Description:
	// Function to set the color intensity of the (_x, _y) pixel.
	// This function is for grayscale or black&white image.
	static void setPixel(cv::Mat& _image, int _x, int _y, unsigned char _p)
	{
		_image.at<unsigned char>(cv::Point(_x, _y)) = _p;
	}
	// Description:
	// Function to set the color intensity of the (_x, _y) pixel.
	// This function is for grayscale or black&white image that has 2 components grayscale and alpha.
	static void setPixel(cv::Mat& _image, int _x, int _y, const cv::Vec2b& _ga)
	{
		_image.at<cv::Vec2b>(cv::Point(_x, _y)) = _ga;
	}
	// Description:
	// Function to set the color intensity of the (_x, _y) pixel.
	// This function is for color image that has 3 components BGR (Blue, Green, Red).
	static void setPixel(cv::Mat& _image, int _x, int _y, const cv::Vec3b& _bgr)
	{
		_image.at<cv::Vec3b>(cv::Point(_x, _y)) = _bgr;
	}
	// Description:
	// Function to set the color intensity of the (_x, _y) pixel.
	// This function is for color image that has 4 components BGRA (Blue, Green, Red, Alpha).
	static void setPixel(cv::Mat& _image, int _x, int _y, const cv::Vec4b& _bgra)
	{
		_image.at<cv::Vec4b>(cv::Point(_x, _y)) = _bgra;
	}

	// Description:
	// Function to get the new dimensions of the image with the same aspect ratio.
	static cv::Size getNewSizeKeepAspectRatio(int _old_w, int _old_h, int _new_w, int _new_h);

	// Description:
	// Function to get a rotated.
	// Specify angle in degrees.
	static cv::Mat getRotatedImage(cv::Mat& _img, float _angle, int _interpolation = cv::INTER_CUBIC);
	// Description:
	// Function to copy FLTK image to OpenCV mat format.
	// Red and blue will be swapped if _swap_rgb is true.
	// Fl_RGB_Image* img = ...;
	// cv::Mat m;
	// if (img->d() == 1) m = cv::Mat(cv::Size(img->w(), img->h()), CV_8UC1);
	// else if (img->d() == 3) m = cv::Mat(cv::Size(img->w(), img->h()), CV_8UC3);
	// else if (img->d() == 4) m = cv::Mat(cv::Size(img->w(), img->h()), CV_8UC4);
	// Fle_ImageUtil::convertToMat(img, m);
	// cv::imshow("Hle", m);
	static void convertToMat(Fl_Image* _img, cv::Mat& _dst, bool _swap_rgb = true);
	// Description:
	// Function to get OpenCV mat from FLTK image.
	// Red and blue will be swapped if _swap_rgb is true.
	static cv::Mat getMat(Fl_Image* img, bool _swap_rgb = true);

	// Description:
	// Function that returns true if the input file is supported by OpenCV images i.e, jpg, bmp, png, etc.
	static bool openCVSupportedImage(const std::string& _filename);
	// Description:
	// Function to get files in a directory.
	// Example:
	// getDirectoryFiles(Fle_StringUtil::extractDirectory(file), "*");
	static std::vector<std::string> getDirectoryFiles(const std::string& _path, const std::string& _ext);
	// Description:
	// Function to get all OpenCV supported image files in a directory.
	// Example:
	// getDirectoryFiles(Fle_StringUtil::extractDirectory(file), "*");
	static std::vector<std::string> getDirectoryImageFiles(const std::string& _path);

	// Description:
	// Function to resize all image files of the specified directory.
	// _w and _h is the new size of the images.
	// set _with_aspect_ratio to true if images need to be resized with aspect ratio.
	// Note: _directory_path should end with "\\".
	static bool batchResize(const std::string& _directory_path, int _w, int _h, bool _with_aspect_ratio = true, int _interpolation = CV_INTER_CUBIC);
};

}

#endif // Fle_ImageUtil_h__