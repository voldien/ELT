cmake_minimum_required(VERSION 2.8.12)
project(ELT)


#	build shared/dynamic library option
OPTION (BUILD_SHARED_LIBS "Build package with shared libraries." ON)

if(NOT BUILD_SHARED_LIBS)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(LINK_SEARCH_START_STATIC TRUE)	
endif(NOT BUILD_SHARED_LIBS)


set (ELT_VERSION_MAJOR 0)
set (ELT_VERSION_MINOR 6)
set (ELT_VERSION_REVISION 65)
set (ELT_VERSION ${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}.${ELT_VERSION_REVISION})

set (PROJECT_VERSION "${ELT_VERSION}")

set(ELT_PACKAGE_VERSION "0" CACHE STRING "the package-specific version used for uploading the sources.")





include_directories(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(./include)



OPTION (ELT_OPT_BUILD_PACKAGE "Set to ON to generate CPack configuration files and packaging targets" OFF)


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
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_definitions(-fPIC)
	endif()
	add_definitions( -fvisibility=hidden )
	add_definitions( -Wall )
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden -Wall" )
elseif(MSVC)
	add_definitions(/MP)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

	FIND_PACKAGE( DirectX )

endif()


IF (CMAKE_BUILD_TYPE STREQUAL "Release")
  SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Debug Postfix for lib, samples and tools")
ELSE()
  SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug Postfix for lib, samples and tools")
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


SOURCE_GROUP( core 	FILES "src/*.c" "src/system/*.c")
SOURCE_GROUP( windows 	FILES "src/system/win/*.c")
SOURCE_GROUP( android 	FILES "src/system/android/*.c")
SOURCE_GROUP( nacl	FILES "src/nacl/*.c")
SOURCE_GROUP( unix	FILES "src/system/unix/*.c")
SOURCE_GROUP( mac	FILES "src/system/mac/*.c")

FILE(GLOB includes		"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB systeminclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/*.h")
FILE(GLOB inputinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/input/*.h")
FILE(GLOB unixinclude 		"${CMAKE_CURRENT_SOURCE_DIR}/include/system/unix/*.h")
FILE(GLOB windowsinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/system/win/*.h")
FILE(GLOB graphicinclude 	"${CMAKE_CURRENT_SOURCE_DIR}/include/graphic/*.h")

add_library(EngineEx ${_srcFiles})
target_link_libraries(EngineEx libGL.so libX11.so libOpenCL.so)




# add the install targets
INSTALL (TARGETS EngineEx DESTINATION lib)
INSTALL (FILES ${includes} DESTINATION include/ELT)
INSTALL (FILES ${systeminclude} DESTINATION include/ELT/system)
INSTALL (FILES ${inputinclude} DESTINATION include/ELT/input)
INSTALL (FILES ${graphicinclude} DESTINATION include/ELT/graphic)
IF ( UNIX )
	INSTALL (FILES ${unixinclude} DESTINATION include/ELT/system/unix)
ELSEIF (WIN32)
	INSTALL (FILES ${windowsinclude} DESTINATION include/ELT/system/win)
ENDIF()

# Generate a pkg-config .pc for the Assimp library.
#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/elt.pc.in" "${PROJECT_BINARY_DIR}/elt.pc" @ONLY )
#INSTALL( FILES "${PROJECT_BINARY_DIR}/elt.pc" DESTINATION ${ASSIMP_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBASSIMP-DEV_COMPONENT})

#debian package
#ELT_OPT_BUILD_PACKAGE
IF (CMAKE_CPACK_COMMAND AND UNIX )

	IF(UNIX)
	SET(CPACK_GENERATOR "DEB")
	ENDIF()


	SET(CPACK_PACKAGE_NAME	"elt")
	SET(CPACK_PACKAGE_CONTACT "" CACHE STRING "Package maintainer and PGP signer.")
	SET(CPACK_PACKAGE_VENDOR "http://elt.linuxsenpai.org/")
	SET(CPACK_PACKAGE_DISPLAY_NAME "ELT ${ELT_VERSION}")
	SET(CPACK_PACKAGE_DESCRIPTION "ELT (Engine Library Toolkit)")
	SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY " ELT (Engine Library Toolkit) ${ELT_VERSION} is a multiplatform API.")
	SET(CPACK_PACKAGE_VERSION "${ELT_VERSION}")
	SET(CPACK_PACKAGE_VERSION_MAJOR "${ELT_VERSION_MAJOR}")
	SET(CPACK_PACKAGE_VERSION_MINOR "${ELT_VERSION_MINOR}")
	SET(CPACK_PACKAGE_VERSION_PATCH "${ELT_VERSION_REVISION}")
	SET(CPACK_PACKAGE_INSTALL_DIRECTORY "elt${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}")
	SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
	#http://stackoverflow.com/questions/28768417/how-to-set-an-icon-in-nsis-install-cmake
	#SET(CPACK_PACKAGE_ICON  "${CMAKE_CURRENT_SOURCE_DIR}/elt.ico")
	SET(CPACK_RESOURCE_FILE_WELCOME )

	#SET(CPACK_
	SET(CPACK_DEBIAN_BUILD_DEPENDS debhelper cmake pkg-config)

	#debian
	SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
	SET(CPACK_DEBIAN_CMAKE_OPTIONS "")
	SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
	SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE all) #
	SET(CPACK_DEBIAN_PACKAGE_DEPENDS "mesa-common-dev, libx11-dev, libx11-xcb-dev, libegl1-mesa-dev, libxrandr-dev, libgles2-mesa-dev, libopenal-dev, libxi-dev, libudev-dev, libglu1-mesa-dev, libasound2-dev, libc6 (>= 2.1), opencl-headers")
	SET(CPACK_DEBIAN_PACKAGE_SUGGESTS "" )
	SET(CPACK_DEBIAN_PACKAGE_NAME "elt")
	#SET(CPACK_DEBIAN_PACKAGE_FILE_NAME "elt-${ELT_VERSION_MAJOR}.${ELT_VERSION_MINOR}${ELT_VERSION_REVISION}")
	SET(CPACK_DEBIAN_PACKAGE_SOURCE_FILES ${_srcFiles} )
	SET(CPACK_DEBIAN_PACKAGE_REMOVE_SOURCE_FILES build ) #samplers docs
	SET(CPACK_DEBIAN_PACKAGE_SOURCE_COPY svn export --force)
	SET(CPACK_DEBIAN_CHANGELOG "" )
	SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Valdemar Lindberg") #required


	SET(CPACK_DEBIAN_DISTRIBUTION_NAME )
	
	execute_process(COMMAND lsb_release -is
	    OUTPUT_VARIABLE _lsb_distribution OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _lsb_release_failed)
	  set(CPACK_DEBIAN_DISTRIBUTION_NAME ${_lsb_distribution} CACHE STRING "Name of the distrubiton")
	string(TOLOWER ${CPACK_DEBIAN_DISTRIBUTION_NAME} CPACK_DEBIAN_DISTRIBUTION_NAME)
	if( ${CPACK_DEBIAN_DISTRIBUTION_NAME} STREQUAL "ubuntu" )
	    set(CPACK_DEBIAN_DISTRIBUTION_RELEASES lucid maverick natty oneiric precise CACHE STRING "Release code-names of the distrubiton release")
	endif()

	#set(DPUT_HOST "" CACHE STRING "PPA repository to upload the debian source")
	INCLUDE(CPack)
	#INCLUDE(DebSourcePPA)
		
	# set(CPACK_DEBIAN_PACKAGE_SECTION devel)

ENDIF()


if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin64/)
		set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib64/)
	elseif()
		set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin32/)
		set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib32/)
	endif()
	
	add_custom_target(UpdateELTLibDebugSymbolsAndDLLs COMMENT "Copying ELT Libraries ..." VERBATIM)


endif(WIN32)


#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/elt-config.

