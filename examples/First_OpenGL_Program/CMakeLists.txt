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

add_executable (first_opengl_program my_first_opengl_program.cpp)
target_link_libraries(first_opengl_program LINK_PUBLIC ${LIBRARIES})

add_executable (point_on_a_line_simulation opengl_point_on_a_line_simulation.cpp)
target_link_libraries(point_on_a_line_simulation LINK_PUBLIC ${LIBRARIES})

add_executable (simple_GLWindow simple_GLWindow.cpp)
target_link_libraries(simple_GLWindow LINK_PUBLIC ${LIBRARIES})
