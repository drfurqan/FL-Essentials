#pragma once
#ifndef Fle_ImageScrollBox_h__
#define Fle_ImageScrollBox_h__

/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ImageScrollBox.h
file base:	Fle_ImageScrollBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image box widget with image zoom/pan support.
			no zooming using mouse wheel, mouse wheel will be used for 
			vertical and horizontal scrolling.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Box.h>

#include <FL/Fl_Scroll.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ImageScrollBox : public Fl_Scroll
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_ImageScrollBox(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_ImageScrollBox();

	// Description:
	// Function to resize the window.
	// Overridden function that will be called while resizing the window.
	virtual void resize(int _x, int _y, int _w, int _h) override;
	// Description:
	// Function to resize the window.
	// Overridden function that will be called while resizing the window.
	virtual void size(int _w, int _h);

	// Description:
	// Function to redraw/update the window.
	// Both update() and redraw() do the same work.
	virtual void redraw();

	// Description:
	// Function to set background as an image of the given color.
	void clear(Fl_Color _color) { p_box->clear(_color); }

	// Description:
	// Function to set an image as background.
	void setImage(const cv::Mat& _image) { p_box->setImage(_image); }
	// Description:
	// Function to get a clone of the background image.
	cv::Mat getImage() const { return p_box->getImage(); }
	// Description:
	// Function to get a reference of the background image.
	cv::Mat& imageRef() { return p_box->imageRef(); }
	// Description:
	// Function that returns the cropped image if valid Roi is found.
	// Use cloned of the returned image i.e., getCroppedImage().clone()
	cv::Mat getCroppedImage() const { return p_box->getCroppedImage(); }

	// Description:
	// Function to load an image from the given file path.
	// _filename should a file name plus extension.
	// Region of Interest (ROI) will be reset to the loaded image size if
	// the second argument is true, otherwise previous ROI will be used to
	// draw the image.
	// Default ROI is Rect(0, 0, 0, 0) means the full image size.
	bool loadImage(const std::string& _filename, bool _reset_roi = true) { return p_box->loadImage(_filename, _reset_roi); }
	// Description:
	// Function to load an image from the path specified by setFilePath();
	bool loadImage(bool _reset_roi = true) { return p_box->loadImage(_reset_roi); }
	// Description:
	// Function to save the current image to disk.
	// example:
	// vector<int> compression_params;
	// compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	// compression_params.push_back(9);
	// saveImage("D:\\a.png", compression_params);
	bool saveImage(const std::string& _filename, const std::vector<int>& _compression_params = std::vector<int>()) { return p_box->saveImage(_filename, _compression_params); }
	// Description:
	// Function to save the current loaded image to disk.
	// example:
	// vector<int> compression_params;
	// compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	// compression_params.push_back(9);
	// saveImage(compression_params);
	bool saveImage(const std::vector<int>& _compression_params = std::vector<int>()) { return p_box->saveImage(_compression_params); }

	// Description:
	// Function to set the file path used for loadImage().
	// _filename should a file name plus extension.
	void setFileLocation(const std::string& _filename) { p_box->setFileLocation(_filename); }
	// Description:
	// Function to get the file path used for loadImage().
	std::string getFileLocation() const { return p_box->getFileLocation(); }

	// Description:
	// Function to get the loaded image size.
	cv::Size getImageSize() const { return p_box->getImageSize(); }

	// Description:
	// Function to set the region of interest for the image to be displayed.
	void setRoi(const cv::Rect& _roi) { p_box->setRoi(_roi); }
	// Description:
	// Function to get the region of interest.
	cv::Rect getRoi() const { return p_box->getRoi(); }
	// Description:
	// Function to reset the region of interest to display the full image size.
	void resetRoi() { p_box->resetRoi(); }

	// Description:
	// Function to set or add text inside the box.
	// In case of background image, then text will be displayed over the image.
	void setText(const std::string& _text) { p_box->setText(_text); }
	// Description:
	// Function to get the assigned text.
	std::string getText() const { return p_box->getText(); }
	// Description:
	// Function to show/hide text, if there is any text assigned by setText() function.
	void setTextEnabled(bool _b) { p_box->setTextEnabled(_b); }
	// Description:
	// Function that returns true if text is visible.
	bool isTextEnabled() const { return p_box->isTextEnabled(); }
	// Description:
	// Function to set the text properties, it's size, color, type, alignment, etc. etc.
	void setFont(Fle_Font _font) { p_box->setFont(_font); }
	// Description:
	// Function to get a pointer to font (text properties such as size, color, type, alignment, etc. etc.).
	Fle_Font* getFont() const { return p_box->getFont(); }

	// Description:
	// Function to set the position and size of the rubber band.
	void setRubberBand(const cv::Rect& _roi) { p_box->setRubberBand(_roi); }
	// Description:
	// Function to get the position and size of the rubber band.
	cv::Rect getRubberBand() const { return p_box->getRubberBand(); }
	// Description:
	// Function to set rubber band enabled.
	void setRubberBandEnabled(const bool _b) { p_box->setRubberBandEnabled(_b); }
	// Description:
	// Function that returns true if the rubber band is enabled.
	bool isRubberBandEnabled() const { return p_box->isRubberBandEnabled(); }
	// Description:
	// Function to set the rubber band color.
	void setRubberBandColor(Fl_Color _c) { p_box->setRubberBandColor(_c); }
	// Description:
	// Function to get the rubber band color.
	Fl_Color getRubberBandColor() const { return p_box->getRubberBandColor(); }

	// Description:
	// Function to get the rubber band color.
	void color(Fl_Color _c) { Fl_Scroll::color(_c); p_box->color(_c); }
	Fl_Color color() const { return Fl_Scroll::color(); }

	// Description:
	// Function to set image draw type, meaning that how the image should be drawn inside the window.
	// Note: zooming only wors with ImageDrawType::Center.
	void setImageDrawType(const Fle_ImageDrawType _type) { m_dtype = _type; }
	// Description:
	// Function to get the image draw type.
	Fle_ImageDrawType getImageDrawType() const { return m_dtype; }

	// Description:
	// Function to reset zooming using the given image size.
	void adjustSize(const cv::Size& _img_size);
	// Description:
	// Function to reset zooming using the given image size.
	void adjustSize();
	// Description:
	// Function to reset zooming.
	void resetZoom();
	// Description:
	// Function to make zoom in with a scale of 1.2.
	void zoomIn();
	// Description:
	// Function to make zoom out with a scale of 0.8.
	void zoomOut();
	// Description:
	// Function that resizes the size of this widget with a scale of _factor.
	void scaleImage(const double _factor);
	// Description:
	// Function to set zoom in and out factors.
	// Default factor for zoom-in is _f[0] = 1.125.
	// Default factor for zoom-out is _f[1] = 0.875.
	void setZoomInOutFactors(const cv::Vec2d& _f) { m_zoom_factors = _f; }
	// Description:
	// Function to get zoom in and out factors.
	cv::Vec2d getZoomInOutFactors() const { return m_zoom_factors; }

	// Description:
	// Function that converts the given the x, y coordinate into image pixel.
	cv::Rect convertMouseCoordToPixels(int _x, int _y);

	// Description:
	// Function to get the current box size.
	cv::Size getSize();

	// Description:
	// Function to get a pointer to embedded box.
	Fle_Box* getBox() const { return p_box; }

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// drawing FLTK widgets such as 
	void draw() override;

	// Description:
	// Function to handle events.
	virtual int handle(int _event) override;
	// Description:
	// Embedded box inside the Double_Window.
	// Description:
	// Function that computes the new size of the image according to Fle_ImageDrawType.
	cv::Size getNewSize(const cv::Size& _img_size, const cv::Size& _box_size);

	Fle_Box* p_box;

	cv::Vec2d m_zoom_factors;
	Fle_ImageDrawType m_dtype;
	double m_zoom;
};

}

#endif // Fle_ImageScrollBox_h__