#include"graphic/geometry.h"
#ifdef GL_ES_VERSION_2_0
	#include<GLES/gl2.h>
	#include<GLES/gl2ext.h>
	#include<GLES/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif

int ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode){
	unsigned int vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,size,NULL, GL_STATIC_DRAW);
	return vbo;
}
