#pragma once

#include <FLE/Fle_OpenGLWindow.h>

using namespace R3D;

class MyOpenGLWindow : public Fle_OpenGLWindow
{
public:
	MyOpenGLWindow(int _w, int _h, const char* _title);

	void initializeGL() override;

	void setupCamera();

	void paintGL() override;

	void timerEvent() override;


	void drawBox(int _w, int _h, int _d);

	void mouseLeftButtonPressEvent(int _x, int _y) override;
	void mouseLeftButtonReleaseEvent() override;
	void mouseLeftButtonDragEvent(int _x, int _y) override;

	void mouseWheelForwardEvent() override;
	void mouseWheelBackwardEvent() override;

	void mouseMiddleButtonPressEvent(int _x, int _y) override;
	void mouseMiddleButtonReleaseEvent() override;
	void mouseMiddleButtonDragEvent(int _x, int _y) override;

private:
	float angle;

	bool has_rotation_started;
	int start_x;
	int start_y;
	float x_rot_angle;
	float y_rot_angle;

	float zoom;

	bool has_panning_started;
	float x_trans;
	float y_trans;
};