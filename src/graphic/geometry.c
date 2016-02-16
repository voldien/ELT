#include"graphic/geometry.h"
#include<stdio.h>


#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif



#if defined(_WIN32)
	extern PFNGLBINDBUFFERPROC glBindBuffer;
#endif

int ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode){
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);

	return vbo;
}


//extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
void ExCreateVAO(int n, unsigned int* arg){
	glGenVertexArrays(n, arg);
}

