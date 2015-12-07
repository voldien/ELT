#!/bin/bash
cmake_minimum_required(VERSION 2.8)
project(ELT)

#	build shared/dynamic library option
option(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
if(NOT BUILD_SHARED_LIBS)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(LINK_SEARCH_START_STATIC TRUE)	
endif(NOT BUILD_SHARED_LIBS)

include_directories(${CMAKE_CURRENT_BINARY_DIR})


set (ELT_VERSION_MAJOR 0)
set (ELT_VERSION_MINOR 6)
set (ELT_VERSION_REVISION 64)
set (ELT_VERSION ${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION})

set (PROJECT_VERSION "${ELT_VERSION}")

add_definitions(-D_INTERNAL_ENGINE=1)




if(CMAKE_COMPILER_IS_MINGW)
	#ADD_DEFINITIONS(
endif()


if((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	if(BUILD_SHARED_LIBS)
	add_definitions(-fPIC)
	endif()

	add_definitions(-fvisibility=hidden -Wall)
elseif(MSVC)
	add_definitions(/MP)

endif()



if (UNIX)
	add_definitions(-Wall)

	if(BUILD_SHARED_LIBS)
		add_definitions(-fvisibility=hidden)

	endif()
endif()


if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

endif()




if(MINGW)



endif()




if (WIN32)
    set(_GLFW_WIN32 1)
    message(STATUS "Using Win32 for window creation")

    if (GLFW_USE_EGL)
        set(_GLFW_EGL 1)
        message(STATUS "Using EGL for context creation")
    else()
        set(_GLFW_WGL 1)
        message(STATUS "Using WGL for context creation")
    endif()
elseif (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "Using Cocoa for window creation")
    set(_GLFW_NSGL 1)
    message(STATUS "Using NSGL for context creation")
elseif (UNIX)
    if (GLFW_USE_WAYLAND)
        set(_GLFW_WAYLAND 1)
        message(STATUS "Using Wayland for window creation")
    elseif (GLFW_USE_MIR)
        set(_GLFW_MIR 1)
        message(STATUS "Using Mir for window creation")
    else()
        set(_GLFW_X11 1)
        message(STATUS "Using X11 for window creation")
    endif()

    if (GLFW_USE_EGL)
        set(_GLFW_EGL 1)
        message(STATUS "Using EGL for context creation")
    else()
        set(_GLFW_GLX 1)
        message(STATUS "Using GLX for context creation")
    endif()
else()
    message(FATAL_ERROR "No supported platform was detected")
endif()




INCLUDE_DIRECTORIES(include)


FILE(GLOB _srcFiles
	"src/*.c"
	"src/graphic/*.c"
	"src/input/*.c"
	"src/system/*.c"
	"src/system/unix/*.c"
)

add_library(EngineEx ${_srcFiles})
# add the install targets
install (TARGETS EngineEx DESTINATION lib)
install (FILES include/*.h DESTINATION include)



