set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/examples)

set(INCLUDE_DIR
${PROJECT_SOURCE_DIR}/include
${FLTK_INCLUDE_DIR}
${OpenCV_INCLUDE_DIRS}
)

include_directories(${INCLUDE_DIR})


set(LIBRARIES 
${PROJECT_NAME} 
${FLTK_LIBRARY}
${OpenCV_LIBS}
${OPENGL_gl_LIBRARY}
${OPENGL_glu_LIBRARY}
${OPENGL_LIBRARIES}
${OPENGL_LIBRARY})


add_executable (hello_world 1-hello_world.cpp)
target_link_libraries(hello_world LINK_PUBLIC ${LIBRARIES})

add_executable (mainwindow_menubar 2-mainwindow_menubar.cpp)
target_link_libraries(mainwindow_menubar LINK_PUBLIC ${LIBRARIES})

add_executable (mainwindow_menubar_statusbar 3-mainwindow_menubar_statusbar.cpp)
target_link_libraries(mainwindow_menubar_statusbar LINK_PUBLIC ${LIBRARIES})

add_executable (demo 4-demo.cpp)
target_link_libraries(demo LINK_PUBLIC ${LIBRARIES})

add_executable (photo_viewer_application Fle_Image_Viewer_main.cpp Fle_Image_Viewer.cpp Fle_Image_Viewer.h Photo_Viewer_Icons.h)
target_link_libraries(photo_viewer_application LINK_PUBLIC ${LIBRARIES})

add_executable (my_first_opengl_program my_first_opengl_program.cpp)
target_link_libraries(my_first_opengl_program LINK_PUBLIC ${LIBRARIES})

add_executable (opengl_point_on_a_line_simulation opengl_point_on_a_line_simulation.cpp)
target_link_libraries(opengl_point_on_a_line_simulation LINK_PUBLIC ${LIBRARIES})

add_executable (opengl_hello_world opengl_hello_world_main.cpp opengl_hello_world.cpp opengl_hello_world.h)
target_link_libraries(opengl_hello_world LINK_PUBLIC ${LIBRARIES})

add_executable (opengl_events_lights opengl_events_lights_main.cpp opengl_events_lights.cpp opengl_events_lights.h)
target_link_libraries(opengl_events_lights LINK_PUBLIC ${LIBRARIES})

add_executable (opengl_events_lights_animation opengl_events_lights_animation_main.cpp opengl_events_lights_animation.cpp opengl_events_lights_animation.h)
target_link_libraries(opengl_events_lights_animation LINK_PUBLIC ${LIBRARIES})

add_executable (OGLWindow OGLWindow_main.cpp OGLWindow.cpp OGLWindow.h)
target_link_libraries(OGLWindow LINK_PUBLIC ${LIBRARIES})

add_executable (opengl_rotation_panning_zooming opengl_rotation_panning_zooming_main.cpp opengl_rotation_panning_zooming.cpp opengl_rotation_panning_zooming.h)
target_link_libraries(opengl_rotation_panning_zooming LINK_PUBLIC ${LIBRARIES})

add_executable (lighting_model_and_mesh_rendering lighting_model_and_mesh_rendering_main.cpp lighting_model_and_mesh_rendering.cpp lighting_model_and_mesh_rendering.h)
target_link_libraries(lighting_model_and_mesh_rendering LINK_PUBLIC ${LIBRARIES})

add_executable (OpenGLSolarSystem OpenGLSolarSystem_main.cpp OpenGLSolarSystem.cpp OpenGLSolarSystem.h)
target_link_libraries(OpenGLSolarSystem LINK_PUBLIC ${LIBRARIES})