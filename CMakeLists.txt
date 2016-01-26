cmake_minimum_required(VERSION 2.8)
project(ELT)


#	build shared/dynamic library option
OPTION (BUILD_SHARED_LIBS "Build package with shared libraries." ON)

if(NOT BUILD_SHARED_LIBS)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(LINK_SEARCH_START_STATIC TRUE)	
endif(NOT BUILD_SHARED_LIBS)


set (ELT_VERSION_MAJOR 0)
set (ELT_VERSION_MINOR 6)
set (ELT_VERSION_REVISION 64)
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




# Generate a pkg-config .pc for the Assimp library.
#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/elt.pc.in" "${PROJECT_BINARY_DIR}/elt.pc" @ONLY )
#INSTALL( FILES "${PROJECT_BINARY_DIR}/elt.pc" DESTINATION ${ASSIMP_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBASSIMP-DEV_COMPONENT})





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



#debian package
IF (CMAKE_CPACK_COMMAND AND UNIX )
	SET(CPACK_PACKAGE_NAME	"ELT")
	SET(CPACK_PACKAGE_CONTACT "" CACHE STRING "Package maintainer and PGP signer.")
	SET(CPACK_PACKAGE_VENDOR "")
	SET(CPACK_PACKAGE_DISPLAY_NAME "")
	SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
	SET(CPACK_PACKAGE_VERSION "")
	SET(CPACK_PACKAGE_VERSION_MAJOR "")
	SET(CPACK_PACKAGE_VERSION_MINOR "")
	SET(CPACK_PACKAGE_VERSION_PATCH "")
	SET(CPACK_PACKAGE_INSTALL_DIRECTORY "")
	SET(CPACK_RESOURCE_FILE_LICENSE "LICENSE")


	#SET(CPACK_

	#debian
	SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
	SET(CPACK_DEBIAN_CMAKE_OPTIONS "")
	SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
	SET(CPACK_DEBIAN_DEPEND "")
	SET(CPACK_DEBIAN_PACKAGE_SUGGETS)
	SET(CPACK_DEBIAN_PACKAGE_NAME "elt")
	SET(CPACK_DEBIAN_PACKAAGE_REMOVE_SOURCE_FILES )
	SET(CPACK_DEBIAN_PACKAGE_SOURCE_COPY )
	SET(CPACK_DEBIAN_CHANGELOG)

	SET(CPACK_DEBIAN_DISTRIBUTION_NAME )
	
	execute_process(COMMAND lsb_release -is
	    OUTPUT_VARIABLE _lsb_distribution OUTPUT_STRIP_TRAILING_WHITESPACE
	    RESULT_VARIABLE _lsb_release_failed)
	  set(CPACK_DEBIAN_DISTRIBUTION_NAME ${_lsb_distribution} CACHE STRING "Name of the distrubiton")
	string(TOLOWER ${CPACK_DEBIAN_DISTRIBUTION_NAME} CPACK_DEBIAN_DISTRIBUTION_NAME)
	if( ${CPACK_DEBIAN_DISTRIBUTION_NAME} STREQUAL "ubuntu" )
		SET(CPACK_DEBIAN_DISTRUBTION_RELEASES lucid maveric natty oneiric previse CACHE STRING "Release code-names of distrubtions release")
	endif()
	set(DPUT_HOST "" CACHE STRING "PPA repository to upload the debian source")
	INCLUDE(CPack)
	#INCLUDE(DebSourcePPA)
		
ENDIF()


if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin64/")
		set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib64/")
	elseif()
		set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin32/")
		set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib32/")
	endif()
	
	add_custom_target(UpdateELTLibDebugSymbolsAndDLLs COMMENT "Copying ELT Libraries ..." VERBATIM)


endif(WIN32)


#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/elt-config.

