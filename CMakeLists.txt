cmake_minimum_required(VERSION 3.15)

project(animation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

add_library(animation
	include/application.h
	include/glad/glad.h
	include/KHR/khrplatform.h

	src/application.cpp
	src/glad.c
	src/main.cpp
)

target_include_directories(animation
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if(MSVC)
	target_link_options(animation PRIVATE
		$<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>
		$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
	)
else()
	target_link_options(animation PRIVATE
		$<$<CONFIG:Debug>:-Wl,-subsystem,console>
		$<$<CONFIG:Release>:-Wl,-subsystem,windows>
	)
endif()

if(TARGET OpenGL::GL)
	target_link_libraries(animation PUBLIC OpenGL::GL)
else()
	if(OPENGL_gl_LIBRARY)
		target_link_libraries(animation PUBLIC ${OPENGL_gl_LIBRARY})
	endif()
endif()
