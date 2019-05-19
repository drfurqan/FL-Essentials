set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/examples)

set(INCLUDE_DIR
${PROJECT_SOURCE_DIR}/include
${FLTK_INCLUDE_DIR}
${OpenCV_INCLUDE_DIRS}
)

include_directories(${INCLUDE_DIR})

if(WIN32)
set(LIBRARIES 
${PROJECT_NAME} 
${OPENGL_gl_LIBRARY}
${OPENGL_glu_LIBRARY}
${OPENGL_LIBRARIES}
${OPENGL_LIBRARY}
${FLTK_LIBRARIES}
${OpenCV_LIBS})
else()
set(LIBRARIES 
${PROJECT_NAME} 
${OPENGL_gl_LIBRARY}
${OPENGL_glu_LIBRARY}
${OPENGL_LIBRARIES}
${FLTK_LIBRARIES}
${OpenCV_LIBS}
-ldl -lz -ljpeg -lpng)
endif(WIN32)

add_executable (hello_world 1-hello_world.cpp)
target_link_libraries(hello_world LINK_PUBLIC ${LIBRARIES})

add_executable (mainwindow_menubar 2-mainwindow_menubar.cpp)
target_link_libraries(mainwindow_menubar LINK_PUBLIC ${LIBRARIES})

add_executable (mainwindow_menubar_statusbar 3-mainwindow_menubar_statusbar.cpp)
target_link_libraries(mainwindow_menubar_statusbar LINK_PUBLIC ${LIBRARIES})

add_executable (demo 4-demo.cpp)
target_link_libraries(demo LINK_PUBLIC ${LIBRARIES})

