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



ExTexture* ExCreateTexture(ExTexture* texture, unsigned int target, int level,
        int internalFormat,
        int width, int height,
        int border, unsigned int format, unsigned int type,
        const void *pixels ){
	if(!texture)
		return NULL;

	texture->target = target;
	texture->internalformat = internalFormat;
	texture->width = width;
	texture->height = height;
	texture->internalformat = format;
	texture->type = type;


	glGenTextures(1,&texture->texture);
	glBindTexture(target,texture->texture);
	glPixelStorei(GL_PACK_ALIGNMENT,4);


	switch(target){
	case GL_TEXTURE_2D:
		glTexImage2D(target,level,internalFormat,width, height,border, format,type,pixels);
		break;
#ifndef GL_ES_VERSION_2_0
	case GL_TEXTURE_1D:
		glTexImage1D(target,level,internalFormat,width,border, format,type,pixels);
		break;

	case GL_TEXTURE_2D_ARRAY:
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, level, texture->internalformat, width, height, texture->layer);
		break;

	case GL_TEXTURE_3D:
		break;
#endif
	}


	glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_REPEAT);


	return texture;
}


void ExSubTexture(ExTexture* texture, int level, int xoffset, int yoffset, int width, int height,int format,int type, const void *pixels ){
	glBindTexture(texture->target,texture->texture);
	switch(texture->target){
	case GL_TEXTURE_2D:
		glTexSubImage2D(texture->target,level,xoffset,yoffset,width,height,format,type,pixels);
		break;
#ifndef GL_ES_VERSION_2_0
	case GL_TEXTURE_1D:
		glTexSubImage1D(texture->target,level,xoffset,width,format,type,pixels);
		break;
	case GL_TEXTURE_2D_ARRAY:
		glTexSubImage3D(texture->target,level,xoffset,yoffset,0,width,height,0,format,type,pixels);
		break;
#endif
	}
}

void ExDeleteTexture(ExTexture* texture){
	glDeleteTextures(1,&texture->texture);
}




unsigned int is_texture_compressed(unsigned int textureid){
	int compress;
	//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,GL_TEXTURE_COMPRESSED_ARB,&compress);
	return compress;
}



unsigned int ExGetTextureTypeSize(unsigned int internalformat){
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

unsigned int ExGetTextureTypeBits(unsigned int internalformat){

}



unsigned int ExGetTextureLevelDatai(unsigned int textureid,unsigned int level, unsigned char** pixeldata){
	int width,height,bpp,internal;
	if(!pixeldata)
		return 0;
	glBindTexture(GL_TEXTURE_2D, textureid);
	/*
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,level,GL_TEXTURE_INTERNAL_FORMAT, &internal);
	bpp = ExGetTextureTypeSize(internal);

	pixeldata[0] = (unsigned char*)malloc(width * height * bpp);

	glGetTexImage(GL_TEXTURE_2D,level,internal, GL_UNSIGNED_BYTE,pixeldata[0]);
	 */
	return 1;
}



unsigned int ExGetInternalSrgbType(unsigned int internal_format){
	switch(internal_format){
	/*
	case GL_RGB:return GL_SRGB;
	case GL_RGBA: return GL_SRGB8_ALPHA8;
	case GL_LUMINANCE: return GL_SLUMINANCE;
	case GL_COMPRESSED_RGB: return GL_COMPRESSED_SRGB;
	case GL_COMPRESSED_RGBA: return GL_COMPRESSED_SRGB_ALPHA;
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
	*/
	default:return internal_format;
	}
}

unsigned int ExGetTextureDataSize(unsigned int textureid){
	int width, height,internalformat;
	glBindTexture(GL_TEXTURE_2D,textureid);


	if(!is_texture_compressed(textureid)){
#ifndef GL_ES_VERSION_2_0
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT, &height);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT, &internalformat);
#endif
		return width* height * ExGetTextureTypeSize(internalformat);
	}
	else{
		//glGetTexLevelParameteriv(GL_TEXTURE_2D,0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB,&internalformat);
		return internalformat;
	}
}



void ExSetTextureAnisotropy(ExTexture* texture,float anisotropy){
	glBindTexture(texture->target,texture->texture);
#ifndef GL_ES_VERSION_2_0
	glTexParameteri(texture->target, GL_TEXTURE_MAX_ANISOTROPY_EXT,anisotropy);
#endif
}


float ExGetMaxTextureAnisotropy(void){
	float fLargest;
#ifndef GL_ES_VERSION_2_0
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
#endif
	return fLargest;
}
