#include"graphic/rendertexture.h"
#include"graphic/texture.h"


#include<EGL/egl.h>
#include<EGL/eglext.h>


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


#ifdef _WIN32
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
#endif




ExFrameBuffer* ExCreateRenderTexture2D(ExFrameBuffer* framebuffer, unsigned int width, unsigned int height, unsigned int attachment){
	GLenum State;
	if(!framebuffer)
		return NULL;

	glGenFramebuffers(1,&framebuffer->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer->framebuffer);


	ExCreateTexture(&framebuffer->texture,GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER,attachment,framebuffer->texture.target,framebuffer->framebuffer,0);


	glDrawBuffers(1, &attachment);
	State = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(State != GL_FRAMEBUFFER_COMPLETE){
		printf("Failed to Initilize ForwardRendering FrameBuffer! | %d",glGetError());
		return NULL;
	}


	glBindFramebuffer(GL_FRAMEBUFFER,0);
	return framebuffer;
}


void ExDestroyRenderTexture(ExFrameBuffer* framebuffer){
	ExDeleteTexture(&framebuffer->texture);

	glDeleteFramebuffers(1,&framebuffer->framebuffer);
	glIsFramebuffer(framebuffer->framebuffer);
}





