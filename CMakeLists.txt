cmake_minimum_required(VERSION 2.8.12)
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


# extracing version.
SET( FIXIT 's/[^0-9]*//g')
 #| sed -e ${FIXIT} | cut -c1-1
execute_process(COMMAND git describe
	    OUTPUT_VARIABLE _major_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _major_version_failed)

 #| sed -e 's/[^0-9].[^0-9]*//g' | cut -c1-1
execute_process(COMMAND  git describe
	    OUTPUT_VARIABLE _minor_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _minor_version_failed)

 #| sed -e 's/[^0-9].[^0-9].[^0-9]*//g' | cut -c1-2
execute_process(COMMAND git describe
	    OUTPUT_VARIABLE _revision_version OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _revision_version_failed)

SET(ELT_VERSION_MAJOR ${_major_version})
SET(ELT_VERSION_MINOR ${_minor_version})
SET(ELT_VERSION_REVISION ${_revision_version_failed})

IF(ELT_VERSION_MAJOR MATCHES "")
	SET(ELT_VERSION_MAJOR 0)
ENDIF()
IF(ELT_VERSION_MINOR MATCHES "")
	SET(ELT_VERSION_MINOR 6)
ENDIF()
IF(ELT_VERSION_REVISION MATCHES "")
	SET(ELT_VERSION_REVISION 8)
ENDIF()


SET(ELT_VERSION ${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION})
MESSAGE(STATUS "ELT version ${ELT_VERSION}.")

SET(PROJECT_VERSION "${ELT_VERSION}")

SET(ELT_PACKAGE_VERSION "" CACHE STRING "the package-specific version used for uploading the sources.")

ADD_DEFINITIONS(-DMAJOR_VERSION=${ELT_VERSION_MAJOR})
ADD_DEFINITIONS(-DMINOR_VERSION=${ELT_VERSION_MINOR})
ADD_DEFINITIONS(-DREVISION_VERSION=${ELT_VERSION_REVISION})

SET(CMAKE_MODULE_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )	#
SET(LIBELT_COMPONENT     "libelt${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION}" )
SET(LIBELT-DEV_COMPONENT "libelt${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION}-dev" )
SET(CPACK_COMPONENTS_ALL elt-bin ${LIBELT_COMPONENT} ${LIBELT-DEV_COMPONENT} elt-dev)

#Add for samples as well.


#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/elt-config.cmake"             "${CMAKE_CURRENT_BINARY_DIR}/elt-config-version.cmake" DESTINATION "${ELT_LIB_INSTALL_DIR}/cmake/elt-${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}" COMPONENT ${LIBELT-DEV_COMPONENT})

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
ENDIF()


#	OpenCL
FIND_PACKAGE(FindOpenCL)
IF(FindOpenCL_FOUND)
	INCLUDE(FindOpenCL)
	IF(OpenCL_FOUND)
		IF (CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)")
		ADD_DEFINITIONS(-DDONT_SUPPORT_OPENCL=1)
		ENDIF()

		ADD_DEFINITIONS(-I${OpenCL_INCLUDE_DIRS})
		ADD_DEFINITIONS(-L${OpenCL_LIBRARY})
		ADD_DEFINITIONS(-lOpenCL)
	ENDIF()
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





SET( elt_src
	${gCore}
	${gmaths}
	${gunix}
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

#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/elt.pc.in" "${PROJECT_BINARY_DIR}/elt.pc" @ONLY )
INSTALL( FILES "${PROJECT_BINARY_DIR}/elt.pc" DESTINATION ${ELT_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${ELT-DEV_COMPONENT})

IF ( UNIX )
	INSTALL (FILES ${unixinclude} DESTINATION include/ELT/system/unix)
ELSEIF (WIN32)
	INSTALL (FILES ${windowsinclude} DESTINATION include/ELT/system/win)
#ELSEIF (
ENDIF()



#debug file for windows.
IF(MSVC)
	OPTION(ELT_INSTALL_PDB "Install MSVC debug files." ON )
ENDIF(MSVC)



#debian package
IF (CMAKE_CPACK_COMMAND AND UNIX AND ELT_OPT_BUILD_PACKAGE)

	MESSAGE(STATUS "Generate CPack script.")
	IF(UNIX)
		SET(CPACK_GENERATOR "DEB")
	ELSE()
		SET(CPACK_GENERATOR "RPM")
	ENDIF()


	SET(CPACK_PACKAGE_NAME	"elt")
	SET(CPACK_PACKAGE_CONTACT "valdemar lindberg" CACHE STRING "Package maintainer and PGP signer.")
	SET(CPACK_PACKAGE_VENDOR "")
	SET(CPACK_PACKAGE_DISPLAY_NAME "ELT ${ELT_VERSION}")
	SET(CPACK_PACKAGE_DESCRIPTION "ELT (Engine Library Toolkit)")
	SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY " ELT (Engine Library Toolkit) ${ELT_VERSION} is a multiplatform API.")
	SET(CPACK_PACKAGE_VERSION "${ELT_VERSION}")
	SET(CPACK_PACKAGE_VERSION_MAJOR "${ELT_VERSION_MAJOR}")
	SET(CPACK_PACKAGE_VERSION_MINOR "${ELT_VERSION_MINOR}")
	SET(CPACK_PACKAGE_VERSION_PATCH "${ELT_VERSION_REVISION}")
	SET(CPACK_PACKAGE_INSTALL_DIRECTORY "elt${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}")
	SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
	SET(CPACK_PACKAGE_ICON  "${CMAKE_CURRENT_SOURCE_DIR}/elticon.ico")
	#SET(CPACK_RESOURCE_FILE_WELCOME )


	STRING(TOUPPER ${LIBELT_COMPONENT}     "LIBELT_COMPONENT_UPPER")
	STRING(TOUPPER ${LIBELT-DEV_COMPONENT} "LIBELT-DEV_COMPONENT_UPPER")

	SET(CPACK_COMPONENT_ELT-BIN_DISPLAY_NAME                       "tools")
	SET(CPACK_COMPONENT_ELT-BIN_DEPENDS                            "${LIBELT_COMPONENT}" )
	SET(CPACK_COMPONENT_${LIBELT_COMPONENT_UPPER}_DISPLAY_NAME     "libraries")
	SET(CPACK_COMPONENT_${LIBELT-DEV_COMPONENT_UPPER}_DISPLAY_NAME "common headers and installs")
	SET(CPACK_COMPONENT_${LIBELT-DEV_COMPONENT_UPPER}_DEPENDS      "${LIBELT_COMPONENT}" )
	SET(CPACK_COMPONENT_ELT-DEV_DISPLAY_NAME                       "${CPACK_COMPONENT_${LIBELT-DEV_COMPONENT}_DISPLAY_NAME}" )
	SET(CPACK_COMPONENT_ELT-DEV_DEPENDS                            "${LIBELT-DEV_COMPONENT}" )



	#	windows installer.	
	SET(CPACK_NSIS_DISPLAY_NAME "elt")



	#debian
	SET(CPACK_DEBIAN_BUILD_DEPENDS debhelper cmake pkg-config)
	SET(CPACK_DEBIAN_PACKAGE_PRIORITY extra)
	SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
	SET(CPACK_DEBIAN_CMAKE_OPTIONS "")
	SET(CPACK_DEBIAN_PACKAGE_DEPENDS "mesa-common-dev , libx11-dev , libx11-xcb-dev , libegl1-mesa-dev , libxrandr-dev , libgles2-mesa-dev , libopenal-dev , libxi-dev, libudev-dev, libglu1-mesa-dev,
 	libasound2-dev, libc6 (>= 2.1), opencl-headers, ${CPACK_COMPONENTS_ALL}")


	SET(CPACK_DEBIAN_PACKAGE_SUGGESTS "" )
	SET(CPACK_DEBIAN_PACKAGE_NAME "elt")
	SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
	#SET(CPACK_DEBIAN_PACKAGE_FILE_NAME "elt-${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}${ELT_VERSION_REVISION}")
	SET(CPACK_DEBIAN_PACKAGE_SOURCE_FILES ${_srcFiles} )
	SET(CPACK_DEBIAN_PACKAGE_REMOVE_SOURCE_FILES build CMakeFiles _CPack_Packages) #samplers docs
	SET(CPACK_DEBIAN_PACKAGE_SOURCE_COPY svn export --force)
	SET(CPACK_DEBIAN_CHANGELOG "" )
	SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Valdemar Lindberg") #required

	SET(CPACK_DEBIAN_DISTRIBUTION_NAME "")
	
	EXECUTE_PROCESS(COMMAND lsb_release -is
	    OUTPUT_VARIABLE _lsb_distribution OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _lsb_release_failed)
	SET(CPACK_DEBIAN_DISTRIBUTION_NAME ${_lsb_distribution} CACHE STRING "Name of the distrubiton")
	STRING(TOLOWER CPACK_DEBIAN_DISTRIBUTION_NAME CPACK_DEBIAN_DISTRIBUTION_NAME)
	IF( CPACK_DEBIAN_DISTRIBUTION_NAME STREQUAL "ubuntu" )
		SET(CPACK_DEBIAN_DISTRIBUTION_RELEASES lucid maverick natty oneiric precise CACHE STRING "Release code-names of the distrubiton release")
	ENDIF()



	SET(CPACK_SOURCE_GENERATOR "TGZ")
	SET(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
	SET(CPACK_SOURCE_IGNORE_FILES "/build/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")



	SET(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE OFF)
	SET(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
	INCLUDE(CPack)
 	INCLUDE(DebSourcePPA)

	SET(DPUT_HOST "" CACHE STRING "PPA repository to upload the debian source")
	#INCLUDE(UploadPPA)
ENDIF()

#	
if(WIN32)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin64/")
		set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib64/")
	elseif()
		set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin32/")
		set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib32/")
	endif()
	
	add_custom_target(UpdateELTLibDebugSymbolsAndDLLs COMMENT "Copying ELT Libraries ..." VERBATIM)


endif(WIN32)


#
IF(FALSE)
	FIND_PACKAGE(JNI)
	IF(JNI_FOUND)
		message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
		message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
	ENDIF()
ENDIF()


#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/elt-config
