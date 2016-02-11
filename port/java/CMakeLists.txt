#
cmake_minimum_required( VERSION 2.8 )
project (ELT)

FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
FIND_PACKAGE(Java REQUIRED COMPONENTS Runtime Development)

include(UseJava)
include(UseSWIG)

FILE(GLOB source "./../../src/*.c")

add_library (ELT ${source})
SET_TARGET_PROPERTIES(ELT PROPERTIES LINKER_LANGUAGE C)


set(CMAKE_SWIG_FLAGS -package example)
set(CMAKE_SWIG_OUTDIR "example")

#SET_SOURCE_FILES_PROPERTIES(example.i PROPERTIES CPLUSPLUS 0)
#SET_SOURCE_FILES_PROPERTIES(example.i PROPERTIES SWIG_FLAGS "-includeall")


set(CMAKE_JNI_TARGET TRUE)

#add_jar(example_swig_jar 
#       	VERSION 1.2.0#
#	ENTRY_POINT example)
#install_jar(example_swig_jar ${LIB_INSTALL_DIR}/example)
#install_jni_symlink(example_swig_jar .)



swig_add_module(example_swig java example.i  ${source})
swig_link_libraries(example_swig Example)


set(JAVA_BUNDLE_SO_FILES "${CMAKE_HOME_DIRECTORY}/libexample_swig.so")

DD_CUSTOM_COMMAND(TARGET example_swig
                   POST_BUILD
		   DEPEND example_swig_jar
		   COMMAND ${JAVA_BUNDLE} "example_swig_jar.jar" "${Java_JAVA_EXECUTABLE}" "example.NativeLib" "${CMAKE_STRIP}" -so ${JAVA_BUNDLE_SO_FILES} -txt ${JAVA_BUNDLE_TXT_FILES}
                   COMMAND ${JAVA_ARCHIVE} -uvf "example_swig_jar.jar" "NATIVE"
		   COMMAND ${CMAKE_COMMAND} -E echo "Class-Path: ." > ${MANIFEST_FILE}
                   COMMAND ${JAVA_ARCHIVE} -uvmf "MANIFEST" "example_swig_jar.jar"
                   COMMAND ${CMAKE_COMMAND} -E remove ${MANIFEST_FILE}
		   )



ADD_CUSTOM_COMMAND(TARGET example_swig
                   POST_BUILD
	           COMMAND ${JAVA_COMPILE} "example_test.java")
