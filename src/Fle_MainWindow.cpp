/*********************************************************************************
created:	2017/01/29   05:58AM
filename: 	Fle_MainWindow.h
file base:	Fle_MainWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Main window class with menu, tool, and status bars.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_MainWindow.h>
#include <FLE/Fle_MessageBox.h>
#include <FLE/Fle_WindowsUtil.h>

#include <FL/fl_draw.H>

#include <iostream>

using namespace R3D;

static Fl_Menu_Item rightClickMenuItems[] = 
{
	{ "\tMenuBar\t",	FL_CTRL + FL_SHIFT + 'm', 0, (void *)1, FL_MENU_TOGGLE | FL_MENU_VALUE | FL_MENU_DIVIDER/*, FL_BOLD + FL_ITALIC, 14*/ },
	{ "\tTopBar\t",		0, 0, (void*)2, FL_MENU_TOGGLE | FL_MENU_VALUE | FL_MENU_DIVIDER },
	{ "\tLeftBar\t",	0, 0, (void*)3, FL_MENU_TOGGLE | FL_MENU_VALUE },
	{ "\tRightBar\t",	0, 0, (void*)4, FL_MENU_TOGGLE | FL_MENU_VALUE | FL_MENU_DIVIDER },
	{ "\tStatusBar\t",	0, 0, (void*)5, FL_MENU_TOGGLE | FL_MENU_VALUE },
	{ 0 }
};

Fle_MainWindow::Fle_MainWindow(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
	Fle_DoubleWindow(_x, _y, _w, _h, _title, _icon_index),
	m_leftmargin(0),
	m_topmargin(0),
	m_rightmargin(0),
	m_bottommargin(0)
{
	int mb_size = 25;
	int sb_size = 22;
	int tb_size = 25;
	int left_tb_size = 25;
	int right_tb_size = 25;
	int gap = 5;

	Fle_DoubleWindow::begin();
	{
		p_centralarea = new Fl_Group(left_tb_size + gap, mb_size + tb_size + gap, _w - left_tb_size - right_tb_size - gap - gap, _h - mb_size - tb_size - sb_size - gap - gap, _title);
		p_centralarea->end();

		p_toptoolbar = new Fle_ToolBar(-2, mb_size, _w + 2, tb_size);
		p_toptoolbar->setMargins(4, 4, 4, 4);
		p_toptoolbar->box(FL_BORDER_BOX);
		p_toptoolbar->setBackgroundColor(Fl::get_color(FL_LIGHT2));
		p_toptoolbar->end();

		p_lefttoolbar = new Fle_ToolBar(0, mb_size + tb_size, left_tb_size, _h - mb_size - tb_size - sb_size);
		p_lefttoolbar->setMargins(4, 4, 4, 4);
		p_lefttoolbar->getCentralLayout()->getTopLayout()->setSpacing(10);
		p_lefttoolbar->setBackgroundColor(Fl::get_color(FL_DARK2));
		p_lefttoolbar->end();
		p_righttoolbar = new Fle_ToolBar(_w - right_tb_size, mb_size + tb_size, right_tb_size, _h - mb_size - tb_size - sb_size);
		p_righttoolbar->setMargins(4, 4, 4, 4);
		p_righttoolbar->getCentralLayout()->getTopLayout()->setSpacing(10);
		p_righttoolbar->setBackgroundColor(Fl::get_color(FL_DARK2));
		p_righttoolbar->end();

		p_statusbar = new Fle_StatusBar(0, _h - sb_size, _w, sb_size);
		p_statusbar->setBackgroundColor(Fl::get_color(FL_LIGHT2));
		p_statusbar->setMargins(5, 5, 0, 0);
		p_statusbar->end();

		p_menubar = new Fle_MenuBar(-2, 0, _w + 2, mb_size, label());	// little expanded to hide the left and right borders.
		p_menubar->setMenuBarBoxType(FL_FLAT_BOX);
		p_menubar->setMenuBarColor(Fl::get_color(FL_LIGHT2));
		p_menubar->setMenuBarItemsColor(Fl::get_color(FL_LIGHT1));
		p_menubar->textsize(12);
		p_menubar->textcolor(Fl::get_color(FL_FOREGROUND_COLOR));
		p_menubar->setRightClickPopupColor(Fl::get_color(FL_LIGHT1));
		p_menubar->setRightClickPopupTextColor(Fl::get_color(FL_FOREGROUND_COLOR));
		p_menubar->setRightClickPopupCallback(rightClickMenuItems, rightClickMenuItem_cb, (void*)this);
		p_menubar->setRightClickPopupEnabled(false);

		p_menubar->hide();
		p_statusbar->hide();
		p_toptoolbar->hide();
		p_lefttoolbar->hide();
		p_righttoolbar->hide();
	}
	Fle_DoubleWindow::end();

	setBackgroundColor(0, 0, 0);
	resizable(p_centralarea);
}

Fle_MainWindow::~Fle_MainWindow()
{
}

void Fle_MainWindow::begin()
{
	p_centralarea->begin();
}
void Fle_MainWindow::end()
{
	p_centralarea->end();
	Fle_DoubleWindow::end();
}
void Fle_MainWindow::beginTopArea()
{
	Fle_DoubleWindow::begin();
}
void Fle_MainWindow::endTopArea()
{
	Fle_DoubleWindow::end();
}

void Fle_MainWindow::resize(int _x, int _y, int _w, int _h)
{
	Fle_DoubleWindow::resize(_x, _y, _w, _h);
	updateContents();
}
void Fle_MainWindow::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}

void Fle_MainWindow::redraw()
{
	p_centralarea->redraw();
	Fle_DoubleWindow::redraw();
}
void Fle_MainWindow::update()
{
	redraw();
}
void Fle_MainWindow::draw()
{
	Fle_DoubleWindow::draw();
}

void Fle_MainWindow::setCentralWidget(Fl_Group* _w)
{ 
	int x = p_centralarea->x();
	int y = p_centralarea->y();
	int w = p_centralarea->w();
	int h = p_centralarea->h();

	if (p_centralarea)
	{
		remove(p_centralarea);
		Fl::delete_widget(p_centralarea);
		p_centralarea = nullptr;
	}

	if (!_w)
		return;

	p_centralarea = _w;
	p_centralarea->size(w, h);
	p_centralarea->position(x, y);
	insert(*p_centralarea, 0);
	resizable(p_centralarea);
}

int Fle_MainWindow::keyPressEvent(int _key)
{
	if (_key == 'm')
	{
		if (Fl::event_state(FL_CTRL) && Fl::event_state(FL_SHIFT))	// if CTRL+SHIFT key is pressed along with m
		{
			toggleMenuBar();
			return 1;
		}
	}
	return 0;
}

void Fle_MainWindow::rightClickMenuItem_cb(Fl_Widget* _w, void* _p)
{
	Fl_Menu_* menu = static_cast<Fl_Menu_*>(_w);
	if (!menu) return;

	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if (!win) return;

	const Fl_Menu_Item* m = menu->mvalue();
	if (!m) return;

	std::string l(m->label());
	if (l == std::string("\tMenuBar\t"))
		win->toggleMenuBar();
	else if (l == std::string("\tTopBar\t"))
		win->toggleTopBar();
	else if (l == std::string("\tLeftBar\t"))
		win->toggleLeftBar();
	else if (l == std::string("\tRightBar\t"))
		win->toggleRightBar();
	else if (l == std::string("\tStatusBar\t"))
		win->toggleStatusBar();
}

void Fle_MainWindow::toggleMenuBar()
{
	if (p_menubar->visible()) p_menubar->hide();
	else p_menubar->show();
	size(w(), h());
	redraw();
}
void Fle_MainWindow::toggleTopBar()
{
	if (p_toptoolbar->visible()) p_toptoolbar->hide();
	else p_toptoolbar->show();
	size(w(), h());
	redraw();
}
void Fle_MainWindow::toggleStatusBar()
{
	if (p_statusbar->visible()) p_statusbar->hide();
	else p_statusbar->show();
	size(w(), h());
	redraw();
}
void Fle_MainWindow::toggleLeftBar()
{
	if (p_lefttoolbar->visible()) p_lefttoolbar->hide();
	else p_lefttoolbar->show();
	size(w(), h());
	redraw();
}
void Fle_MainWindow::toggleRightBar()
{
	if (p_righttoolbar->visible()) p_righttoolbar->hide();
	else p_righttoolbar->show();
	size(w(), h());
	redraw();
}

void Fle_MainWindow::toggleMenuBar_cb(Fl_Widget* _w, void* _p)
{
	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if(win) win->toggleMenuBar();
}
void Fle_MainWindow::toggleTopToolBar_cb(Fl_Widget* _w, void* _p)
{
	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if (win) win->toggleTopBar();
}
void Fle_MainWindow::toggleStatus_cb(Fl_Widget* _w, void* _p)
{
	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if (win) win->toggleStatusBar();
}
void Fle_MainWindow::toggleLeftToolBar_cb(Fl_Widget* _w, void* _p)
{
	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if (win) win->toggleLeftBar();
}
void Fle_MainWindow::toggleRightToolBar_cb(Fl_Widget* _w, void* _p)
{
	Fle_MainWindow* win = static_cast<Fle_MainWindow*>(_p);
	if (win) win->toggleRightBar();
}

void Fle_MainWindow::updateContents()
{
	// adjust the central area while resizing the window.
	// 31 combination of visible or not-visible widgets that I have fixed.
	// It was hella time consuming but it was really important for better visualization and convenience. 
	// Now all toolbars, menubar, and statusbar are
	// synchronized to each other.
	int gap = 0;

	unsigned int m = p_menubar->visible();
	unsigned int t = p_toptoolbar->visible();
	unsigned int s = p_statusbar->visible();
	unsigned int l = p_lefttoolbar->visible();
	unsigned int r = p_righttoolbar->visible();

	int lw = p_lefttoolbar->w();
	int lh = p_lefttoolbar->h();

	int rw = p_righttoolbar->w();
	int rh = p_righttoolbar->h();

	int tw = p_toptoolbar->w();
	int th = p_toptoolbar->h();

	int mw = p_menubar->w();
	int mh = p_menubar->h();

	int sw = p_statusbar->w();
	int sh = p_statusbar->h();

	// if all widgets are visible.
	if (m && t && s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - sh - gap - gap
			);
	}
	// if only menubar is visible.
	else if (m && !t && !s && !l && !r)
		p_centralarea->resize(
		0 + m_leftmargin + gap,
		m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - gap - gap
		);
	// if menubar and top toolbar are visible.
	else if (m && t && !s && !l && !r)
		p_centralarea->resize(
		0 + m_leftmargin + gap,
		m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - gap - gap
		);
	// if menubar, top toolbar, and statusbar are visible.
	else if (m && t && s && l && !r)
		p_centralarea->resize(
		0 + m_leftmargin + lw + gap,
		m_topmargin + mh + th + gap,
		w() - m_rightmargin - m_leftmargin - lw - gap - gap,
		h() - m_bottommargin - m_topmargin - mh - th - sh - gap - gap
		);


	// if top toolbar and statusbar are visible.
	else if (!m && t && s && !l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - th - sh - gap - gap
			);
	}
	// if top toolbar and left toolbar are visible.
	else if (!m && t && !s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - gap - gap
			);
	}
	// if top toolbar and right toolbar are visible.
	else if (!m && t && !s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - gap - gap
			);
	}

	// only menu
	// if statusbar and left toolbar are visible.
	else if (!m && !t && s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - sh - gap - gap
			);
	}
	// if statusbar and right toolbar are visible.
	else if (!m && !t && s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - sh - gap - gap
			);
	}


	// if left and right toolbars are visible.
	else if (!m && !t && !s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - gap - gap
			);
	}

	// only toolbar
	// if only top toolbar is visible.
	else if (!m && t && !s && !l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - th - gap - gap
			);
	}
	// if only statusbar is visible.
	else if (!m && !t && s && !l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - sh - gap - gap
			);
	}
	// if only left toolbar is visible.
	else if (!m && !t && !s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - gap - gap
			);
	}
	// if only right toolbar is visible.
	else if (!m && !t && !s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - gap - gap
			);
	}

	// only menu
	// if menubar and statusbar are visible.
	else if (m && !t && s && !l && !r)
		p_centralarea->resize(
		0 + m_leftmargin + gap,
		m_topmargin + mh + gap,
		w() - m_rightmargin - m_leftmargin - gap - gap,
		h() - m_bottommargin - m_topmargin - mh - sh - gap - gap
		);
	// if menubar and left toolbar are visible.
	else if (m && !t && !s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - gap - gap
			);
	}
	// if menubar and right toolbar are visible.
	else if (m && !t && !s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - gap - gap
			);
	}

	// if all widgets are invisible.
	else if (!m && !t && !s && !l && !r)
		p_centralarea->resize(
		0 + m_leftmargin + gap,
		m_topmargin + gap,
		w() - m_rightmargin - m_leftmargin - gap - gap,
		h() - m_bottommargin - m_topmargin - gap - gap
		);

	// if toolbar, statusbar, left toolbar, and right toolbars are visible.
	else if (!m && t && s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - sh - gap - gap
			);
	}
	else if (m && !t && s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - sh - gap - gap
			);

	}
	else if (m && t && !s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - gap - gap
			);

	}
	else if (m && t && s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap,
			h() - m_bottommargin - m_topmargin - mh - th - sh - gap - gap
			);
	}

	// tool bar with others
	else if (!m && !t && s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - sh - gap - gap
			);
	}
	else if (m && !t && s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - sh - gap - gap
			);
	}
	else if (m && !t && s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - sh - gap - gap
			);
	}


	// left bar with others
	else if (!m && t && s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - sh - gap - gap
			);
	}
	else if (m && t && s && !l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - sh - gap - gap
			);
	}
	else if (!m && t && s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - sh - gap - gap
			);
	}



	// status bar with others
	else if (!m && t && !s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - th - gap - gap
			);
	}
	else if (m && !t && !s && l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + gap,
			w() - m_rightmargin - m_leftmargin - lw - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - gap - gap
			);
	}
	else if (m && t && !s && !l && r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - rw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - gap - gap
			);
	}
	else if (m && t && !s && l && !r)
	{
		p_centralarea->resize(
			0 + m_leftmargin + lw + gap,
			m_topmargin + mh + th + gap,
			w() - m_rightmargin - m_leftmargin - lw - gap - gap,
			h() - m_bottommargin - m_topmargin - mh - th - gap - gap
			);
	}

	if (p_menubar->visible()) 
		p_toptoolbar->position(-2, p_menubar->h());
	else  
		p_toptoolbar->position(-2, 0);

	if (p_statusbar->visible()) 
		p_statusbar->position(0, h() - p_statusbar->h());

	p_lefttoolbar->resize(0, p_centralarea->y(), lw, p_centralarea->h());
	p_righttoolbar->resize(p_centralarea->x() + p_centralarea->w() + gap + m_rightmargin, p_centralarea->y(), rw, p_centralarea->h());
}

void Fle_MainWindow::setBackgroundColor(uchar _red, uchar _green, uchar _blue)
{
	p_centralarea->color(fl_rgb_color(_red, _green, _blue));
	Fle_DoubleWindow::color(fl_rgb_color(_red, _green, _blue));
}
void Fle_MainWindow::setBackgroundColor(Fl_Color _color)
{
	p_centralarea->color(_color);
	Fle_DoubleWindow::color(_color);
}
void Fle_MainWindow::color(uchar _red, uchar _green, uchar _blue)
{
	setBackgroundColor(_red, _green, _blue);
}
void Fle_MainWindow::color(Fl_Color _color)
{
	setBackgroundColor(_color);
}
Fl_Color Fle_MainWindow::color() const
{
	return getBackgroundColor();
}