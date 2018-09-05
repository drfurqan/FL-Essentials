#pragma once
#ifndef Fle_Timer_h__
#define Fle_Timer_h__

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

#include <FLE/Fle_Export.h>

#include <functional>

namespace R3D
{

/************************************************************************/
/*                                                                      */
/************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_Timer
{
public:
	// Description:
	// Constructor to create a timer by specifying the time and a callback function.
	// Example:
	Fle_Timer();
	// Description:
	// Constructor to create a timer by specifying the time and a callback function.
	// Example:
	Fle_Timer(double _time_in_sec, const std::function<void()>& _func);
	// Description:
	// Destructor that stops the timer on deletion.
	virtual ~Fle_Timer();

	// Description:
	// Function to start the timer.
	// It returns true on success.
	bool start();
	// Description:
	// Function to stop the timer.
	// It returns true on success.
	bool stop();
	// Description:
	// Function to pause the timer.
	void pause(bool _b) { m_pause = _b; }
	// Description:
	// Function that returns true if timer is in pause state.
	bool pause() const { return m_pause; }
	// Description:
	// Function to set time (in seconds) for this timer.
	// If you want frames per second, set time like setTime(1.0/30.0) meaning 30 FPS.
	void setTime(double _time_in_seconds) { m_time_in_sec = _time_in_seconds; }
	// Description:
	// Function to get the timer speed in seconds. 
	double getTime() const { return m_time_in_sec; }

	// Description:
	// Function that returns true if the timer has started, otherwise false.
	bool hasStarted();

	// Description:
	// It it's true, this timer will act as a single shot timer, meaning that the specified function "_func" will be
	// called only once (after the specified time).
	// If it's false, then this timer will become a repeat timer.
	void setSingleShot(bool _b) { m_singleshot = _b; }
	// Description:
	// Function that returns true if this timer is a single shot timer.
	bool isSingleShot() const { return m_singleshot; }

	// Description:
	// Function to specify the callback function for this timer.
	void setFunction(const std::function<void()>& _func) { p_func = _func; }
	// Description:
	// Function to get the callback function of this timer.
	const std::function<void()>& getFunction() const { return p_func; }

	// Description:
	// Static function that will create a single shot timer. 
	// It executes the specified function "_func" only once (after the specified time in seconds).
	static void singleShot(double _time_in_sec, const std::function<void()>& _func);

	// Description:
	// Function to get the local date and time.
	static std::string getLocalTime(const char* _format = "%Y-%m-%d %X");

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the real-time updating kind of stuff functionalities.
	// This function will be called repeatedly with the specified time interval specified by 
	// setTime(1/30) until stop() function is called.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly.
	virtual void timerEvent();

private:
	// Description:
	// Call back function for single shot timer.
	static void timerEvent_cb(void* _p);
	
	std::function<void()> p_func;
	double m_time_in_sec;
	bool m_pause;
	bool m_singleshot;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_Idle
{
public:
	// Description:
	// Constructor to create a idle loop for the specified function _func.
	// Example:
	Fle_Idle();
	// Description:
	// Constructor to create a idle loop for the specified function _func.
	// Example:
	Fle_Idle(const std::function<void()>& _func);
	// Description:
	// Destructor that stops the idle function on deletion.
	virtual ~Fle_Idle();
	// Description:
	// Function to start the idle loop.
	// It returns true on success.
	bool start();
	// Description:
	// Function to stop the idle loop.
	// It returns true on success.
	bool stop();
	// Description:
	// Function to pause the idle loop.
	void pause(bool _b) { m_pause = _b; }
	// Description:
	// Function that returns true if idle loop is on pause state.
	bool pause() const { return m_pause; }

	// Description:
	// Function that returns true if the timer has started, otherwise false.
	bool hasStarted();

	// Description:
	// Function to specify the callback function for this timer.
	void setFunction(const std::function<void()>& _func) { p_func = _func; }
	// Description:
	// Function to get the callback function of this timer.
	const std::function<void()>& getFunction() const { return p_func; }

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the real-time updating kind of stuff functionalities.
	// This function will be called repeatedly until stop() function is called.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly.
	// On WIN32, this function scales up to about 62 FPS then will go no faster. 
	virtual void idleEvent();

private:
	// Description:
	// Call back function for idle event loop.
	static void idleEvent_cb(void* _p);

	std::function<void()> p_func;
	bool m_pause;
};

}

#endif // Fle_Timer_h__