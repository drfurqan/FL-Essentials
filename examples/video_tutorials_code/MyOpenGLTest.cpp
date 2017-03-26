
#include <FLE/Fle_Core.h>
#include <FLE/Fle_OpenGLWindow.h>

#include <Fl/gl.h>
#include <Fl/glu.h>
#include <Fl/glut.h>

using namespace R3D;

class MyOpenGLWindow : public Fle_OpenGLWindow
{
public:
	MyOpenGLWindow(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
	{
	}

	void initializeGL()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void paintGL()
	{
		glClearColor(0.6, 0.6, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		///////////////////////////////////////////
		glViewport(0, 0, w(), h());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0, double(w() / h()), 0.1, 10000);

		gluLookAt(0, 0, 100,
			0, 0, 0,
			0, 1, 0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		///////////////////////////////////////////

		glRotatef(25, 1, 0, 0);
		glRotatef(25, 0, 1, 0);
		glBegin(GL_LINES);

		glColor3f(1.0, 0, 0);
		glVertex3f(-100, 0, 0);
		glVertex3f(100, 0, 0);

		glColor3f(0, 1.0, 0);
		glVertex3f(0, -100, 0);
		glVertex3f(0, 100, 0);

		glColor3f(0, 0, 1.0);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0, 100);

		glEnd();
	}
};

int main()
{
	Fle_Core::init();

	MyOpenGLWindow win(1000, 600, "My First OpenGL window");
	win.show();

	return Fle_Core::exec();
}