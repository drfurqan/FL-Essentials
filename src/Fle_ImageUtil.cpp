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

#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_StringUtil.h>
#include <FLE/Fle_Timer.h>
#include <FLE/Fle_StatusBar.h>
#include <FLE/Fle_WindowsUtil.h>

#if (_MSC_VER >= 1900)
#include <filesystem>	// for create directory
#endif
#include <memory>

using namespace R3D;

cv::Size Fle_ImageUtil::getNewSizeKeepAspectRatio(int _old_w, int _old_h, int _new_w, int _new_h)
{
	int _final_w, _final_h;
	const auto w2 = _new_h * (_old_w / static_cast<double>(_old_h));
	const auto h1 = _new_w * (_old_h / static_cast<double>(_old_w));
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
cv::Size Fle_ImageUtil::getNewSizeKeepAspectRatio(const cv::Size& _old, const cv::Size& _new)
{
	return getNewSizeKeepAspectRatio(_old.width, _old.height, _new.width, _new.height);
}

cv::Mat Fle_ImageUtil::getRotatedImage(const cv::Mat& _img, const double _angle, const int _interpolation)
{
	cv::Mat dst;
	if (_img.empty())
		return dst;

	if (_angle == 0.)
	{
		dst = _img;
	}
	if (_angle == 90.)
	{
		cv::transpose(_img, dst);
		cv::flip(dst, dst, 0);
	}
	else if (_angle == 180.)
	{
		cv::flip(_img, dst, -1);
	}
	else if (_angle == 270.)
	{
		cv::transpose(_img, dst);
		cv::flip(dst, dst, 1);
	}
	else
	{
		// get rotation matrix for rotating the image around its center.
		const cv::Point2f center(_img.cols / 2.f, _img.rows / 2.f);
		auto rot = cv::getRotationMatrix2D(center, _angle, 1.0);
		auto bbox = cv::RotatedRect(center, _img.size(), float(_angle)).boundingRect();		// determine bounding rectangle.
		rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;							// adjust transformation matrix.
		rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
		cv::warpAffine(_img, dst, rot, bbox.size(), _interpolation);
	}

	return dst;
}

void Fle_ImageUtil::convertToMat(Fl_Image* _img, cv::Mat& _dst, bool _swap_rgb)
{
	if (_img->d() == 0 || _img->d() == 2) return;

	char r, g, b, a;
	for (int y = 0; y < _img->h(); y++)
	{
		for (int x = 0; x < _img->w(); x++)
		{
			const long index = (y * _img->w() * _img->d()) + (x * _img->d());
			switch (_img->count())
			{
				case 1:
				{
					const auto buf = _img->data()[0];
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
					default: ;
					}
					break;
				}
			default: ;
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
	if (_filename.empty())
		return false;

	const auto ext = Fle_StringUtil::convertToLower(Fle_StringUtil::extractFileExt(_filename));
	if (ext == "jpg" || ext == "jpeg" || ext == "jpe" || ext == "jp2" || ext == "png" || ext == "bmp" || ext == "dib" || ext == "tif" || ext == "tiff" || ext == "pgm" || ext == "pbm" || ext == "ppm" || ext == "ras" || ext == "sr" || ext == "webp" || ext == "gif" || ext == "dcm" || ext == "dicom")
		return true;
	return false;
}

std::vector<std::string> Fle_ImageUtil::getDirectoryFiles(const std::string& _directory, const std::vector<std::string>& _filters)
{
	std::vector<std::string> files;
	if (_directory.empty())
		return files;

	std::string dir = _directory;
	if (Fle_StringUtil::endsWith(dir, "\\") || Fle_StringUtil::endsWith(dir, "/"))
		dir = _directory + "*.*";
	else
		dir = _directory + Fle_StringUtil::separator() + "*.*";

	const cv::String s(dir.c_str());

	std::vector<cv::String> fn;
	cv::glob(s, fn, false);
	
	if (_filters.empty())
	{
		files.resize(fn.size());
		std::copy(fn.begin(), fn.end(), files.begin());
	}
	else
	{
		files.reserve(fn.size());
		for (std::size_t i = 0; i < fn.size(); i++)
		{
			bool ok = false;
			const auto ext = Fle_StringUtil::convertToLower(Fle_StringUtil::extractFileExt(fn[i]));
			for (std::size_t j = 0; j < _filters.size(); j++)
			{
				if (ext == _filters[j])
				{
					ok = true;
					break;
				}
			}

			if (ok)
				files.emplace_back(fn[i]);
		}
	}

	return files;
}
std::vector<std::string> Fle_ImageUtil::getDirectoryImageFiles(const std::string& _directory, const std::vector<std::string>& _additional_filters)
{
	if (_directory.empty())
		return std::vector<std::string>();

	int n = 0;
	std::vector<std::string> filters(15);
	filters[n++] = "jpg"; 
	filters[n++] = "jpeg";
	filters[n++] = "jpe"; 
	filters[n++] = "jp2"; 
	filters[n++] = "png"; 
	filters[n++] = "bmp"; 
	filters[n++] = "dib"; 
	filters[n++] = "tif"; 
	filters[n++] = "tiff";
	filters[n++] = "pgm"; 
	filters[n++] = "pbm"; 
	filters[n++] = "ppm"; 
	filters[n++] = "ras"; 
	filters[n++] = "sr";
	filters[n++] = "webp";
	for (const auto& i : _additional_filters)
		filters.emplace_back(i);
	return getDirectoryFiles(_directory, filters);
}

int Fle_ImageUtil::batchResize(const std::string& _directory_path, int _w, int _h, bool _with_aspect_ratio, int _interpolation, const std::vector<std::string>& _additional_filters, Fle_StatusBar* _sb)
{
	if (_directory_path.empty()) return 0;
	if (_w < 2 || _h < 2) return 0;

	auto files = Fle_ImageUtil::getDirectoryImageFiles(_directory_path, _additional_filters);
	if (files.empty()) return 0;

	if (_sb) _sb->showMessage("Resizing! please wait...", 100000);

	auto t = Fle_Timer::getLocalTime("%Y-%m-%d %X");
	auto folder = "Resized-" + t;
	std::replace(folder.begin() + folder.size() - t.size(), folder.end(), ':', '-');
	auto dir = _directory_path + Fle_StringUtil::separator() + folder;

	bool r;
#if (_MSC_VER >= 1900)
	namespace fs = std::filesystem;
	r = fs::create_directories(dir);
#else
	r = Fle_WindowsUtil::create_directory(dir);
#endif

	if (r)
	{
		if (_sb) _sb->showMessage("Resizing and saving! please wait...", 100000);

		auto n = 0;
		for (std::size_t i = 0; i < files.size(); i++)
		{
			auto name = Fle_StringUtil::extractFileNameWithExt(files[i]);
			auto img = cv::imread(files[i], cv::IMREAD_UNCHANGED);
			if (img.empty())
			{
				if (_sb) _sb->showMessage("Couldn't read the image (" + name + ")!", 10);
				continue;
			}

			// opencv doesn't support DCM writing, so just save into jpg.
			auto ext = Fle_StringUtil::extractFileExt(files[i]);
			if (ext == "dcm")
				name += ".jpg";

			// check the depth of the imported image and convert to 8 bit image.
			auto src(img);
			if (src.depth() == CV_16U || src.depth() == CV_16S)
			{
				double min, max;
				cv::minMaxLoc(src, &min, &max);
				src.convertTo(src, CV_8UC1, 255.0 / (max - min), - min * 255.0 / (max - min));
			}

			cv::Size s(_w, _h);
			if (_with_aspect_ratio)
				s = Fle_ImageUtil::getNewSizeKeepAspectRatio(src.cols, src.rows, _w, _h);

			if (_interpolation < 0)
			{
				if (s.width < src.cols || s.height < src.rows)
					cv::resize(src, src, s, 0, 0, cv::InterpolationFlags::INTER_AREA);
				else
					cv::resize(src, src, s, 0, 0, cv::InterpolationFlags::INTER_CUBIC);
			}
			else
			{
				cv::resize(src, src, s, 0, 0, _interpolation);
			}

			std::vector<int> compression_params;
			compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(5);
			if(cv::imwrite(dir + Fle_StringUtil::separator() + name, src, compression_params))
			{
				if (_sb) _sb->showMessage(Fle_StringUtil::to_string(n) + " resized and saved!", 8);
				n++;
			}
		}

		return n;
	}

	return 0;
}
int Fle_ImageUtil::batchInvert(const std::string& _directory_path, const std::vector<std::string>& _additional_filters, Fle_StatusBar* _sb)
{
	if (_directory_path.empty()) return 0;

	auto files = Fle_ImageUtil::getDirectoryImageFiles(_directory_path, _additional_filters);
	if (files.empty()) return 0;

	if (_sb) _sb->showMessage("Inverting! please wait...", 100000);

	auto t = Fle_Timer::getLocalTime("%Y-%m-%d %X");
	auto folder = "Inverted-" + t;
	std::replace(folder.begin() + folder.size() - t.size(), folder.end(), ':', '-');
	auto dir = _directory_path + Fle_StringUtil::separator() + folder;

	bool r;
	#if (_MSC_VER >= 1900)
	namespace fs = std::filesystem;
	r = fs::create_directories(dir);
	#else
	r = Fle_WindowsUtil::create_directory(dir);
	#endif

	if (r)
	{
		if (_sb) _sb->showMessage("Inverting and saving! please wait...", 100000);

		auto n = 0;
		for (std::size_t i = 0; i < files.size(); i++)
		{
			auto name = Fle_StringUtil::extractFileNameWithExt(files[i]);
			auto img = cv::imread(files[i], cv::IMREAD_UNCHANGED);
			if (img.empty())
			{
				if (_sb) _sb->showMessage("Couldn't read the image (" + name + ")!", 10);
				continue;
			}

			// opencv doesn't support DCM writing, so just save into jpg.
			auto ext = Fle_StringUtil::extractFileExt(files[i]);
			if (ext == "dcm")
				name += ".jpg";

			if (img.type() == CV_8UC4)
			{
				cv::Mat dst;
				cv::cvtColor(img, dst, cv::COLOR_BGRA2BGR);

				cv::Mat bit;
				cv::bitwise_not(dst, bit);

				cv::cvtColor(bit, bit, cv::COLOR_BGR2BGRA);

				int from_to[] = { 3, 3 };
				cv::mixChannels({ {img} }, { {bit} }, from_to, 1);

				if (cv::imwrite(dir + Fle_StringUtil::separator() + name, bit))
				{
					if (_sb) _sb->showMessage(Fle_StringUtil::to_string(n) + " inverted and saved!", 8);
					n++;
				}
			}
			else
			{
				// check the depth of the imported image and convert to 8 bit image.
				if (img.depth() == CV_16U || img.depth() == CV_16S)
				{
					double min, max;
					cv::minMaxLoc(img, &min, &max);
					img.convertTo(img, CV_8UC1, 255.0 / (max - min));
				}

				cv::Mat bit;
				cv::bitwise_not(img, bit);
				if (cv::imwrite(dir + Fle_StringUtil::separator() + name, bit))
				{
					if (_sb) _sb->showMessage(Fle_StringUtil::to_string(n) + " inverted and saved!", 8);
					n++;
				}
			}
		}

		return n;
	}

	return 0;
}

void Fle_ImageUtil::autoAdjustBrightnessAndContrast(const cv::Mat& _src, cv::Mat& _dst, float _clipHistPercent)
{
	if (_clipHistPercent < 0)
		return;

	auto histSize = 256;
	auto minGray = 0.0, maxGray = 0.0;

	cv::Mat gray;
	if (_src.type() == CV_8UC1) gray = _src;
	else if (_src.type() == CV_8UC3) cv::cvtColor(_src, gray, cv::COLOR_BGR2GRAY);
	else if (_src.type() == CV_8UC4) cv::cvtColor(_src, gray, cv::COLOR_BGRA2GRAY);
	
	if (_clipHistPercent == 0)		// keep full available range
	{
		cv::minMaxLoc(gray, &minGray, &maxGray);
	}
	else
	{
		// to calculate gray-scale histogram
		cv::Mat hist;
		float range[] = { 0, 256 };
		const float* histRange = { range };
		auto uniform = true;
		auto accumulate = false;
		cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

		// calculate cumulative distribution from the histogram
		std::vector<float> accumulator(histSize);
		accumulator[0] = hist.at<float>(0);
		for (auto i = 1; i < histSize; i++)
			accumulator[i] = accumulator[i - 1] + hist.at<float>(i);

		// locate points that cuts at required value
		auto max = accumulator.back();
		_clipHistPercent *= (max / 100.0);	// make percent as absolute
		_clipHistPercent /= 2.0;			// left and right wings
		// locate left cut
		minGray = 0.0;
		while (accumulator[minGray] < _clipHistPercent)
			minGray++;

		// locate right cut
		maxGray = histSize - 1;
		while (accumulator[maxGray] >= (max - _clipHistPercent))
			maxGray--;
	}

	// current range
	auto inputRange = maxGray - minGray;
	auto alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
	auto beta = -minGray * alpha;				// beta shifts current range so that minGray will go to 0

	// Apply brightness and contrast normalization
	// convertTo operates with saurate_cast
	_src.convertTo(_dst, -1, alpha, beta);

	// restore alpha channel from source 
	if (_dst.type() == CV_8UC4)
	{
		int from_to[] = { 3, 3 };
		cv::mixChannels({ {_src} }, { {_dst} }, from_to, 1);
	}
}

std::vector<cv::Mat> Fle_ImageUtil::splitChannels(const cv::Mat& _mat)
{
	if (_mat.channels() < 1)
		return std::vector<cv::Mat>();

	auto chan = std::unique_ptr<cv::Mat[]>(new cv::Mat[_mat.channels()]);
	cv::split(_mat, chan.get());

	std::vector<cv::Mat> result;
	result.reserve(_mat.channels());
	for (auto i = 0; i < _mat.channels(); i++)
		result.emplace_back(chan[i]);

	return result;
}
cv::Mat Fle_ImageUtil::mergeChannels(const std::vector<cv::Mat>& _mats)
{
	if (_mats.size() <= 0)
		throw std::invalid_argument("invalid input mat.");

	if (_mats.at(0).channels() != 1)
		throw std::invalid_argument("input 0 is not a 1 channel mat.");

	const auto type = _mats.at(0).type();
	const auto size = _mats.at(0).size();

	for (std::size_t i = 1; i < _mats.size(); i++)
	{
		if ((type != _mats.at(i).type()) || (size != _mats.at(i).size()))
			throw std::invalid_argument("mats have different sizes or depths. (or not 1 channel)");
	}

	cv::Mat result(_mats.at(0).rows, _mats.at(0).cols, _mats.at(0).type());

	std::unique_ptr<cv::Mat[]> mergeinput(new cv::Mat[_mats.size()]);
	for (std::size_t i = 0; i < _mats.size(); i++)
		mergeinput[i] = _mats.at(i);

	cv::merge(mergeinput.get(), _mats.size(), result);

	return result;
}
