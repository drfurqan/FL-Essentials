/*********************************************************************************
created:	2017/01/26   02:31AM
filename: 	Fle_Timer.h
file base:	Fle_Timer
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A timer class for FLTK repeat and idle timers.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Timer.h"

using namespace R3D;

Fle_Timer::Fle_Timer() :
m_time_in_sec(1/30),
p_func(nullptr),
m_pause(false),
m_singleshot(false)
{
}
Fle_Timer::Fle_Timer(double _time_in_sec, const std::function<void()>& _func) :
m_time_in_sec(_time_in_sec),
p_func(_func),
m_pause(false),
m_singleshot(false)
{
}

Fle_Timer::~Fle_Timer()
{
	stop();
}

bool Fle_Timer::start()
{
	if (hasStarted()) return false;
	Fl::repeat_timeout(m_time_in_sec, Fle_Timer::timerEvent_cb, (void*)this);
	return true;
}
bool Fle_Timer::stop()
{
	if (hasStarted())
	{
		Fl::remove_timeout(Fle_Timer::timerEvent_cb, (void*)this);
		return true;
	}
	return false;
}
bool Fle_Timer::hasStarted()
{
	if (Fl::has_timeout(Fle_Timer::timerEvent_cb, (void*)this))
		return true;
	return false;
}

void Fle_Timer::timerEvent()
{
	if (p_func)
		p_func();
}
void Fle_Timer::timerEvent_cb(void* _p)
{
	Fle_Timer* w = static_cast<Fle_Timer*>(_p);
	if (w)
	{
		if (w->pause())
			return;

		w->timerEvent();

		if (w->isSingleShot())
			Fl::remove_timeout(Fle_Timer::timerEvent_cb, (void*)_p);
		else
			Fl::repeat_timeout(w->getTime(), Fle_Timer::timerEvent_cb, (void*)_p);
	}
}

void Fle_Timer::singleShot(double _time_in_sec, const std::function<void()>& _func)
{
	Fle_Timer* t = new Fle_Timer(_time_in_sec, _func);
	t->setSingleShot(true);
	t->pause(false);
	t->start();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Fle_Idle::Fle_Idle() :
p_func(nullptr),
m_pause(false)
{
}
Fle_Idle::Fle_Idle(const std::function<void()>& _func) :
p_func(_func),
m_pause(false)
{
}

Fle_Idle::~Fle_Idle()
{
	stop();
}

bool Fle_Idle::start()
{
	if (hasStarted()) return false;
	Fl::add_idle(Fle_Idle::idleEvent_cb, (void*)this);	// add_idle: On WIN32 scales up to about 62 FPS then will go no faster. 
	return true;
}
bool Fle_Idle::stop()
{
	if (hasStarted())
	{
		Fl::remove_idle(Fle_Idle::idleEvent_cb, (void*)this);	// add_idle: On WIN32 scales up to about 62 FPS then will go no faster. 
		return true;
	}
	return false;
}
bool Fle_Idle::hasStarted()
{
	if(Fl::has_idle(Fle_Idle::idleEvent_cb, (void*)this))
		return true;
	return false;
}

void Fle_Idle::idleEvent()
{
	if (p_func)
		p_func();
}
void Fle_Idle::idleEvent_cb(void* _p)
{
	Fle_Idle* w = static_cast<Fle_Idle*>(_p);
	if (w)
	{
		if (w->pause()) 
			return;
		w->idleEvent();
	}
}
