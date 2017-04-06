

#include <FLE/Fle_Core.h>
#include "MyOpenGLWindow.h"

using namespace R3D;

int main()
{
	Fle_Core::init();

	MyOpenGLWindow win(1000, 700, "3D Model Manipulation in OpenGL");
	win.show();

	return Fle_Core::exec();
}