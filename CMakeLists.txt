cmake_minimum_required(VERSION 2.8.9)
project(ELT)


#	build shared/dynamic library option
OPTION (BUILD_SHARED_LIBS "Build package with shared libraries." ON)
if(NOT BUILD_SHARED_LIBS)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(LINK_SEARCH_START_STATIC TRUE)	
endif(NOT BUILD_SHARED_LIBS)





INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(./include)



OPTION (ELT_OPT_BUILD_PACKAGE "Set to ON to generate CPack configuration files and packaging targets" ON)


ADD_DEFINITIONS(-D_INTERNAL_ENGINE=1)


execute_process(COMMAND git describe
		COMMAND sed -e "s/[^0-9]*//g"
		COMMAND cut -c1-1
	    OUTPUT_VARIABLE _major_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _major_version_failed)

execute_process(COMMAND git describe
		COMMAND sed -e "s/[^0-9].[^0-9]*//g"
		COMMAND cut -c1-1
	    OUTPUT_VARIABLE _minor_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _minor_version_failed)

execute_process(COMMAND git describe
		COMMAND sed -e "s/[^0-9].[^0-9].[^0-9]*//g"
		COMMAND cut -c1-2
	    OUTPUT_VARIABLE _revision_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _revision_version_failed)

SET(ELT_VERSION_MAJOR ${_major_version})
SET(ELT_VERSION_MINOR ${_minor_version})
SET(ELT_VERSION_REVISION ${_revision_version})

SET(ELT_VERSION ${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION})
MESSAGE(STATUS "ELT version ${ELT_VERSION}.")

SET(PROJECT_VERSION "${ELT_VERSION}")

SET(ELT_PACKAGE_VERSION "" CACHE STRING "the package-specific version used for uploading the sources.")

ADD_DEFINITIONS(-DMAJOR_VERSION=${ELT_VERSION_MAJOR})
ADD_DEFINITIONS(-DMINOR_VERSION=${ELT_VERSION_MINOR})
ADD_DEFINITIONS(-DREVISION_VERSION=${ELT_VERSION_REVISION})

SET(CMAKE_MODULE_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )	#
#Add for samples as well.

#configure_file (
#	${PROJECT_SOURCE_DIR}/elt.pc.in
#	${PROJECT_LIBRARY_DIR}/elt.pc
#)




if(CMAKE_COMPILER_IS_MINGW)
	ADD_DEFINITIONS(-ELT_BUILD_NO_IFC_IMPORTER )
endif()

#	gnu compiler
if((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )
	endif()

	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall" )


	ADD_DEFINITIONS( -Wall -w -I"include" -fPIC -DVD_INTERNAL -fpermissive -Wfatal-errors ) 
	IF (CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE(STATUS "Compile for release.")
		ADD_DEFINITIONS(-DNDEBUG)
		ADD_DEFINITIONS(-O3)
		SET(CMAKE_RELEASE TRUE)
		SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
	ELSE()
		MESSAGE(STATUS "Compile for debug.")
		ADD_DEFINITIONS(-D_DEBUG)
		ADD_DEFINITIONS(-g3)
		SET(CMAKE_DEBUG TRUE)
	ENDIF()


elseif(MSVC)
	ADD_DEFINITIONS(/MP)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

	FIND_PACKAGE( DirectX )

endif()





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



IF (CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Debug Postfix for lib, samples and tools")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -s" )
ELSE()
  	SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug Postfix for lib, samples and tools")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g" )
ENDIF()




IF ( NOT TARGET uninstall)


ENDIF()


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

elseif(ANDROID)


else()

    message(FATAL_ERROR "No supported platform was detected")
endif()



INCLUDE(FindOpenGL)
IF(OPENGL_FOUND)

	
	IF(OPENGL_GLU_FOUND)
	ADD_DEFINITIONS(-L${OPENGL_glu_LIBRARY})

	ENDIF()
ELSE()

ENDIF()


#	OpenCL
FIND_PACKAGE(OpenCL)
IF(FindOpenCL_FOUND)
	INCLUDE(OpenCL)
ENDIF()
IF(OpenCL_FOUND OR USE_OPENCL)
	MESSAGE(STATUS "Using OpenCL")
	ADD_DEFINITIONS(-DSUPPORT_OPENCL=1)

	ADD_DEFINITIONS(-I${OPENCL_INCLUDE_DIRS})
	ADD_DEFINITIONS(-L${OPENCL_LIBRARIES})
	SET(LINK_LIBRARIES "${LINK_LIBRARIES}-lOpenCL")
ENDIF()



#ADD_SUBDIRECTORY( src/ )


# TODO make it compadiable for what platform to port to.

FILE(GLOB gCore		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/input/*.c"
)

FILE(GLOB gmaths	"${CMAKE_CURRENT_SOURCE_DIR}/src/math/*.c")

FILE(GLOB gunix		"${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.c")
FILE(GLOB gwin 		"${CMAKE_CURRENT_SOURCE_DIR}/src/system/win/*.c")
FILE(GLOB graphic	"${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/*.c")
FILE(GLOB gandroid	"")
FILE(GLOB gnacl	"")
FILE(GLOB gmac	"")


SOURCE_GROUP( core 	FILES	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
				"${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c"
				"${CMAKE_CURRENT_SOURCE_DIR}/src/input/*.c")
SOURCE_GROUP( maths	FILES	"${CMAKE_CURRENT_SOURCE_DIR}/src/math/*.c")

SOURCE_GROUP( windows 	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/win/*.c")
SOURCE_GROUP( android 	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/android/*.c")
SOURCE_GROUP( nacl	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/nacl/*.c")
SOURCE_GROUP( unix	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.c")
SOURCE_GROUP( mac	FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/src/system/mac/*.c")

FILE(GLOB includes		"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB mathinclude		"${CMAKE_CURRENT_SOURCE_DIR}/include/math/*.h" )
FILE(GLOB systeminclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/*.h")
FILE(GLOB inputinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/input/*.h")
FILE(GLOB unixinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/system/unix/*.h")
FILE(GLOB windowsinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/win/*.h")
FILE(GLOB graphicinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/graphic/*.h")
FILE(GLOB androidinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/android/*.h")




SET( elt_src
	${gCore}
	${gmaths}
	${gunix}
	${graphic}
)

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
				 -lX11
				 
)


# add the install targets
INSTALL (TARGETS EngineEx DESTINATION lib)
INSTALL (FILES ${includes} DESTINATION include/ELT)
INSTALL (FILES ${mathinclude} DESTINATION include/ELT/math)
INSTALL (FILES ${graphicinclude} DESTINATION include/ELT/graphic)
INSTALL (FILES ${systeminclude} DESTINATION include/ELT/system)
INSTALL (FILES ${inputinclude} DESTINATION include/ELT/input)
INSTALL (FILES ${graphicinclude} DESTINATION include/ELT/graphic)
INSTALL (FILES ${androidinclude} DESTINATION include/ELT/system/android)

#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/elt.pc.in" "${PROJECT_BINARY_DIR}/elt.pc" @ONLY )
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
