#pragma once

#include <FLE/Fle_OpenGLWindow.h>


using namespace R3D;

class MyOpenGLWindow : public Fle_OpenGLWindow
{
public:
	MyOpenGLWindow(int _w, int _h, const char* _title);

	void initializeGL();

	void paintGL();

	void timerEvent();

	void drawBox(int _w, int _h, int _d);

private:
	float angle;
};