#include"graphic/rendertexture.h"
#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
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

ExFrameBuffer* ExCreateRenderTexture2D(ExFrameBuffer* framebuffer,unsigned int width, unsigned int height,unsigned int attachment){
	if(!framebuffer)
		return NULL;

	glGenFramebuffers(1,&framebuffer->framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,framebuffer->framebuffer);




	glGenTextures(1,&framebuffer->texture.texture);
	glBindTexture(GL_TEXTURE_2D, framebuffer->texture.texture);


	return framebuffer;
}
ExFrameBuffer* ExCreateRenderTexture3D(ExFrameBuffer* framebuffer,unsigned int width, unsigned int height,unsigned int attachment){
	if(!framebuffer)
		return NULL;

	glGenFramebuffers(1,&framebuffer->framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,framebuffer->framebuffer);



	glGenTextures(1,&framebuffer->texture.texture);
	glBindTexture(GL_TEXTURE_3D, framebuffer->texture.texture);

}
