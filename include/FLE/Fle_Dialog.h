#pragma once
#ifndef Fle_Dialog_h__
#define Fle_Dialog_h__

/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_Dialog.h
file base:	Fle_Dialog
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Dialog class to create dialogs for getting users inputs with Ok, Cancel
			buttons.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Window.h>
#include <FLE/Fle_Button.h>
#include <FLE/Fle_Layout.h>

#include <vector>

namespace R3D
{


class FL_ESSENTIALS_EXPORT Fle_Dialog : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with position, size, title, and icon.
	Fle_Dialog(int _x, int _y, int _w, int _h, const char* _title = 0, int _status_bar_height = 58, int _x_margin = 0, int _y_margin = 0);
	// Description:
	// Constructor to create a window size, title, and icon.
	// This constructor sets the position at the center of the screen/monitor.
	Fle_Dialog(int _w, int _h, const char* _title = 0, int _status_bar_height = 58, int _x_margin = 0, int _y_margin = 0);
	// Description:
	// Destructor that destroys timer (if any) and other data.
	virtual ~Fle_Dialog();

	// Description:
	// Function that must be called whenever there is a need to add widget inside the window.
	// It is the overloaded name of begin(). You can use begin() or this function to
	// start adding/catching/grabbing widgets inside the window.
	virtual void begin();
	// Description:
	// Function that must be called to stop adding widgets inside the window.
	// It is the overloaded name of end(). You can use end() or this function to
	// stop adding/catching/grabbing widgets.
	virtual void end();

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space or border on the left side of the layout.
	// default value is zero.
	void setLeftMargin(int _value) { m_leftmargin = _value; }
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space or border on the right side of the layout.
	// default value is zero.
	void setRightMargin(int _value) { m_rightmargin = _value; }
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space or border on the top side of the layout.
	// default value is zero.
	void setTopMargin(int _value) { m_topmargin = _value; }
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space or border on the bottom side of the box.
	// default value is zero.
	void setBottomMargin(int _value) { m_bottommargin = _value; }
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Description:
	// Function to set the space margins in pixels, 
	// meaning that the spaces or borders on the sides of the layout.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom)
	{
		m_leftmargin = _left;
		m_rightmargin = _right;
		m_topmargin = _top;
		m_bottommargin = _bottom;
	}

	// Description:
	// Return code for exec() function.
	enum
	{
		Cancel = 0,
		Ok = 1
	};
	// Description:
	// Function to execute this dialog with modal state.
	// Modal means it remains on top and users can't access to any other widget without closing this dialog.
	// It returns 1 if Ok button is pressed, otherwise returns 0 for cancel or close button.
	// Example:
	// if (dlg->exec() == Fle_Dialog::Ok)
	// {
	//	 std::cout << "Done";
	// }
	int exec();

	// Description:
	// Function to execute a dialog window that has a spinner input field. 
	// Example: 
	// This example will create 1 input spinner field with 1 label.
	//
	// double numbr = 5;
	// if (Fle_Dialog::getNumber(300, 120, "Specify Total Number of Frames", "Frames: ", numbr))
	// {
	//	 std::cout << numbr << std::endl;
	// }
	static int getNumber(int _w, int _h,				// width and height of the dialog window.
		const char* _title, 							// title of the dialog window.
		const char* _label, 							// label of input spinner.
		double& _value, 								// default or initial value (result will be stored in _value).
		double _minimum, 								// minimum value of the input spinner.
		double _maximum, 								// maximum value of the input spinner.
		double _step,									// incremental/decremental step of the input spinner.
		const char* _checkbox_label,					// if specified, a check box is created after spinners (result will be stored in _checkbox).
		bool& _checkbox);

	static int getNumber(int _w, int _h,				// width and height of the dialog window.
		const char* _title, 							// title of the dialog window.
		const char* _label, 							// label of input spinner.
		double& _value, 								// default or initial value (result will be stored in _value).
		double _minimum = 0, 							// minimum value of the input spinner.
		double _maximum = 99, 							// maximum value of the input spinner.
		double _step = 0.1);							// incremental/decremental step of the input spinner.

	// Description:
	// Function to execute a dialog window that has number of spinner inputs fields. 
	// Each field will have the default value given by _values.
	// If _checkbox is true, then a checkbox at the end of the spinners will be created,
	// and returned the bool value in the same variable.
	// Example: 
	// This example will create 5 input spinners fields with 5 labels.
	// number of _labels = total number of input spinners.
	//
	// std::vector<const char*> _labels = { "Frame: ", "Fps: ", "Cam: ", "XYZ: ", "ABC: " };
	// std::vector<double> _values = { 0, 1, 2.5, 3, 4.1 };
	// std::vector<double> _minimums = { 0, 0, 2, 3, 4 };
	// std::vector<double> _maximums = { 99, 100, 200, 300, 400 };
	// std::vector<double> _steps = { 0.1, 1, 0.2, 3, 0.4 };
	// bool check = true;
	// if (Fle_Dialog::getNumbers(300, 300, "Dialog with Five Double/Integer Inputs", _labels, _values, _minimums, _maximums, _steps, check))
	// {
	//	 for (std::size_t i = 0; i < _labels.size(); i++)
	//		std::cout << _values[i] << std::endl;
	//   std::cout << check << std::endl;
	// }
	//
	// Note: size of _labels, _values, _minimums, _maximums, and _steps must be equal.
	//
	static int getNumbers(int _w, int _h,				// width and height of the dialog window.
		const char* _title,								// title of the dialog window.
		const std::vector<const char*>& _labels,		// labels of input spinners.
		std::vector<double>& _values,					// default or initial values (results will be stored in _values).
		const std::vector<double>& _minimums,			// minimum values of the input spinners.
		const std::vector<double>& _maximums,			// maximum values of the input spinners.
		const std::vector<double>& _steps,				// incremental/decremental steps of the input spinners.	
		const char* _checkbox_label,					// if specified, a check box is created after spinners (result will be stored in _checkbox).
		bool& _checkbox);

	static int getNumbers(int _w, int _h,				// width and height of the dialog window.
		const char* _title,								// title of the dialog window.
		const std::vector<const char*>& _labels,		// labels of input spinners.
		std::vector<double>& _values,					// default or initial values (results will be stored in _values).
		const std::vector<double>& _minimums,			// minimum values of the input spinners.
		const std::vector<double>& _maximums,			// maximum values of the input spinners.
		const std::vector<double>& _steps);				// incremental/decremental steps of the input spinners.

	// Description:
	// Function to execute a dialog window that has one input text box. 
	//
	// Example: 
	// This example will create 1 input text box with 1 label.
	//
	// std::string input_text = "Enter text here...";
	// if (Fle_Dialog::getInput(300, 120, "Specify Total Number of Frames", "Frames: ", input_text))
	// {
	//	 std::cout << input_text << std::endl;
	// }
	static int getInput(int _w, int _h, 				// width and height of the dialog window.
		const char* _title,  							// title of the dialog window.
		const char* _label,  							// label of input box.
		std::string& _value); 							// default or initial value (result will be stored in _value).

	// Description:
	// Function to execute a dialog window that has number of input text box fields. 
	// Each field will have the default value given by _values.
	// number of _labels = total number of input text boxes.
	//
	// Example: 
	// This example will create 5 input boxes with 5 labels.
	//
	// std::vector<const char*> _labels = { "Frame: ", "Fps: ", "Cam: ", "XYZ: ", "ABC: " };
	// std::vector<std::string> _values = { "Enter text here...", "1", "2", "3", "4" };
	// if (Fle_Dialog::getInputs(300, 300, "Dialog with Five Double/Integer Inputs", _labels, _values))
	// {
	//	 for (std::size_t i = 0; i < _labels.size(); i++)
	//		 std::cout << _values[i] << std::endl;
	// }
	//
	// Note: size of _labels and _values must be equal.
	//
	static int getInputs(int _w, int _h,				// width and height of the dialog window.
		const char* _title,								// title of the dialog window.
		const std::vector<const char*>& _labels,		// labels of input boxes.
		std::vector<std::string>& _values);				// default or initial values (results will be stored in _values).

	// Description:
	// Function to execute a dialog window that has one menu with items and it's label. 
	// index of the selected item will be stored in _selected_index.
	// assign _label to 0 or nullptr if you don't want to give a label to menu items.
	//
	// Example: 
	// This example will create 1 menu with 5 items and 1 label (Choose).
	//
	// std::vector<std::string> _items = { "  Item 0", "  1", "  2", "  3", "  4" };
	// int selected_item = 3;
	// if (Fle_Dialog::getItem(300, 120, "Select Items", "Choose: ", _items, selected_item))
	// {
	//	 std::cout << selected_item << std::endl;
	// }
	static int getItem(int _w, int _h, 					// width and height of the dialog window.
		const char* _title,  							// title of the dialog window.
		const char* _label,  							// label of menu items.
		const std::vector<std::string>& _items, 		// menu items.
		int& _selected_index); 							// default or initial value (result will be stored in _selected_index).

	// Description:
	// Function to execute a dialog window that has a multi-line input text box. 
	//
	// Example: 
	// This example will create a multi-line input text box with a description label.
	// assign _label to 0 or nullptr if you don't want a top label of the text box.
	//
	// std::string input_text_ = "Enter your text here...";
	// if (Fle_Dialog::getText(400, 300,
	//	  "Label of the Multi-line Text Box",
	//	  input_text_,
	//	  Fle_Font(13, FL_WHITE),
	//	  "Enter the Description",
	//	  Fle_Font(13, FL_WHITE),
	//	  fl_rgb_color(80, 80, 80),
	//	  fl_rgb_color(230, 230, 255)))
	// {
	//	 std::cout << input_text_ << std::endl;
	// }
	static int getText(int _w, int _h, 		// width and height of the dialog window.
		const char* _title,  				// title of the dialog window.
		std::string& _text,					// initial value and the returned value of the multi-line text box.
		Fle_Font _text_prop,				// _text properties
		const char* _label,  				// label of the multi-line text box. Assign to 0 or nullptr if you don't want a label.
		Fle_Font _label_prop,				// _label properties
		Fl_Color _text_bkgrnd_color,		// background color of the text box.
		Fl_Color _text_selection_color		// text selection color
		);
	
	// Description:
	// Function to execute a dialog window that has a multi-line input text box and it's properties. 
	//
	// Example: 
	// This example will create a multi-line input text box with a label.
	// std::string input_text = "Enter your text here...";
	// if (Fle_Dialog::getText(400, 300, "Label of the Multi-line Text Box", input_text, Fle_Font(13, FL_WHITE)))
	// {
	//	 std::cout << input_text << std::endl;
	// }
	static int getText(int _w, int _h, 		// width and height of the dialog window.
		const char* _title,  				// title of the dialog window.
		std::string& _text,					// initial value and the returned value of the multi-line text box.
		Fle_Font _text_prop					// _text properties
		);
	
	// Description:
	// Function to execute a dialog window that has a multi-line input text box and a description label. 
	//
	// Example: 
	// std::string input_text_ = "Enter your text here...";
	// if (Fle_Dialog::getText(400, 300,
	//	  "Label of the Multi-line Text Box",
	//	  input_text_,
	//	  Fle_Font(13, FL_WHITE),
	//	  "Enter the Description",
	//	  Fle_Font(13, FL_WHITE, FL_ALIGN_CENTER, FL_HELVETICA_BOLD)))
	// {
	//	 std::cout << input_text_ << std::endl;
	// }
	static int getText(int _w, int _h, 		// width and height of the dialog window.
		const char* _title,  				// title of the dialog window.
		std::string& _text,					// initial value and the returned value of the multi-line text box.
		Fle_Font _text_prop,				// _text properties
		const char* _label,  				// label of the multi-line text box. Assign to 0 or nullptr if you don't want a label.
		Fle_Font _label_prop				// _label properties
		);

	// Description:
	// Function to execute a dialog window that has a HTML supported multi-line text box. 
	// Assign _label to 0 or nullptr if you don't want a top label of the text box.

	// Example: 
	// std::ostringstream sstream;
	// sstream <<
	// "<br><center><h3>FLE v1.0.4</h3></center>"
	// "<center><h6>(February 24 2017)</h6></center>"
	// "<br><center><h4><a href=\"http://real3d.pk/\">http://real3d.pk/</a></h4></center>"
	// "</p><br><center><a href=\"mailto:info@real3d.pk\">info@real3d.pk</a></center></p>";
	// if (Fle_Dialog::openHelpDialog(
	//	 400, 300,
	//	 "About",
	//	 sstream.str(),
	//	 Fle_Font(13, FL_WHITE),
	//	 "Description",
	//	 Fle_Font(13, FL_WHITE)))
	// {
	//	 std::cout << "Ok button is pressed." << std::endl;
	// }
	static int openHelpDialog(
		int _w, int _h, 					// width and height of the dialog window.
		const char* _title,  				// title of the dialog window.
		const std::string& _html_text,		// normal text or with html support.
		Fle_Font _text_prop,				// _text properties
		const char* _label,  				// label of the multi-line text box. Assign to 0 or nullptr if you don't want a label.
		Fle_Font _label_prop,				// _label properties
		Fl_Color _text_bkgrnd_color = fl_rgb_color(80, 80, 80),		// background color of the text box.
		Fl_Color _text_selection_color = fl_rgb_color(230, 230, 255)		// text selection color
		);

	// Description:
	// Function to execute a dialog window that has Yes, No, and Cancel buttons, and a text box.
	// It returns 0 if No button is pressed.
	// It returns 1 if Yes button is pressed.
	// It returns 2 if Cancel button is pressed.

	// Example: 
	// switch (Fle_Dialog::ask(400, 150, "Warning", "Are you sure you want to close?"))
	// {
	// case 0: std::cout << "No is pressed." << std::endl; break;
	// case 1: std::cout << "Yes is pressed." << std::endl; break;
	// case 2: std::cout << "Cancel is pressed." << std::endl; break;
	// }
	static int ask(int _w, int _h, 			// width and height of the dialog window.
		const char* _title,  				// title of the dialog window.
		const std::string& _text,			// initial value and the returned value of the multi-line text box.
		const char* _1st_btn_text = "Yes",					// first button text.
		const char* _2nd_btn_text = "No",					// 2nd button text.
		const char* _3rd_btn_text = "Cancel",				// 3rd button text.
		Fle_Font _text_prop = Fle_Font(13, FL_WHITE),				// _text properties
		Fl_Color _text_bkgrnd_color = fl_rgb_color(80, 80, 80),		// background color of the text box.
		Fl_Color _text_selection_color = fl_rgb_color(230, 230, 255)// text selection color
		);
	// Description:
	// Function to execute a dialog window that has 3 buttons, and a text box.
	// It returns 0 if 1st button is pressed.
	// It returns 1 if 2nd button is pressed.
	// It returns 2 if 3rd button is pressed.

	// Example: 
	// switch (Fle_Dialog::ask("Warning", "Are you sure you want to close?", "Yes", "No", "Cancel"))
	// {
	// case 0: std::cout << "No is pressed." << std::endl; break;
	// case 1: std::cout << "Yes is pressed." << std::endl; break;
	// case 2: std::cout << "Cancel is pressed." << std::endl; break;
	// }
	// The default dialog size is (400 x 150).
	static int ask(
		const char* _title,  				// title of the dialog window.
		const std::string& _text,			// initial value and the returned value of the multi-line text box.
		const char* _1st_btn_text,	// first button text.
		const char* _2nd_btn_text,	// 2nd button text.
		const char* _3rd_btn_text	// 3rd button text.
		);
	// Description:
	// Function to execute a dialog window that has 3 buttons, and a text box.
	// It returns 0 if 1st button is pressed.
	// It returns 1 if 2nd button is pressed.
	// It returns 2 if 3rd button is pressed.

	// Example: 
	// switch (Fle_Dialog::ask("Warning", "Are you sure you want to close?", "Yes", "No"))
	// {
	// case 0: std::cout << "No is pressed." << std::endl; break;
	// case 1: std::cout << "Yes is pressed." << std::endl; break;
	// }
	// The default dialog size is (400 x 150).
	static int ask(
		const char* _title,  				// title of the dialog window.
		const std::string& _text,			// initial value and the returned value of the multi-line text box.
		const char* _1st_btn_text,	// first button text.
		const char* _2nd_btn_text	// 2nd button text.
		);

	// Description:
	// Function to set a pointer to Ok button.
	void setOkButton(Fle_Button* _b) { p_ok = _b; }
	// Description:
	// Function to get a pointer to Ok button.
	Fle_Button* getOkButton() { return p_ok; }
	// Description:
	// Function to set a pointer to Cancel button.
	void setCancelButton(Fle_Button* _b) { p_cancel = _b; }
	// Description:
	// Function to get a pointer to Cancel button.
	Fle_Button* getCancelButton() { return p_cancel; }

	// Description:
	// Function to get a pointer to main layout.
	Fle_VLayout* getMainLayout() const { return p_main_vlayout; }
	// Description:
	// Function to get a pointer to central layout.
	Fle_VHLayout* getCentralLayout() const { return p_central_hlayout; }
	// Description:
	// Function to get a pointer to statusbar.
	Fle_VHLayout* getStatusBar() const { return p_statusbar_vhlayout; }

	// Description:
	// Function to set the statusbar's fixed height.
	void setStatusBarFixedHeight(int _h);

protected:
	Fle_VLayout* p_main_vlayout;
	Fle_VHLayout* p_central_hlayout;
	Fle_VHLayout* p_statusbar_vhlayout;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;

	Fle_Button* p_ok;
	Fle_Button* p_cancel;
};

/********************************************************************************/
/* Examples to create a dialog with input widgets.								*/
/* These widgets will be very useful for getting inputs from users in Integers, */
/* Doubles, and Texts, etc.															*/
/********************************************************************************/

//double numbr = 5;
//if (Fle_Dialog::getNumber(300, 120, "Specify Total Number of Frames", "Frames: ", numbr))
//{
//	std::cout << numbr << std::endl;
//}
//
//std::vector<const char*> _labels = { "Frame: ", "Fps: ", "Cam: ", "XYZ: ", "ABC: " };
//std::vector<double> _values = { 0, 1, 2.5, 3, 4.1 };
//std::vector<double> _minimums = { 0, 0, 2, 3, 4 };
//std::vector<double> _maximums = { 99, 100, 200, 300, 400 };
//std::vector<double> _steps = { 0.1, 1, 0.2, 3, 0.4 };
//if (Fle_Dialog::getNumbers(300, 300, "Dialog with Five Double/Integer Inputs", _labels, _values, _minimums, _maximums, _steps))
//{
//	for (std::size_t i = 0; i < _labels.size(); i++)
//		std::cout << _values[i] << std::endl;
//}
//
//std::string input_text = "Enter text...";
//if (Fle_Dialog::getInput(300, 120, "Specify Total Number of Frames", "Frames: ", input_text))
//{
//	std::cout << input_text << std::endl;
//}
//
//std::vector<const char*> _labels_ = { "Frame: ", "Fps: ", "Cam: ", "XYZ: ", "ABC: " };
//std::vector<std::string> _values_ = { "Enter text here...", "1", "2", "3", "4" };
//if (Fle_Dialog::getInputs(300, 300, "Dialog with Five Double/Integer Inputs", _labels_, _values_))
//{
//	for (std::size_t i = 0; i < _labels_.size(); i++)
//		std::cout << _values_[i] << std::endl;
//}
//
//std::string _input_text_ = "Enter your text here...";
//if (Fle_Dialog::getText(400, 300, "Label of the Multi-line Text Box", _input_text_, Fle_Font(13, FL_WHITE)))
//{
//	std::cout << _input_text_ << std::endl;
//}
//
//std::string input_text_ = "Enter your text here...";
//if (Fle_Dialog::getText(400, 300,
//	"Label of the Multi-line Text Box",
//	input_text_,
//	Fle_Font(13, FL_WHITE),
//	"Enter the Description",
//	Fle_Font(13, FL_WHITE, FL_ALIGN_CENTER, FL_HELVETICA_BOLD)))
//{
//	std::cout << input_text_ << std::endl;
//}
//
//std::vector<std::string> _items = { "  Item 0", "  1", "  2", "  3", "  4" };
//int selected_item = 3;
//if (Fle_Dialog::getItem(300, 120, "Select Items", "Choose: ", _items, selected_item))
//{
//	std::cout << selected_item << std::endl;
//}
//
//std::ostringstream sstream;
//sstream <<
//"<br><center><h3>FLE v1.0.4</h3></center>"
//"<center><h6>(February 24 2017)</h6></center>"
//"<br><center><h4><a href=\"http://real3d.pk/\">http://real3d.pk/</a></h4></center>"
//"</p><br><center><a href=\"mailto:info@real3d.pk\">info@real3d.pk</a></center></p>";
//if (Fle_Dialog::openHelpDialog(
//	400, 300,
//	"About",
//	sstream.str(),
//	Fle_Font(13, FL_WHITE),
//	"Description",
//	Fle_Font(13, FL_WHITE)))
//{
//	std::cout << "Ok button is pressed." << std::endl;
//}

//switch (Fle_Dialog::ask("Warning", "Are you sure you want to close?", "Yes", "No", "Cancel"))
//{
//case 0: std::cout << "No is pressed." << std::endl; break;
//case 1: std::cout << "Yes is pressed." << std::endl; break;
//case 2: std::cout << "Cancel is pressed." << std::endl; break;
//}
//
//switch (Fle_Dialog::ask("Warning", "Are you sure you want to close?", "Yes", "No"))
//{
//case 0: std::cout << "No is pressed." << std::endl; break;
//case 1: std::cout << "Yes is pressed." << std::endl; break;
//}

}

#endif // Fle_Dialog_h__