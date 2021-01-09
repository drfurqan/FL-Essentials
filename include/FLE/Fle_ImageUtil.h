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
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_RGB_Image.H>

#include <opencv2/opencv.hpp>

namespace R3D
{

class Fle_StatusBar;

	// Description:
// Image draw types.
enum Fle_ImageDrawType
{
	Fit = 0,	// image will be fit to windows size.
	Stretch,	// image will be stretched to the window size.
	Center,		// image will be displayed at the center.
};

class FL_ESSENTIALS_EXPORT Fle_ImageUtil
{
public:
	// Description:
	// Function that returns the pixel intensity at _x, _y.
	template <typename DataType>
	static DataType getPixel(cv::Mat& _image, int _x, int _y)
	{
		return _image.at<DataType>(cv::Point(_x, _y));
	}

	// Description:
	// Function to set the color intensity of the (_x, _y) pixel.
	template <typename DataType>
	static void setPixel(cv::Mat& _image, int _x, int _y, const DataType& _p)
	{
		_image.at<DataType>(cv::Point(_x, _y)) = _p;
	}

	// Description:
	// Function to get the X derivative of the given image.
	template <typename DataType, typename ReturnType>
	ReturnType getDerivativeX(const cv::Mat& _img, int _x, int _y)
	{
		ReturnType gradient_in_x =
				_img.at<DataType>(_y - 1, _x - 1) +
			2 * _img.at<DataType>(_y, _x - 1) +
				_img.at<DataType>(_y + 1, _x - 1) -
				_img.at<DataType>(_y - 1, _x + 1) -
			2 * _img.at<DataType>(_y, _x + 1) -
				_img.at<DataType>(_y + 1, _x + 1);
		return gradient_in_x;
	}

	// Description:
	// Function to get the Y derivative of the given image.
	template <typename DataType, typename ReturnType>
	ReturnType getDerivativeY(const cv::Mat& _img, int _x, int _y)
	{
		ReturnType gradient_in_y =
				_img.at<DataType>(_y - 1, _x - 1) +
			2 * _img.at<DataType>(_y - 1, _x) +
				_img.at<DataType>(_y - 1, _x + 1) -
				_img.at<DataType>(_y + 1, _x - 1) -
			2 * _img.at<DataType>(_y + 1, _x) -
				_img.at<DataType>(_y + 1, _x + 1);
		return gradient_in_y;
	}

	// Description:
	// Function to get the new dimensions of the image with the same aspect ratio.
	static cv::Size getNewSizeKeepAspectRatio(int _old_w, int _old_h, int _new_w, int _new_h);
	static cv::Size getNewSizeKeepAspectRatio(const cv::Size& _old, const cv::Size& _new);

	// Description:
	// Function to get a rotated image.
	// Specify angle in degrees.
	static cv::Mat getRotatedImage(const cv::Mat& _img, const double _angle, const int _interpolation = cv::InterpolationFlags::INTER_LINEAR);

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
	static bool isOpenCVSupportedImage(const std::string& _filename);
	// Description:
	// Function to get files in a directory.
	// Example:
	// getDirectoryFilesFiltered("D:\\test\\", {});	 // returns all files in the given directory.
	// getDirectoryFilesFiltered("D:\\test\\", {"jpg", "png"}); // returns only jpg and png files in the given directory.
	static std::vector<std::string> getDirectoryFiles(const std::string& _directory, const std::vector<std::string>& _filters = std::vector<std::string>());
	// Description:
	// Function to get all OpenCV supported image files in a directory.
	// 	"jpg" | "jpeg" | "jpe" | "jp2" |"png" | "bmp" | "dib" | "tif" | "tiff" | "pgm" | "pbm" | "ppm" | "ras" |"sr" | "webp" | "gif" | "dcm")
	// Example:
	// getDirectoryImageFiles("D:\\test\\");
	// _additional_filters = {"gif", "dcm"} to add more filters
	static std::vector<std::string> getDirectoryImageFiles(const std::string& _directory, const std::vector<std::string>& _additional_filters = {});

	// Description:
	// Function to resize all image files of the specified directory.
	// _w and _h is the new size of the images.
	// set _with_aspect_ratio to true if images need to be resized with aspect ratio.
	// set _hasDICOM to true if opencv is built with gdcm lib.
	// It returns totally number of resized images.
	// If _interpolation -1 => auto resizing interpolation is used, otherwise the specifed interpolation.
	static int batchResize(const std::string& _directory_path, int _w, int _h, bool _with_aspect_ratio = true, int _interpolation = -1, const std::vector<std::string>& _additional_filters = {}, Fle_StatusBar* _sb = nullptr);
	// Description:
	// Function to invert all image files of the specified directory.
	// set _hasDICOM to true if opencv is built with gdcm lib.
	// It returns totally number of resized images.
	static int batchInvert(const std::string& _directory_path, const std::vector<std::string>& _additional_filters = {}, Fle_StatusBar* _sb = nullptr);

	// Description:
	// Function to perform auto brightness and contrast optimization with optional histogram clipping.
	// _clipHistPercent cut wings of histogram at given percent.
	static void autoAdjustBrightnessAndContrast(const cv::Mat& _src, cv::Mat& _dst, float _clipHistPercent = 0.f);

	// Description:
	// Function to split channels from the given mat.
	static std::vector<cv::Mat> splitChannels(const cv::Mat& _mat);
	// Description:
	// Function to merge the given channels.
	static cv::Mat mergeChannels(const std::vector<cv::Mat>& _mats);
};

template void Fle_ImageUtil::setPixel<unsigned char>(cv::Mat& _image, int _x, int _y, const unsigned char& _p);
template void Fle_ImageUtil::setPixel<cv::Vec2b>(cv::Mat& _image, int _x, int _y, const cv::Vec2b& _p);
template void Fle_ImageUtil::setPixel<cv::Vec3b>(cv::Mat& _image, int _x, int _y, const cv::Vec3b& _p);
template void Fle_ImageUtil::setPixel<cv::Vec4b>(cv::Mat& _image, int _x, int _y, const cv::Vec4b& _p);

}

#endif // Fle_ImageUtil_h__