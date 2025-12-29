cmake_minimum_required(VERSION 3.15)

project(animation LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

add_library(animation
	include/application.h
	include/attribute.h
	include/draw.h
	include/index_buffer.h
	include/shader.h
	include/texture.h
	include/uniform.h
	include/glad/glad.h
	include/KHR/khrplatform.h
	include/stb/stb_image.h
	include/math/constants.h
	include/math/vec2.h
	include/math/vec3.h
	include/math/vec4.h
	include/math/mat4.h

	src/application.cpp
	src/draw.cpp
	src/glad.c
	src/index_buffer.cpp
	src/shader.cpp
	src/texture.cpp
	src/stb_image.cpp
	src/windows.h
	src/windows.cpp
	src/sample1/sample1.cpp
	src/sample1/sample1.h
)

add_executable(animation-app src/main.cpp)
target_link_libraries(animation-app PRIVATE animation)

target_include_directories(animation
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

set_source_files_properties(src/glad.c PROPERTIES LANGUAGE C)
target_compile_definitions(animation PRIVATE
	$<$<COMPILE_LANGUAGE:C>:GLAD_GLAPI_EXPORT_BUILD>
)

# Disable specific MSVC warnings when building for Windows using generator expressions
# Applies only when the compiler is MSVC and the platform is Windows
target_compile_options(animation PRIVATE
	$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<PLATFORM_ID:Windows>>:/wd28251>
	$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<PLATFORM_ID:Windows>>:/wd28159>
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
