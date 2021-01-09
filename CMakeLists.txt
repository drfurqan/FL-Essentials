# ------------------------------------------------------------------------------
# About cmake
# ------------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8.11)
# set(CMAKE_DEBUG_POSTFIX d)

# ------------------------------------------------------------------------------
# Library name
# ------------------------------------------------------------------------------

project (fle)

# file(READ VERSION FLE_VERSION)

set(VERSION_MAJOR 1)
set(VERSION_MINOR_0 5)
set(VERSION_MINOR_1 0)
set(VERSION_PLAIN ${VERSION_MAJOR}.${VERSION_MINOR_0}.${VERSION_MINOR_1})

# ------------------------------------------------------------------------------
# Library's source files (*.cpp files)
# ------------------------------------------------------------------------------

# include(FindFLTK.cmake)

option(OPTION_BUILD_EXAMPLES "Build examples written in FLE" ON)

if(OPTION_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif(OPTION_BUILD_EXAMPLES)

# ------------------------------------------------------------------------------
# Library's source files (*.cpp files)
# ------------------------------------------------------------------------------

set(CPPFILES
${CMAKE_SOURCE_DIR}/src/Fle_AbstractOpenGLActor.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Box.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Button.cpp
${CMAKE_SOURCE_DIR}/src/Fle_CheckGroup.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ColorChooser.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ColorChooserDialog.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Core.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Dialog.cpp
${CMAKE_SOURCE_DIR}/src/Fle_DoubleWindow.cpp
${CMAKE_SOURCE_DIR}/src/Fle_FileDialog.cpp
${CMAKE_SOURCE_DIR}/src/Fle_FileSys.cpp
${CMAKE_SOURCE_DIR}/src/Fle_FloatInputSlider.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Font.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Group.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ImageBox.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ImageScrollBox.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ImageUtil.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ImageWidget.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Input.cpp
${CMAKE_SOURCE_DIR}/src/Fle_InputSlider.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Layout.cpp
${CMAKE_SOURCE_DIR}/src/Fle_MainWindow.cpp
${CMAKE_SOURCE_DIR}/src/Fle_MenuBar.cpp
${CMAKE_SOURCE_DIR}/src/Fle_MessageBox.cpp
${CMAKE_SOURCE_DIR}/src/Fle_MultiColorChooserDialog.cpp
${CMAKE_SOURCE_DIR}/src/Fle_OpenGLTextActor.cpp
${CMAKE_SOURCE_DIR}/src/Fle_OpenGLWindow.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ProgressBar.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ScrollBox.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Spinner.cpp
${CMAKE_SOURCE_DIR}/src/Fle_StatusBar.cpp
${CMAKE_SOURCE_DIR}/src/Fle_StringUtil.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Timer.cpp
${CMAKE_SOURCE_DIR}/src/Fle_ToolBar.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Tree.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Widgets.cpp
${CMAKE_SOURCE_DIR}/src/Fle_Window.cpp
${CMAKE_SOURCE_DIR}/src/Fle_WindowsUtil.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_Color4D.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_FaceIndices3.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_Matrix4x4.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_Vector2D.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_Vector3D.cpp
${CMAKE_SOURCE_DIR}/src/Math/Fle_Vector4D.cpp
)

# ------------------------------------------------------------------------------
# Library's header files (*.h files)
# ------------------------------------------------------------------------------

set(HEADERFILES
${CMAKE_SOURCE_DIR}/include/FLE/Fle_AbstractOpenGLActor.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Box.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Button.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_CheckGroup.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Color.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ColorChooser.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ColorChooserDialog.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Core.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Dialog.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_DoubleWindow.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Export.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_FileDialog.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_FileSys.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_FloatInputSlider.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Font.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Group.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ImageBox.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ImageScrollBox.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ImageUtil.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ImageWidget.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Input.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_InputSlider.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Layout.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_MainWindow.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_MenuBar.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_MessageBox.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_MultiColorChooserDialog.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_OpenGLTextActor.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_OpenGLWindow.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ProgressBar.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ScrollBox.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Size.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Spinner.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_StatusBar.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_StringUtil.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Timer.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_ToolBar.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Tree.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Widgets.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_Window.h
${CMAKE_SOURCE_DIR}/include/FLE/Fle_WindowsUtil.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_Color4D.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_FaceIndices3.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_Matrix4x4.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_Vector2D.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_Vector3D.h
${CMAKE_SOURCE_DIR}/include/FLE/Math/Fle_Vector4D.h
)

# ------------------------------------------------------------------------------
# Prepare source files for shared and static FLE library
# ------------------------------------------------------------------------------

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set (SHARED_FILES ${CPPFILES})

set (STATIC_FILES ${SHARED_FILES})

# add_definitions(-DFL_ESSENTIALS_EXPORT)

# ------------------------------------------------------------------------------
# Add source and header files and define the statis or shared version
# ------------------------------------------------------------------------------

if (WIN32)
	add_library (${PROJECT_NAME} STATIC ${STATIC_FILES} ${HEADERFILES})
else()
	add_library (${PROJECT_NAME} STATIC ${STATIC_FILES} ${HEADERFILES}) #no SHARED 
endif()

# ------------------------------------------------------------------------------
# Required libraries for this library which is FLE
# ------------------------------------------------------------------------------

# find_package(FLTK REQUIRED)
find_package(FLTK REQUIRED fltk fltk_forms fltk_gl fltk_images)
if (WIN32)
	find_package(OpenCV REQUIRED opencv_world)
else()
	find_package(OpenCV REQUIRED)
endif()

# ------------------------------------------------------------------------------
# Link all the required and optional libraries to this library
# ------------------------------------------------------------------------------

set (OPTIONAL_LIBS)

if (WIN32)
	list(APPEND OPTIONAL_LIBS opengl32.lib)
	list(APPEND OPTIONAL_LIBS glu32.lib)
	list(APPEND OPTIONAL_LIBS comctl32.lib)
	list(APPEND OPTIONAL_LIBS comdlg32.lib)
	list(APPEND OPTIONAL_LIBS gdi32.lib)
	list(APPEND OPTIONAL_LIBS ws2_32.lib)
	list(APPEND OPTIONAL_LIBS vfw32.lib)
	list(APPEND OPTIONAL_LIBS advapi32.lib)
	list(APPEND OPTIONAL_LIBS user32.lib)
	list(APPEND OPTIONAL_LIBS shell32.lib)
	list(APPEND OPTIONAL_LIBS ole32.lib)
endif (WIN32)

# set CMAKE_CXX_FLAGS to -Wl,--no-as-needed in cmake-gui. 
target_link_libraries(
${PROJECT_NAME}
${OPTIONAL_LIBS} 
${FLTK_LIBRARY} 
${OpenCV_LIBS}
)

# ------------------------------------------------------------------------------
# Add paths to FLTK and OpenCV include directories
# ------------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${FLTK_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Add proprocessor defininations
# ------------------------------------------------------------------------------

if (WIN32)
    if (MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEF:ExportedFunctions.def /NODEFAULTLIB")
	set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:LIBCMT")
	set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT")
	set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCPRTD")
    endif()
endif()

# ------------------------------------------------------------------------------
# set output name of the library with major and minor version
# ------------------------------------------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION_PLAIN})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${VERSION_PLAIN})

if (WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_${VERSION_MAJOR}${VERSION_MINOR_0}${VERSION_MINOR_1})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_OUTPUT_NAME ${PROJECT_NAME}_${VERSION_MAJOR}${VERSION_MINOR_0}${VERSION_MINOR_1}d)
endif()

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} 
RUNTIME DESTINATION bin           
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)

install(DIRECTORY 
${PROJECT_SOURCE_DIR}/include/FLE
DESTINATION include 
USE_SOURCE_PERMISSIONS
PATTERN ".svn" EXCLUDE
)
