
cmake_minimum_required(VERSION 2.8)
project(ELT)

#	build shared/dynamic library option
option(BUILD_SHARED_LIBS "Build package with shared libraries." ON)

if(NOT BUILD_SHARED_LIBS)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(LINK_SEARCH_START_STATIC TRUE)	
endif(NOT BUILD_SHARED_LIBS)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(include)


set (ELT_VERSION_MAJOR 0)
set (ELT_VERSION_MINOR 6)
set (ELT_VERSION_REVISION 64)
set (ELT_VERSION ${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION})

set (PROJECT_VERSION "${ELT_VERSION}")

add_definitions(-D_INTERNAL_ENGINE=1)

add_definitions(-DMAJOR_VERSION=${ELT_VERSION_MAJOR})
add_definitions(-DMINOR_VERSION=${ELT_VERSION_MINOR})
add_definitions(-DREVISION_VERSION=${ELT_VERSION_REVISION})

#configure_file (
#	${PROJECT_SOURCE_DIR}/elt.pc.in
#	${PROJECT_LIBRARY_DIR}/elt.pc
#)



if(CMAKE_COMPILER_IS_MINGW)
	#ADD_DEFINITIONS(
endif()


#	gnu compiler
if((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	if(BUILD_SHARED_LIBS)
		add_definitions(-fPIC)
	endif()
	add_definitions(-fvisibility=hidden -Wall)
elseif(MSVC)
	add_definitions(/MP)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()




if (WIN32)
    set(_EX_WIN32 1)
    message(STATUS "Using Win32 for window creation")

    if (EX_USE_EGL)
        set(_EX_EGL 1)
        message(STATUS "Using EGL for context creation")
    else()
        set(_EX_WGL 1)
        message(STATUS "Using WGL for context creation")
    endif()

elseif (APPLE)
    set(_EX_COCOA 1)
    message(STATUS "Using Cocoa for window creation")

    set(_EX_NSGL 1)
    message(STATUS "Using NSGL for context creation")


elseif (UNIX)

    if (EX_USE_WAYLAND)
        set(_EX_WAYLAND 1)
        message(STATUS "Using Wayland for window creation")
    else()
        set(_EX_X11 1)
        message(STATUS "Using X11 for window creation")
    endif()

    if (EX_USE_EGL)
        set(_EX_EGL 1)
        message(STATUS "Using EGL for context creation")
    else()
        set(_EX_GLX 1)
        message(STATUS "Using GLX for context creation")
    endif()


else()

    message(FATAL_ERROR "No supported platform was detected")
endif()






# TODO make it compadiable for what platform to port to.
FILE(GLOB _srcFiles
	"src/*.c"
	"src/graphic/*.c"
	"src/input/*.c"
	"src/system/*.c"
	"src/system/unix/*.c"
)

add_library(EngineEx ${_srcFiles})
target_link_libraries(EngineEx GL X11 OpenCL)


# add the install targets
install (TARGETS EngineEx DESTINATION lib)
install (FILES include/*.h DESTINATION include)

