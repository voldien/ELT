/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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
#include"../elt_def.h"
#include"../ExNT.h"

typedef struct ex_texture {
	unsigned int target; /**/
	unsigned int texture; /**/
	unsigned int width; /**/
	unsigned int height; /**/
	unsigned int layer; /**/
	unsigned int type; /**/
	unsigned int internalformat; /**/
} ExTexture;

#ifdef __cplusplus	/*	C++ environment	*/
extern "C" {
#endif

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC ExTexture* ExCreateTexture(ExTexture* texture,
		unsigned int target, int level, int internalFormat, int width,
		int height, int border, unsigned int format, unsigned int type,
		const void *pixels);

/*
 *
 */
extern ELTDECLSPEC void ExSubTexture(ExTexture* texture, int level, int xoffset,
		int yoffset, int width, int height, int format, int type,
		const void *pixels);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDeleteTexture(ExTexture* texture);

/**
 *	Check if texture is a opengl texture object and is valid.
 *
 *	@Return None zero if true.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExIsTexture(const ExTexture* texture);

/*
 *	return texture internal type in size in bytes
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetTextureTypeSize(
		unsigned int internalformat);

/*
 *	return texture internal type in size in bits
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetTextureTypeBits(
		unsigned int internalformat);

/*
 *	Get texture internal format by number of bits
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetTextureTypeBySize(
		unsigned int bytesperpixel);

/*
 *	Get texture internal format by number of bits
 *	@Return
 */
extern ELTDECLSPEC unsigned int ExGetTextureTypeByBits(
		unsigned int bitsPerPixels);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ExGetinternalSrgbType(
		unsigned int internal_format);

/*
 *	get texture size in bytes
 *	@Return
 */
extern ELTDECLSPEC unsigned int ExGetTextureDataSize(unsigned int textureid);

/*
 *	Get texture data by level in unsigned int
 *	@Return
 */
extern ELTDECLSPEC unsigned int ExGetTextureLevelDatai(unsigned int textureid,
		unsigned int level, unsigned char** pixeldata);

extern ELTDECLSPEC void ELTAPIENTRY ExGenerateTextureMipmap(ExTexture* texture);

extern ELTDECLSPEC void ELTAPIENTRY ExSetTextureAnisotropy(ExTexture* texture,
		float anisotropy);

/*	GL_NUM_COMPRESSED_TEXTURE_FORMATS	*/
extern int getNumTextureCompressFormat(void);
extern float ExGetMaxTextureAnisotropy(void);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif 

