

#include "Fle_Core.h"
#include "MyOpenGLWindow.h"

using namespace R3D;

int main()
{
	Fle_Core::init();

	MyOpenGLWindow win(1000, 700, "My OpenGL window");
	win.show();

	Fle_Core::exec();
}