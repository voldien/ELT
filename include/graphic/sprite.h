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
	float pos[3];
	float angle;
	float rect[4];
}ExSprite;

typedef struct sprite_batch{
	unsigned int num;
	unsigned int numDraw;
	unsigned int vbo;
	ShaderHeader shader;

}ExSpriteBatch;

extern DECLSPEC ExSpriteBatch* ELTAPIENTRY ExCreateSpriteBatch(ExSpriteBatch* spriteBatch);
extern DECLSPEC int	ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch);

extern DECLSPEC int ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch);
extern DECLSPEC int ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch);
extern DECLSPEC int ELTAPIENTRY ExDrawSprite(ExSpriteBatch* spritebatch,ExTexture* texture,float* position,float depth);



#ifdef __cplusplus	/* C++ environment	*/
}
#endif 


#endif 

