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
#include"../EngineAssembly.h"
#include"texture.h"
#include"shader.h"
#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

typedef struct ex_srpite{
	float pos[3];				/**/
	float angle;				/**/
	float rect[4];				/**/
	int texture;				/**/
	float scale;				/**/
	float color[4];				/**/
}ExSprite;

typedef struct sprite_batch{
	unsigned int num;					/**/
	unsigned int numDraw;				/**/
	unsigned int vbo;					/**/

	ExShader shader;					/**/

	int numTexture;
	int numMaxTextures;

	ExTexture* texture[32];
	ExSprite* sprite;

	float scale;
	float cameraPos[2];
	float rotation;

	unsigned int width;
	unsigned int height;

	float viewmatrix[3][3];
	int locationViewMatrix;
	int locationScale;
	int locationTexture;

}ExSpriteBatch;


/*
 *	Create
 */
extern DECLSPEC ExSpriteBatch* ELTAPIENTRY ExCreateSpriteBatch(ExSpriteBatch* spriteBatch);

/*
 *
 */
extern DECLSPEC int	ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch);



//extern DECLSPEC int ELTAPIENTRY ExGetSpriteBatchUniform(ExSpriteBatch* spritebatch);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch,float* camerapos, float scale);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch);

/**/
extern DECLSPEC int ELTAPIENTRY ExDrawSprite(ExSpriteBatch* spritebatch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth);

/**/
extern DECLSPEC int ELTAPIENTRY ExDrawSpriteNormalize(ExSpriteBatch* spritebatch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth);


/**/
extern DECLSPEC int ELTAPIENTRY ExAddSpriteNormalized(ExSpriteBatch* spritebatch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth);

/**/
extern DECLSPEC int ELTAPIENTRY ExAddSprite(ExSpriteBatch* spritebatch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth);

/**/
extern DECLSPEC int ELTAPIENTRY ExRemoveSprite(ExSpriteBatch* spritebatch,int index);

/**/
extern DECLSPEC int ELTAPIENTRY ExFlushSpriteBatch(ExSpriteBatch* spritebatch);

/*	*/
extern DECLSPEC int ELTAPIENTRY ExDisplaySprite(ExSpriteBatch* spritebatch);


#ifdef __cplusplus	/* C++ environment	*/
}
#endif 


#endif 

