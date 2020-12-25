## FL-Essentials
FL-Essentials (FLE) is a FLTK based software system which provides extreme easiness in building (responsive) GUI applications. It consists of C++ class library and gives thread-safe image processing support for OpenCV. It also provides OpenGL based 3D classes to create computer graphics applications with fully featured GUI.

## Repository structure

FLE Library is implemented in C++ (but provides both a C and a 
C++ish interface). The directory structure is: <br/>

-  /examples (Examples to illustrate possible use cases for FLE)
-  /include/FLE (Public header C and C++ header files) <br/>	
-  /include/FLE/Math (Classes for 3D math and OpenGL programming)
-  /lib (Prebuild static libraries for VS2017) <br/>	
-  /src	 (Source code) <br/>	
-  /extras	 (useful material to create an application) <br/>						
<br/>

## Building
Take a look into the `INSTALL` file. The build system is CMake, if you already used CMake before there is a good chance you know what to do. <br/>	

Video tutorial that explains the build procedure using CMake (three libraries OpenCV, FLTK, and FLE are compiled in this video): <br/>	

[![How to Build OpenCV, FLTK, FL-Essentials using CMake](how_to_build.png)](https://youtu.be/bwVpf_uKaGo "How to Build OpenCV, FLTK, FL-Essentials using CMake")

## Required Libraries
-  FLTK >= 1.4.x
-  OpenCV >= 2.x.x

## Author
Written by  Dr. Furqan Ullah.

## Reporting Bugs
Report bugs to drfurqan@users.noreply.github.com.

## Copyright
Copyright (c) 2017-2019 Dr. Furqan Ullah.

## See Also
Source code at: <https://github.com/drfurqan/FL-Essentials>.

## Screenshots
![Alt text](https://github.com/drfurqan/FL-Essentials/tree/master/examples/photo_viewer.png?raw=true "Photo Viewer Written in FLE, Inspired by Windows Photo Viewer")

![Alt text](https://github.com/drfurqan/FL-Essentials/tree/master/examples/3d_solar_system.PNG?raw=true "3D Solar System written in FLE/OpenGL")

![Alt text](https://github.com/drfurqan/FL-Essentials/tree/master/examples/opengl_events_lights.PNG?raw=true "OpenGL Demo written in FLE/OpenGL")

![Alt text](https://github.com/drfurqan/FL-Essentials/tree/master/examples/demo.PNG?raw=true "FLE Demo that shows various widgets such as MenuBar, ToolBar, StatusBar, Left-Right Bars, Layouts, Buttons")
