#include"graphic/texture.h"
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


unsigned int is_texture_compressed(unsigned int textureid){
	int compress;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,GL_TEXTURE_COMPRESSED_ARB,&compress);
	return compress;
}



unsigned int getTextureTypeSize(unsigned int internalformat){
	switch(internalformat){
	case GL_LUMINANCE:
	case GL_LUMINANCE_ALPHA:
	case GL_ALPHA:
	case GL_INTENSITY:
	case GL_RED:
	case GL_BLUE:
	case GL_GREEN:
		return 1;
	case GL_RGB:
	case GL_RGB8:
	case GL_BGR:
		return 3;
	case GL_RGBA:
	case GL_BGRA:
		return 4;
	default:
		return 0;

	}
}
unsigned int getTextureLevelDatai(unsigned int textureid,unsigned int level, unsigned char** pixeldata){
	int width,height,bpp,internal;
	if(!pixeldata)
		return 0;
	glBindTexture(GL_TEXTURE_2D, textureid);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_INTERNAL_FORMAT, &internal);
	bpp = getTextureTypeSize(internal);

	pixeldata[0] = (unsigned char*)malloc(width * height * bpp);

	glGetTexImage(GL_TEXTURE_2D,level,internal, GL_UNSIGNED_BYTE,pixeldata[0]);

	return 1;
}



unsigned int getInternalSrgbType(unsigned int internal_format){
	switch(internal_format){
	case GL_RGB:return GL_SRGB;
	case GL_RGBA: return GL_SRGB8_ALPHA8;
	case GL_LUMINANCE: return GL_SLUMINANCE;
	case GL_COMPRESSED_RGB: return GL_COMPRESSED_SRGB;
	case GL_COMPRESSED_RGBA: return GL_COMPRESSED_SRGB_ALPHA;
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
	default:return internal_format;
	}
}

unsigned int getTextureDataSize(unsigned int textureid){
	int width, height,internalformat;
	glBindTexture(GL_TEXTURE_2D,textureid);
	if(!is_texture_compressed(textureid)){
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT, &height);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT, &internalformat);
		return width* height * getTextureTypeSize(internalformat);
	}
	else{
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB,&internalformat);
		return internalformat;
	}
}




float getMaxTextureAnisotropy(void){
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	return fLargest;
}
