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

#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_StringUtil.h>
#include <FLE/Fle_WindowsUtil.h>

#if (_MSC_VER >= 1900)
#include <filesystem>	// for create directory
#endif

using namespace R3D;

cv::Size Fle_ImageUtil::getNewSizeKeepAspectRatio(int _old_w, int _old_h, int _new_w, int _new_h)
{
	int _final_w = 0, _final_h = 0;
	double w2 = _new_h * (_old_w / static_cast<double>(_old_h));
	double h1 = _new_w * (_old_h / static_cast<double>(_old_w));
	if (h1 <= _new_h)
	{
		_final_w = _new_w;
		_final_h = static_cast<int>(h1);
	}
	else
	{
		_final_w = static_cast<int>(w2);
		_final_h = _new_h;
	}
	return cv::Size(_final_w, _final_h);
}

cv::Mat Fle_ImageUtil::getRotatedImage(cv::Mat& _img, float _angle, int _interpolation)
{
	// get rotation matrix for rotating the image around its center.
	cv::Point2f center(_img.cols / 2.f, _img.rows / 2.f);
	cv::Mat rot = cv::getRotationMatrix2D(center, _angle, 1.0);
	// determine bounding rectangle.
	cv::Rect bbox = cv::RotatedRect(center, _img.size(), _angle).boundingRect();
	// adjust transformation matrix.
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	cv::Mat rotated;
	cv::warpAffine(_img, rotated, rot, bbox.size(), _interpolation);

	return rotated;
}

void Fle_ImageUtil::convertToMat(Fl_Image* _img, cv::Mat& _dst, bool _swap_rgb)
{
	if (_img->d() == 0 || _img->d() == 2) return;

	char r, g, b, a;
	for (int y = 0; y < _img->h(); y++)
	{
		for (int x = 0; x < _img->w(); x++)
		{
			long index = (y * _img->w() * _img->d()) + (x * _img->d());
			switch (_img->count())
			{
				case 1:
				{
					const char *buf = _img->data()[0];
					switch (_img->d())
					{
					case 1: // 8bit
					{                                   
						r = g = b = *(buf + index);
						setPixel(_dst, x, y, static_cast<unsigned char>(r));
						break;
					}
					case 3: // 24bit                         
						r = *(buf + index + 0);
						g = *(buf + index + 1);
						b = *(buf + index + 2);
						if(_swap_rgb) setPixel(_dst, x, y, cv::Vec3b(static_cast<unsigned char>(b), static_cast<unsigned char>(g), static_cast<unsigned char>(r)));
						else setPixel(_dst, x, y, cv::Vec3b(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b)));
						
						break;
					case 4: // 32bit
						r = *(buf + index + 0);
						g = *(buf + index + 1);
						b = *(buf + index + 2);
						a = *(buf + index + 3);
						if (_swap_rgb) setPixel(_dst, x, y, cv::Vec4b(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a)));
						else setPixel(_dst, x, y, cv::Vec4b(static_cast<unsigned char>(b), static_cast<unsigned char>(g), static_cast<unsigned char>(r), static_cast<unsigned char>(a)));
						
						break;
					}
					break;
				}
			}
		}
	}
}

cv::Mat Fle_ImageUtil::getMat(Fl_Image* _img, bool _swap_rgb)
{
	cv::Mat m;
	if (_img->d() == 1) m = cv::Mat(cv::Size(_img->w(), _img->h()), CV_8UC1);
	else if (_img->d() == 3) m = cv::Mat(cv::Size(_img->w(), _img->h()), CV_8UC3);
	else if (_img->d() == 4) m = cv::Mat(cv::Size(_img->w(), _img->h()), CV_8UC4);
	convertToMat(_img, m, _swap_rgb);
	return m;
}

bool Fle_ImageUtil::isOpenCVSupportedImage(const std::string& _filename)
{
	std::string ext = Fle_StringUtil::convertToLower(Fle_StringUtil::extractFileExt(_filename));
	if (ext == "jpg" || ext == "jpeg" || ext == "jpe" || ext == "jp2" || ext == "png" || ext == "bmp" || ext == "tif" || ext == "tiff" || ext == "pgm" || ext == "pbm" || ext == "ppm" || ext == "ras" || ext == "sr")
		return true;
	return false;
}

std::vector<std::string> Fle_ImageUtil::getDirectoryFiles(const std::string& _directory, const std::string& _ext)
{
	std::string seprator;
#if defined(_WIN32)
	seprator = "\\";
#else 
	seprator = "/";
#endif

	std::string f = _directory + seprator + "*." + _ext;
	cv::String s(f.c_str());

	std::vector<cv::String> fn;
	cv::glob(s, fn, false);

	std::vector<std::string> files;

	for (std::size_t i = 0; i < fn.size(); i++)
		files.push_back(fn[i]);

	return files;
}
std::vector<std::string> Fle_ImageUtil::getDirectoryImageFiles(const std::string& _directory)
{
	std::vector<std::string> imgs = { 
		"jpg", "JPG", 
		"jpeg", "JPEG", 
		"jpe", "JPE", 
		"jp2", "JP2", 
		"png", "PNG", 
		"bmp", "BMP", 
		"tif", "TIF", 
		"tiff", "TIFF", 
		"pgm", "PGM", 
		"pbm", "PBM", 
		"ppm", "PPM", 
		"ras", "RAS", 
		"sr", "SR" };

	// cv::glob gives sorting file paths, so useless the following method that try not to sort
	// the file paths, it removed all other file paths that are not OpenCV supported images.
	//std::vector<std::string> paths;
	//paths.reserve(100);
	//std::vector<std::string> files = getDirectoryFiles(_path, "*");
	//for (std::size_t i = 0; i < files.size(); i++)
	//{
	//	std::cout << files[i] << std::endl;
	//	for (std::size_t j = 0; j < imgs.size(); j++)
	//	{
	//		if (Fle_StringUtil::extractFileExt(files[i]) == imgs[j])
	//			paths.push_back(files[i]);
	//	}
	//}
	//return paths;

	// this method returns only OpenCV supported file paths.
	std::vector<std::string> files;
	for (std::size_t i = 0; i < imgs.size(); i++)
	{
		std::vector<std::string> f = getDirectoryFiles(_directory, imgs[i]);
		for (std::size_t j = 0; j < f.size(); j++)
		{
			files.push_back(f[j]);
		}
	}
	return files;
}

bool Fle_ImageUtil::batchResize(const std::string& _directory_path, int _w, int _h, bool _with_aspect_ratio, int _interpolation)
{
	if (_directory_path.empty()) return false;
	if (_w < 1 || _h < 1) return false;

	std::vector<std::string> files = Fle_ImageUtil::getDirectoryImageFiles(Fle_StringUtil::extractDirectory(_directory_path));
	if (files.empty()) return false;

	std::string folder_name = "resized";
	std::string seprator;
#if defined(_WIN32)
	seprator = "\\";
#else 
	seprator = "/";
#endif

	if (Fle_WindowsUtil::create_directory(_directory_path + seprator + folder_name)) // create src folder
		std::cout << "New directory has been created, named 'resized'." << std::endl;

	bool b = false;
	for (std::size_t i = 0; i < files.size(); i++)
	{
		cv::Mat src = cv::imread(files[i], CV_LOAD_IMAGE_UNCHANGED);
		if (!src.empty())
		{
			cv::Size s(_w, _h);
			if (_with_aspect_ratio)
				s = Fle_ImageUtil::getNewSizeKeepAspectRatio(src.cols, src.rows, _w, _h);
			cv::resize(src, src, s, 0, 0, _interpolation);
			std::string name = Fle_StringUtil::extractFileNameWithExt(files[i]);
			b = cv::imwrite(_directory_path + seprator + folder_name + seprator + name, src);
#ifdef _DEBUG
			if (b)
				std::cout << i << " - " << _directory_path + seprator + folder_name + seprator + name << std::endl;
#endif // _DEBUG
		}
	}
	return b;
}

std::vector<cv::Mat> Fle_ImageUtil::splitChannels(const cv::Mat& _mat) const
{
	if (_mat.channels() < 1)
		return std::vector<cv::Mat>{};

	auto chan = std::unique_ptr<cv::Mat[]>(new cv::Mat[_mat.channels()]);
	cv::split(_mat, chan.get());

	std::vector<cv::Mat> result{};
	for (int i = 0; i < _mat.channels(); i++)
		result.emplace_back(chan[i]);

	return result;
}
cv::Mat Fle_ImageUtil::mergeChannels(std::vector<cv::Mat> _mats) const
{
	if (_mats.size() <= 0)
		throw std::invalid_argument{ "no input mat" };

	// check
	if (_mats.at(0).channels() != 1)
		throw std::invalid_argument{ "mat 0 not 1 channel" };

	int type = _mats.at(0).type();
	auto size = _mats.at(0).size();

	for (std::size_t i = 1; i < _mats.size(); i++)
	{
		if ((type != _mats.at(i).type()) || (size != _mats.at(i).size()))
			throw std::invalid_argument{ "mats have different sizes or depths. (or not 1 channel)" };
	}

	cv::Mat result{ _mats.at(0).rows, _mats.at(0).cols, _mats.at(0).type() };

	std::unique_ptr<cv::Mat[]> mergeinput(new cv::Mat[_mats.size()]);
	for (std::size_t i = 0; i < _mats.size(); i++)
		mergeinput[i] = _mats.at(i);

	cv::merge(mergeinput.get(), _mats.size(), result);

	return result;
}
