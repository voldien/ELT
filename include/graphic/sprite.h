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
#ifndef _ELT_SPRITE_H_ 
#define _ELT_SPRITE_H_ 1
#include"texture.h"
#include"shader.h"
#include"font.h"
#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

/*
 *
 */
typedef struct ex_srpite{
	float pos[3];					/*	position.	*/
	float angle;					/*	angle.	*/
	float rect[4];					/*	*/
	int texture;					/*	texture index.*/
	float scale;					/*	uniform scale.	*/
	float color[4];					/*	color.	*/
}ExSprite;

/*
 *
 */
typedef struct sprite_batch{
	/*
	 *	number of sprite allocated.
	 */
	unsigned int num;					/**/
	unsigned int numDraw;				/**/
	/*unsigned int numlabelDraw;*/		/**/
	unsigned int vbo;					/**/
	unsigned int vao;					/**/

	/**/
	ExShader spriteShader;				/**/
	//ExShader fontshader;


	/*	Number of associated textures.	*/
	int numTexture;
	/*	Max number of texture units.	*/
	int numMaxTextures;


	/*	TODO add texture target. make texture to pointer	*/
	int texture[32];					/**/
	//int* target[32];					/**/
	ExSprite* sprite;					/**/



	float scale;						/**/
	float cameraPos[2];					/**/
	float rotation;						/**/


	/*	*/
	unsigned int width;					/**/
	unsigned int height;				/**/


	/*	view matrix.	*/
	float viewmatrix[3][3];				/**/


	/*	cached uniform location.	*/
	struct{
		/*	*/
		int locationViewMatrix;				/**/
		int locationScale;					/**/
		int locationTexture;				/**/
	};
}ExSpriteBatch;


/**
 *	Create
 *
 *	@Return
 */
extern ELTDECLSPEC ExSpriteBatch* ELTAPIENTRY ExCreateSpriteBatch(ExSpriteBatch* spriteBatch);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSpriteBatchAllocateSprite(ExSpriteBatch* spritebatch, unsigned int num);


//extern ELTDECLSPEC int ELTAPIENTRY ExGetSpriteBatchUniform(ExSpriteBatch* spritebatch);


/**
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch, const float* camerapos, float scale);

/*
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch);


/*
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDrawSprite(ExSpriteBatch* spritebatch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth);

/*
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExDrawSpriteNormalize(ExSpriteBatch* spritebatch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth);

/**/
extern ELTDECLSPEC int ELTAPIENTRY ExDrawSpriteLabel(ExSpriteBatch* spritebatch, ExFont* font, float* position, float* rect, float* color, float scale, float angle, float depth);


/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExAddSpriteNormalized(ExSpriteBatch* spritebatch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth);

/*
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExAddSprite(ExSpriteBatch* spritebatch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth);



/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExRemoveSprite(ExSpriteBatch* spritebatch, int index);

/*
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExFlushSpriteBatch(ExSpriteBatch* spritebatch);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDisplaySprite(ExSpriteBatch* spritebatch);


#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
