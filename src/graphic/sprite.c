#include"graphic/sprite.h"
#include"graphic/geometry.h"
#include"math/vect.h"

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

DECLSPEC ExSpriteBatch* ExCreateSpriteBatch(ExSpriteBatch* batch){
	batch->vbo = ExCreateVBO(GL_ARRAY_BUFFER, ExGetPageSize() * sizeof(float), GL_DYNAMIC_DRAW);
	batch->num = ExGetPageSize();

	if(!ExLoadShaderv(&batch->shader,EX_VERTEX_SPRITE, EX_FRAGMENT_SPRITE,NULL, NULL, NULL)){

	}

	return batch;
}
DECLSPEC int ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch){
	glDeleteBuffers(1,&spritebatch->vbo);

	return 	glIsBuffer(spritebatch->vbo);
}

DECLSPEC int ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch){

}
DECLSPEC int ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch){

	glUseProgram(spriteBatch->shader.program);

	glBindBuffer(GL_ARRAY_BUFFER, spriteBatch->vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(ExSprite),NULL);
	glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 3);
	glVertexAttribPointer(2,3,GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 4);

	glDrawArrays(GL_POINTS,0,spriteBatch->numDraw);

}


DECLSPEC int ELTAPIENTRY ExDrawSprite(ExSpriteBatch* sprite, ExTexture* texture,float* position,float depth){


	return TRUE;
}
