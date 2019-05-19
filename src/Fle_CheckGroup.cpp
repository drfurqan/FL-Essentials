/*********************************************************************************
created:	2017/03/01   01:53PM
filename: 	Fle_CheckGroup.h
file base:	Fle_CheckGroup
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A group that can be toggled active or inactive.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_CheckGroup.h>

#include <FL/Fl.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_CheckGroup::Fle_CheckGroup(int _x, int _y, int _w, int _h, const char* _title) : Fl_Group(_x, _y, _w, _h, _title)
{
    p_chkbtn = new Fl_Check_Button(0, 0, 0, 0);
    p_chkbtn->labelsize(12);
    p_chkbtn->value(1);
	p_chkbtn->color(FL_WHITE);
	p_chkbtn->callback(toggle_cb, (void*)this);
 	color(FL_WHITE);
	box(FL_BORDER_FRAME);
    align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    m_spacesize = 10;
	end();
}

void Fle_CheckGroup::draw()
{
    int lblW = 0, lblH, X, i;

    if(label() == 0)
        lblW = lblH = 0;
    else if(strlen( label() ) == 0)
        lblW = lblH = 0;
    else
    {
        measure_label(lblW, lblH);
        lblW += m_spacesize;
        lblH += 2;
    }

    // align the label
    if( align() & FL_ALIGN_LEFT )
        X = 4;
    else if( align() & FL_ALIGN_RIGHT )
        X = w() - lblW - 8;
    else
        X = w()/2 - lblW/2 - 2;

    // draw the main group box
    if( damage() & ~FL_DAMAGE_CHILD )
        fl_draw_box( box(), x(), y()+lblH/2, w(), h()-lblH/2, color() );

    unsigned char* active = nullptr;
    if( !p_chkbtn->value() )
    {
        active = new unsigned char[children()];
        for( i = 1; i < children(); i++ )
        {
            active[i-1] = child(i)->active();
            child(i)->deactivate();
        }
    }

    // clip and draw the children
    p_chkbtn->resize( p_chkbtn->x(), p_chkbtn->y(), 0, 0 );
    fl_clip( x()+2, y()+lblH+1, w()-4, h()-lblH-3 );
    draw_children();
    fl_pop_clip();

    // clear behind the button and draw it
    fl_color( color() );
    fl_rectf( x()+X, y(), lblW+4, lblH );
    fl_color( labelcolor() );
    p_chkbtn->label( label() );
    p_chkbtn->resize( x()+X+2, y(), lblW, lblH );
    draw_child( *p_chkbtn );

    if(!p_chkbtn->value())
    {
        for(i=1; i<children(); i++)
        {
            if(active[i-1])
                child(i)->activate();
            else
                child(i)->deactivate();
        }
        delete [] active;
    }
}

void R3D::Fle_CheckGroup::activate()
{
	value(1);
}

void R3D::Fle_CheckGroup::deactivate()
{
	value(0);
}

int R3D::Fle_CheckGroup::active() const
{
	return value();
}

int R3D::Fle_CheckGroup::value() const
{
	return p_chkbtn->value();
}

void R3D::Fle_CheckGroup::value(int v)
{
	p_chkbtn->value(v); 
	redraw();
}

void R3D::Fle_CheckGroup::setCheckButtonColor(Fl_Color _c)
{
	p_chkbtn->color(_c);
}

void R3D::Fle_CheckGroup::labelsize(int _size)
{
	p_chkbtn->labelsize(_size);
}

void R3D::Fle_CheckGroup::setOffsetSize(int _size)
{
	m_spacesize = _size;
}

void Fle_CheckGroup::toggle()
{
	do_callback();
	redraw();
}
void R3D::Fle_CheckGroup::toggle_cb(Fl_Widget* _w, void* _data)
{
	static_cast<Fle_CheckGroup*>(_data)->toggle();
}
