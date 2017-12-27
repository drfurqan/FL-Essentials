/*********************************************************************************
created:	2017/01/30   12:51AM
filename: 	Fle_ImageWidget.h
file base:	Fle_ImageWidget
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized image widget with load, save, zoom/pan support.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageWidget.h>
#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_MessageBox.h>

#include <FL/Fl.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_ImageWidget::Fle_ImageWidget(int _x, int _y, int _w, int _h, const char* _title) :
Fl_Widget(_x, _y, _w, _h, _title),
m_dtype(Fle_ImageDrawType::Fit),
m_zoom(1),
m_zoom_factors(cv::Vec2d(1.1, 0.9)),
m_isize(cv::Size(_w, _h))
{
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_ImageWidget::~Fle_ImageWidget()
{
	m_fimage.release();
}
void Fle_ImageWidget::clear(const cv::Vec3b& _color)
{
	cv::Mat m(m_isize, CV_8UC3);
	for (int y = 0; y < m.rows; y++)
		for (int x = 0; x < m.cols; x++)
			Fle_ImageUtil::setPixel(m, x, y, _color);
	setImage(m);
}

void Fle_ImageWidget::draw()
{
	draw(Fl_Widget::x(), Fl_Widget::y(), Fl_Widget::w(), Fl_Widget::h());
}
void Fle_ImageWidget::draw(int _x, int _y, int _w, int _h)
{	
	if (m_image.empty()) return;
	if (m_image.cols <= 0 || m_image.rows <= 0) return;
	if (m_isize.width <= 0 || m_isize.height <= 0) return;

	if (m_dtype == Fle_ImageDrawType::Fit)
		m_isize = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, _w, _h);
	else if (m_dtype == Fle_ImageDrawType::Stretch)
		m_isize = cv::Size(_w, _h);
	else if (m_dtype == Fle_ImageDrawType::Center && m_zoom == 1)	// if there is no zooming
	{
		if (m_image.cols > w() || m_image.rows > h())	// if image is greater than the box size.
			m_isize = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, w(), h());
		else // image with original size.
			m_isize = cv::Size(m_image.cols, m_image.rows);
	}

	m_fimage.release();
	m_fimage = cv::Mat::zeros(m_isize, m_image.type());

	cv::resize(m_image, m_fimage, m_isize, 0, 0, cv::INTER_CUBIC);
	if (m_fimage.channels() == 4) cv::cvtColor(m_fimage, m_fimage, CV_BGRA2RGBA);
	else if (m_fimage.channels() == 3) cv::cvtColor(m_fimage, m_fimage, CV_BGR2RGB);
		
	int X = _x + (_w - m_isize.width) / 2;
	int Y = _y + (_h - m_isize.height) / 2;

	fl_push_clip(X, Y, m_isize.width, m_isize.height);

	// fl_draw_image does not support (4-channels) transparent images like PNG. 
	// It only support RGB (3-channels).
	// fl_draw_image(m_fimage.datastart, X, Y, s.width, s.height, m_fimage.channels(), m_fimage.step);
	Fl_RGB_Image o(m_fimage.datastart, m_isize.width, m_isize.height, m_fimage.channels(), static_cast<int>(m_fimage.step));
	o.draw(X, Y);	// Fl_RGB_Image works fine with the transparent PNG images.

	fl_pop_clip();
}

bool Fle_ImageWidget::loadImage(const std::string& _filename)
{
	if (_filename.empty()) return false;
	try
	{
		Fl::lock();				// acquire the lock
		m_image = cv::imread(_filename, CV_LOAD_IMAGE_UNCHANGED);
		if (!m_image.empty())
		{
			redraw();
			Fl::unlock();			// release the lock; allow other threads to access FLTK again
			Fl::awake();			// use Fl::awake() to signal main thread to refresh the GUI

			m_filepath = _filename;
			return true;
		}
		Fl::unlock();			// release the lock; allow other threads to access FLTK again
		Fl::awake();			// use Fl::awake() to signal main thread to refresh the GUI
	}
	catch (const cv::Exception& _ex)
	{
		Fle_MessageBox::Error("Something went wrong in loading image file!");
		std::cout << "Exception reading image from disk: %s\n" << _ex.what();
	}
	catch (...)
	{
		Fle_MessageBox::Error("Something went wrong in loading image file!");
	}
	return false;
}
void Fle_ImageWidget::setImage(const cv::Mat& _image)
{
	// Details of multi-threaded programming in FLTK:
	// http://www.fltk.org/doc-1.3/advanced.html#advanced_multithreading
	// I'm drawing from a different (not main) thread, therefore, FLTK needs to be locked up.
	
	if (_image.empty()) return;

	Fl::lock();				// acquire the lock
	m_image = _image;
	redraw();
	Fl::unlock();			// release the lock; allow other threads to access FLTK again
	Fl::awake();			// use Fl::awake() to signal main thread to refresh the GUI
}
cv::Mat Fle_ImageWidget::getImage() const
{
	// Details of multi-threaded programming in FLTK:
	// http://www.fltk.org/doc-1.3/advanced.html#advanced_multithreading
	// I'm drawing from a different (not main) thread, therefore, FLTK needs to be locked up.

	cv::Mat m;
	Fl::lock();				// acquire the lock
	m = m_image.clone();
	Fl::unlock();			// release the lock; allow other threads to access FLTK again
	Fl::awake();			// use Fl::awake() to signal main thread to refresh the GUI
	return m;
}

bool Fle_ImageWidget::saveImage(const std::string& _filename, const std::vector<int>& _compression_params)
{
	if (m_image.empty()) return false;

	bool b = true;
	try 
	{
		Fl::lock();				// acquire the lock
		b = cv::imwrite(_filename, m_image, _compression_params);
		Fl::unlock();			// release the lock; allow other threads to access FLTK again
		Fl::awake();			// use Fl::awake() to signal main thread to refresh the GUI
	}
	catch (const cv::Exception& _ex)
	{
		Fle_MessageBox::Error("Something went wrong in saving image file!");
		std::cout << "Exception converting image to PNG format: %s\n" << _ex.what();
		b = false;
	}
	catch (...)
	{
		Fle_MessageBox::Error("Something went wrong in saving image file!");
		b = false;
	}
	return b;
}

void Fle_ImageWidget::resetZoom()
{
	if (m_image.empty()) return;

	m_zoom = 1.0;

	// interesting hack to adjust this widget's position and size in the parent widget.
	Fl_Group* g = static_cast<Fl_Group*>(parent());
	if (g)
	{
		cv::Size s;
		if (m_dtype == Fle_ImageDrawType::Fit)
			s = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, g->w(), g->h());
		else if (m_dtype == Fle_ImageDrawType::Stretch)
			s = cv::Size(g->w(), g->h());
		else if (m_dtype == Fle_ImageDrawType::Center)
		{
			if(m_image.cols > g->w() || m_image.rows > g->h())
				s = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, g->w(), g->h());
			else
				s = cv::Size(m_image.cols, m_image.rows);
		}
		size(s.width, s.height);
		position(static_cast<int>((g->w() - Fl_Widget::w()) / 2), static_cast<int>((g->h() - Fl_Widget::h()) / 2));
		m_isize = s;
	}
}

void Fle_ImageWidget::zoomIn()
{
	if (m_image.empty()) return;
	if (m_dtype != Fle_ImageDrawType::Center) return;	// zooming only works with ImageDrawType::Original.

	scaleImage(m_zoom_factors[0]);
	redraw();
}
void Fle_ImageWidget::zoomOut()
{
	if (m_image.empty()) return;
	if (m_dtype != Fle_ImageDrawType::Center) return;	// zooming only works with ImageDrawType::Original.

	scaleImage(m_zoom_factors[1]);
	redraw();
}
void Fle_ImageWidget::scaleImage(double _factor)
{
	if (m_image.empty()) return;
	if (m_dtype != Fle_ImageDrawType::Center) return;	// zooming only works with ImageDrawType::Original.

	// set box size by multiplying with the zoom factor.
	m_zoom *= _factor;

	// limit the zoom factor by 8.
	if (m_zoom > 10.0)	m_zoom = 10.0;

	Fl_Group* g = static_cast<Fl_Group*>(parent());
	if (g)
	{
		// restrict the outward zooming.
		if (m_zoom < 1)
		{
			m_isize = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_isize.width, m_isize.height, g->w(), g->h());
			m_zoom = 1;
		}
		else
		{
			if (m_image.cols >= g->w() || m_image.rows >= g->h())
				m_isize = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, static_cast<int>(g->w() * m_zoom), static_cast<int>(g->h() * m_zoom));
			else
				m_isize = Fle_ImageUtil::getNewSizeKeepAspectRatio(m_image.cols, m_image.rows, static_cast<int>(m_image.cols * m_zoom), static_cast<int>(m_image.rows * m_zoom));
		}
	}
	
	size(m_isize.width, m_isize.height);
}