#include"graphic/geometry.h"
#include<stdio.h>


#ifdef GL_ES_VERSION_3_0
	#undef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif

#if defined(_WIN32)
	extern PFNGLBINDBUFFERPROC glBindBuffer;
#endif

void ExGenBuffers(int n, unsigned int* buffers){
	glGenBuffers(n, buffers);
}


int ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode){
	unsigned int vbo;
	ExGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, size, NULL, mode);
	return vbo;
}



void ExSetBufferSize(unsigned int target, unsigned int buffer, unsigned int size, unsigned int mode){
	glBindBuffer(target, buffer);
	glBufferData(target, size, NULL, mode);
}


//extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
void ExCreateVAO(int n, unsigned int* arg){
	glGenVertexArrays(n, arg);
}



int ExDestroyBuffer(unsigned int buffer){
	glDeleteBuffers(1, &buffer);
	return glIsBuffer(buffer) != GL_FALSE;
}

