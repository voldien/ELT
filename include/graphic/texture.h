/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_TEXTURE_H_ 
#define _ELT_TEXTURE_H_ 1

typedef struct ex_texture{
	unsigned int target;
	unsigned int texture;
	unsigned int width;
	unsigned int height;
	unsigned int layer;
	unsigned int type;
	unsigned int internalformat;
}ExTexture;


#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/*
	return texture internal type in size in bytes
*/
extern unsigned int ExGetTextureTypeSize(unsigned int internalformat);

/*
	return texture internal type in size in bits
*/

extern unsigned int ExGetTextureTypeBits(unsigned int internalformat);

/**
	Get texture Internal format by number of bits
*/
extern unsigned int ExGetTextureTypeBySize(unsigned int bytesperpixel);


/**
	Get texture Internal format by number of bits
*/
extern unsigned int ExGetTextureTypeByBits(unsigned int bitsPerPixels);

/**

*/
extern unsigned int ExGetInternalSrgbType(unsigned int internal_format);

/*
	get texture size in bytes
*/
extern unsigned int ExGetTextureDataSize(unsigned int textureid);
/**
    Get texture data by level in unsigned int
*/
extern unsigned int ExGetTextureLevelDatai(unsigned int textureid,unsigned int level,unsigned char** pixeldata);


extern ExTexture* ExCreateTexture(ExTexture* texture, unsigned int  target, int level, int internalFormat, int  width, int height, int border, unsigned int format, unsigned int type, const void *pixels);

extern void ExSubTexture(ExTexture* texture, int level,	int xoffset, int yoffset, int width, int height,int format,int type, const void *pixels );

extern void ExDeleteTexture(ExTexture* texture);

extern void ExGenerateTextureMipmap(ExTexture* texture);

extern void  ExSetTextureAnisotropy(ExTexture* texture,float anisotropy);


//GL_NUM_COMPRESSED_TEXTURE_FORMATS
extern int getNumTextureCompressFormat(void);
extern float ExGetMaxTextureAnisotropy(void);



#ifdef __cplusplus	/* C++ environment	*/
}
#endif 


#endif 

