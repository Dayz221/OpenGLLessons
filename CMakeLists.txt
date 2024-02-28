cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(OpenGLLessons)

add_executable(OpenGLLessons 
	src/main.cpp
	src/renderer/shaders.cpp
	src/renderer/shaders.h
	src/renderer/window.cpp
	src/renderer/window.h
	src/renderer/texture2D.cpp
	src/renderer/texture2D.h
	src/resourses/resourseManager.cpp
	src/resourses/resourseManager.h
	src/resourses/stb_image.h
)

target_compile_features(OpenGLLessons PUBLIC cxx_std_17)

add_subdirectory(external/glfw)
target_link_libraries(OpenGLLessons glfw)

add_subdirectory(external/glad)
target_link_libraries(OpenGLLessons glad)

include_directories(external/glm)

set_target_properties(OpenGLLessons PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET OpenGLLessons POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:OpenGLLessons>/res)