CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT(ELT)

# Build shared/dynamic library option
OPTION (BUILD_SHARED_LIBS "Build package with shared libraries." ON)
IF(NOT BUILD_SHARED_LIBS)
	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	SET(LINK_SEARCH_START_STATIC TRUE)	
ENDIF(NOT BUILD_SHARED_LIBS)

#
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 7)
SET(VERSION_REVISION 2)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )

#
MESSAGE(STATUS "ELT version ${VERSION}.")
SET(PROJECT_VERSION "${VERSION}")

#
ADD_DEFINITIONS(-DMAJOR_VERSION=${VERSION_MAJOR})
ADD_DEFINITIONS(-DMINOR_VERSION=${VERSION_MINOR})
ADD_DEFINITIONS(-DREVISION_VERSION=${VERSION_REVISION})
ADD_DEFINITIONS(-DVERSION=${VERSION})
ADD_DEFINITIONS(-D_INTERNAL_ENGINE=1)

#
SET(CMAKE_MODULE_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )

# 
IF(CMAKE_COMPILER_IS_MINGW)
	ADD_DEFINITIONS(-ELT_BUILD_NO_IFC_IMPORTER )
ENDIF()

# GNU C compiler
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )
	ENDIF()

	ADD_DEFINITIONS( -Wall -w -DVD_INTERNAL -fpermissive -Wfatal-errors ) 

	IF (CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE(STATUS "Compile for release.")
		ADD_DEFINITIONS(-DNDEBUG)
		ADD_DEFINITIONS(-O2)
		SET(CMAKE_RELEASE TRUE)
		SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
	ELSE()
		MESSAGE(STATUS "Compile for debug.")
		ADD_DEFINITIONS(-D_DEBUG)
		ADD_DEFINITIONS(-g3)
		SET(CMAKE_DEBUG TRUE)
	ENDIF()

ELSEIF(MSVC)
	ADD_DEFINITIONS(/MP)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

	# Find DirectX for DirectX support.
	FIND_PACKAGE( DirectX )
	
ENDIF()

#
IF ( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin" )
ENDIF ( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )

# Cache these to allow the user to override them manually.
SET( ELT_LIB_INSTALL_DIR "lib" CACHE PATH
  "Path the built library files are installed to." )
SET( ELT_INCLUDE_INSTALL_DIR "include" CACHE PATH
  "Path the header files are installed to." )
SET( ELT_BIN_INSTALL_DIR "bin" CACHE PATH
  "Path the tool executables are installed to." )

#
IF (CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Debug Postfix for lib, samples and tools")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -s" )
ELSE()
  	SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug Postfix for lib, samples and tools")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g" )
ENDIF()

IF (WIN32)
	SET(_EX_WIN32 1)
	MESSAGE(STATUS "Using Win32 for window creation")

    IF (EX_USE_EGL)
	SET(_EX_EGL 1)
	MESSAGE(STATUS "Using EGL for context creation")
    ELSE()
	SET(_EX_WGL 1)
	MESSAGE(STATUS "Using WGL for context creation")
    ENDIF()

ELSEIF (APPLE)
    set(_EX_COCOA 1)
    message(STATUS "Using Cocoa for window creation")

    set(_EX_NSGL 1)
    message(STATUS "Using NSGL for context creation")


ELSEIF (UNIX)

    IF (EX_USE_WAYLAND)
        set(_EX_WAYLAND 1)
        message(STATUS "Using Wayland for window creation")
    ELSE()
        set(_EX_X11 1)
        message(STATUS "Using X11 for window creation")
    ENDIF()

    IF (EX_USE_EGL)
        set(_EX_EGL 1)
        message(STATUS "Using EGL for context creation")
    ELSE ()
        set(_EX_GLX 1)
        message(STATUS "Using GLX for context creation")
    ENDIF ()

ELSEIF(ANDROID)


ELSE()

    message(FATAL_ERROR "No supported platform was detected")
ENDIF()


# Find OpenGL on the system.
INCLUDE(FindOpenGL)
IF(OPENGL_FOUND)
	MESSAGE(STATUS "Find OpenGL.")

	IF(OPENGL_GLU_FOUND)
		ADD_DEFINITIONS(-L${OPENGL_glu_LIBRARY})
	ENDIF()
ELSE()
	MESSAGE(STATUS "Couldn't find OpenGL.")
ENDIF()


# OpenCL
FIND_PACKAGE(OpenCL)
IF(FindOpenCL_FOUND)
	INCLUDE(OpenCL)
ENDIF()

# Check if OpenCL is presented.
IF(OpenCL_FOUND OR USE_OPENCL)
	#
	MESSAGE(STATUS "Using OpenCL")
	ADD_DEFINITIONS(-DSUPPORT_OPENCL=1)

	ADD_DEFINITIONS(-I${OPENCL_INCLUDE_DIRS})
	ADD_DEFINITIONS(-L${OPENCL_LIBRARIES})
	SET(LINK_LIBRARIES "${LINK_LIBRARIES}-lOpenCL")
ELSE()
	MESSAGE(STATUS "OpenCL could not be found on the system.")
	ADD_DEFINITIONS(-DSUPPORT_OPENCL=0)
ENDIF()

# TODO make it compadiable for what platform to port to.

FILE(GLOB gCore		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/input/*.c"
)

#
FILE(GLOB gunix		"${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.c")
FILE(GLOB gwin 		"${CMAKE_CURRENT_SOURCE_DIR}/src/system/win/*.c")
FILE(GLOB graphic	"${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/*.c")
FILE(GLOB gandroid	"")
FILE(GLOB gnacl	"")
FILE(GLOB gmac	"")


# Core source code with no platform dependency.
SOURCE_GROUP( core 	FILES	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
				"${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c"
				"${CMAKE_CURRENT_SOURCE_DIR}/src/input/*.c")

# Platform soruce code.
SOURCE_GROUP( windows 	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/win/*.c")
SOURCE_GROUP( android 	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/android/*.c")
SOURCE_GROUP( nacl	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/nacl/*.c")
SOURCE_GROUP( unix	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.c")
SOURCE_GROUP( mac	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/mac/*.c")

#
FILE(GLOB includes		"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB mathinclude		"${CMAKE_CURRENT_SOURCE_DIR}/include/math/*.h" )
FILE(GLOB systeminclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/*.h")
FILE(GLOB inputinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/input/*.h")
FILE(GLOB unixinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/system/unix/*.h")
FILE(GLOB windowsinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/win/*.h")
FILE(GLOB graphicinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/graphic/*.h")
FILE(GLOB androidinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/android/*.h")

#
SET( elt_src ${gCore} ${gmaths} ${gunix} ${graphic} )

# Add library target.
ADD_LIBRARY(EngineEx ${elt_src} )
TARGET_LINK_LIBRARIES(EngineEx
				 -lX11
				 -lEGL
				 -lXrender
				 -lpthread
				 -ldl
				 -lrt
				 -lxcb
				 -lX11-xcb
				 -lXrandr
				 -lm
				 -lopenal
				 ${OPENGL_LIBRARIES}
				 ${LINK_LIBRARIES}
				 -lGLU
				 
)

# Add the install targets
INSTALL (TARGETS EngineEx DESTINATION lib)
INSTALL (FILES ${includes} DESTINATION include/ELT)
INSTALL (FILES ${mathinclude} DESTINATION include/ELT/math)
INSTALL (FILES ${graphicinclude} DESTINATION include/ELT/graphic)
INSTALL (FILES ${systeminclude} DESTINATION include/ELT/system)
INSTALL (FILES ${inputinclude} DESTINATION include/ELT/input)
INSTALL (FILES ${graphicinclude} DESTINATION include/ELT/graphic)
INSTALL (FILES ${androidinclude} DESTINATION include/ELT/system/android)

INSTALL( FILES "${PROJECT_BINARY_DIR}/elt.pc" DESTINATION ${ELT_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${ELT-DEV_COMPONENT})

IF ( UNIX )
	INSTALL (FILES ${unixinclude} DESTINATION include/ELT/system/unix)
ELSEIF (WIN32)
	INSTALL (FILES ${windowsinclude} DESTINATION include/ELT/system/win)
ENDIF()

IF( UNIX )	
	SET( TARGETDIR "${PROJECT_NAME}-${VERSION}")
	ADD_CUSTOM_TARGET(	distribution
				COMMAND mkdir -p ${TARGETDIR}
				COMMAND cp -r src include samples shader CMakeLists.txt LICENSE ${TARGETDIR}
				COMMAND tar cf - ${TARGETDIR} | gzip -c > ${TARGETDIR}.tar.gz 
				COMMAND rm -r ${TARGETDIR} )
ENDIF()
