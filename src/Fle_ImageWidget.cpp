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

#include <FLE/Fle_ImageWidget.h>
#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_StringUtil.h>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <FL/Fl_GIF_Image.H>

using namespace R3D;

Fle_ImageWidget::Fle_ImageWidget(int _x, int _y, int _w, int _h, const char* _title) :
	Fl_Widget(_x, _y, _w, _h, _title),
	m_roi(cv::Rect(0, 0, 0, 0))
{
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_ImageWidget::~Fle_ImageWidget()
{
}
void Fle_ImageWidget::clear(Fl_Color _color)
{
	int r = (_color & 0xFF000000) >> 24;
	int g = (_color & 0x00FF0000) >> 16;
	int b = (_color & 0x0000FF00) >> 8;

	cv::Mat m(cv::Size(640, 480), CV_8UC3);
	for (int y = 0; y < m.rows; y++)
		for (int x = 0; x < m.cols; x++)
			m.at<cv::Vec3b>(cv::Point(x, y)) = cv::Vec3b(b, g, r);

	setImage(m);
	resetRoi();
	redraw();
}

void Fle_ImageWidget::draw()
{
	drawImage(x(), y(), w(), h());
}
void Fle_ImageWidget::drawImage(const int _x, const int _y, const int _w, const int _h)
{	
	if (m_image.empty()) 
		return;

	cv::Mat fimage;
	if ((m_roi.x < 0) || (m_roi.y < 0) ||
		((m_roi.x + m_roi.width) > m_image.cols) ||
		((m_roi.y + m_roi.height) > m_image.rows) ||
		(m_roi.width < 2) ||
		(m_roi.height < 2))
	{
		fimage = m_image.clone();
	}
	else
	{
		fimage = cv::Mat(m_image, m_roi).clone();
	}

	const int channel = fimage.channels();
	const int d = fimage.depth();

	if(d == CV_16U || d == CV_16S)		// 16 bit images
	{
		double min, max;
		cv::minMaxLoc(fimage, &min, &max);
		fimage.convertTo(fimage, CV_8UC1, 255.0 / (max - min));
	}

	if (_w < fimage.cols || _h < fimage.rows)
		cv::resize(fimage, fimage, cv::Size(_w, _h), 0, 0, cv::INTER_AREA);
	else
		cv::resize(fimage, fimage, cv::Size(_w, _h), 0, 0, cv::INTER_LINEAR);

	if (channel == 4) cv::cvtColor(fimage, fimage, cv::COLOR_BGRA2RGBA);
	else if (channel == 3) cv::cvtColor(fimage, fimage, cv::COLOR_BGR2RGB);

	fl_push_clip(_x, _y, fimage.cols, fimage.rows);

	if (channel <= 3)
	{
		// fl_draw_image does not support (4-channels) transparent images like PNG. 
		// It only support RGB (3-channels).
		fl_draw_image(fimage.datastart, _x, _y, fimage.cols, fimage.rows, fimage.channels(), static_cast<int>(fimage.step));	// faster
	}
	else
	{
		Fl_RGB_Image o(fimage.datastart, fimage.cols, fimage.rows, fimage.channels(), static_cast<int>(fimage.step));
		o.draw(_x, _y);	// Fl_RGB_Image works fine with the transparent PNG images.
	}
	
	fl_pop_clip();
}

bool Fle_ImageWidget::loadImage(const std::string& _filename, bool _reset_roi)
{
	if (_filename.empty())
		return false;

	std::string ext = Fle_StringUtil::convertToLower(Fle_StringUtil::extractFileExt(_filename));

	try
	{
		if (ext == "gif")
		{
			// loads the first image of the gif file.
			Fl_GIF_Image gif(_filename.c_str());
			if (gif.fail() < 0)
				return false;

			Fl_RGB_Image o(&gif);
			int type = CV_8UC3;
			if (o.d() == 1)	type = CV_8UC1;
			else if (o.d() == 2)	type = CV_8UC2;
			else if (o.d() == 3)	type = CV_8UC3;
			else if (o.d() == 4)	type = CV_8UC4;
			cv::Mat m(cv::Size(o.w(), o.h()), type);
			Fle_ImageUtil::convertToMat(&o, m, false);

			setFileLocation(_filename);
			setImage(m);
			if (_reset_roi)
				resetRoi();
			return true;
		}
		else
		{
			cv::Mat img = cv::imread(_filename, cv::IMREAD_UNCHANGED);
			if (!img.empty())
			{
				cv::Mat fimage(img);
				const int d = img.depth();
				if (d == CV_16U || d == CV_16S)	// 16 bit images
				{
					double min, max;
					cv::minMaxLoc(fimage, &min, &max);
					fimage.convertTo(fimage, CV_8UC1, 255.0 / (max - min), -min * 255.0 / (max - min));
				}

				setFileLocation(_filename);
				setImage(fimage);
				if (_reset_roi) 
					resetRoi();
				return true;
			}
		}
	}
	catch (const cv::Exception& _ex)
	{
		std::cout << "Exception reading image from disk: " << _ex.what() << "\n";
	}
	catch (...)
	{
		std::cout << "Exception in reading image from disk!" << "\n";
	}
	return false;
}
bool Fle_ImageWidget::loadImage(bool _reset_roi)
{
	return loadImage(m_filename, _reset_roi);
}
bool Fle_ImageWidget::saveImage(const std::string& _filename, const std::vector<int>& _compression_params)
{
	if (_filename.empty())
		return false;

	try 
	{
#if (_MSC_VER > 1600)
		Fl::lock();				// acquire the lock
		if (m_image.empty())
		{
			Fl::unlock();			// release the lock
			return false;
		}

		bool b = cv::imwrite(_filename, m_image, _compression_params);
		Fl::unlock();			// release the lock
#else
		if (m_image.empty())
			return false;
		bool b = cv::imwrite(_filename, m_image, _compression_params);
#endif
		return b;
	}
	catch (const cv::Exception& _ex)
	{
		std::cout << "Exception in saving image file: " << _ex.what() << "\n";
	}
	catch (...)
	{
		std::cout << "Exception in saving image file!" << "\n";
	}
	return false;
}
bool Fle_ImageWidget::saveImage(const std::vector<int>& _compression_params)
{
	return saveImage(m_filename, _compression_params);
}

void Fle_ImageWidget::setImage(const cv::Mat& _image)
{
	// Details of multi-threaded programming in FLTK:
	// http://www.fltk.org/doc-1.3/advanced.html#advanced_multithreading
	// I'm drawing from a different (not main) thread, therefore, FLTK needs to be locked up.

	if (_image.empty()) 
		return;

#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	m_image = _image;
	Fl::unlock();			// release the lock; allow other threads to access FLTK again
#else
	m_image = _image;
#endif
}
cv::Mat Fle_ImageWidget::getImage() const
{
	cv::Mat m;
#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	m = m_image.clone();
	Fl::unlock();			// release the lock
#else
	m = m_image.clone();
#endif
	return m;
}
cv::Mat& Fle_ImageWidget::imageRef()
{
	return m_image;
}

cv::Size Fle_ImageWidget::getImageSize() const
{
	cv::Size s;
#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	s = cv::Size(m_image.cols, m_image.rows);
	Fl::unlock();			// release the lock
#else
	s = cv::Size(m_image.cols, m_image.rows);
#endif
	return s;
}

void Fle_ImageWidget::setRoi(const cv::Rect& _roi)
{
#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	m_roi = _roi;
	Fl::unlock();			// release the lock; allow other threads to access FLTK again
#else
	m_roi = _roi;
#endif
}
cv::Rect Fle_ImageWidget::getRoi() const
{
	cv::Rect r;
#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	r = m_roi;
	Fl::unlock();			// release the lock; allow other threads to access FLTK again
#else
	r = m_roi;
#endif
	return r;
}
void Fle_ImageWidget::resetRoi()
{
#if (_MSC_VER > 1600)
	Fl::lock();				// acquire the lock
	m_roi = cv::Rect(0, 0, m_image.cols, m_image.rows);
	Fl::unlock();			// release the lock
#else
	m_roi = cv::Rect(0, 0, m_image.cols, m_image.rows);
#endif
}

cv::Mat Fle_ImageWidget::getCroppedImage()
{
#if (_MSC_VER > 1600)
	cv::Mat img;
	Fl::lock();				// acquire the lock
	if ((m_roi.x < 0) || (m_roi.y < 0) ||
		((m_roi.x + m_roi.width) > m_image.cols) ||
		((m_roi.y + m_roi.height) > m_image.rows) ||
		(m_roi.width < 2) ||
		(m_roi.height < 2))
	{
		img = m_image;
	}
	else
	{
		img = m_image(m_roi);
	}
	Fl::unlock();			// release the lock
	return img;
#else
	return m_image;
#endif
}