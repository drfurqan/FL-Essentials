## FL-Essentials
FL-Essentials is a FLTK based software system which provides extreme easiness in building (responsive) GUI applications. It consists of C++ class library and gives thread-safe image processing support for OpenCV. It makes FLTK functionality easier, faster, and lighter. It works fine as a static or shared library.

## Repository structure

FLE Library is implemented in C++ (but provides both a C and a 
C++ish interface). The directory structure is: <br/>

-  /applications (desktop applications developed in FLE) <br/>
-  /code	 (Source code) <br/>						
-  /include (Public header C and C++ header files) <br/>		
-  /lib (Static libraries for VS2013, VS2015) <br/>		
-  /samples (Examples to illustrate possible use cases for FLE) <br/>

## Building
Take a look into the `INSTALL` file. The build system is CMake, if you already used CMake before there is a good chance you know what to do. <br/>	

Video tutorial that explains the build procedure using CMake (three libraries OpenCV, FLTK, and FLE are compiled in this video): <br/>	

[![How to Build OpenCV, FLTK, FL-Essentials using CMake](how_to_build.png)](https://youtu.be/bwVpf_uKaGo "How to Build OpenCV, FLTK, FL-Essentials using CMake")

## Required Libraries
-  FLTK >= 1.3.x
-  OpenCV >= 2.x.x

## Author
Written by  Dr. Furqan Ullah.

## Reporting Bugs
Report bugs to drfurqan@users.noreply.github.com.

## Copyright
Copyright (c) 2017 Dr. Furqan Ullah.

## See Also
Source code at: <https://github.com/drfurqan/FL-Essentials>.

## Screenshots
![Alt text](https://github.com/drfurqan/FL-Essentials/blob/master/examples/photo_viewer.png?raw=true "Photo Viewer Written in FLE, Inspired by Windows Photo Viewer")

![Alt text](https://github.com/drfurqan/FL-Essentials/blob/master/examples/opengl_events_lights.PNG?raw=true "OpenGL Demo written in FLE")

![Alt text](https://github.com/drfurqan/FL-Essentials/blob/master/examples/demo.PNG?raw=true "FLE Demo that shows various widgets such as MenuBar, ToolBar, StatusBar, Left-Right Bars, Layouts, Buttons")