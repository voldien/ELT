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
	int texture[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	batch->vbo = ExCreateVBO(GL_ARRAY_BUFFER, ExGetPageSize() * sizeof(ExSprite) * 10, GL_DYNAMIC_DRAW);
	batch->num = ExGetPageSize() * 10;
	batch->sprite = malloc(batch->num * sizeof(ExSprite));
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&batch->numMaxTextures);
	batch->numMaxTextures = 16;


	if(!ExLoadShaderv(&batch->shader,EX_VERTEX_SPRITE, EX_FRAGMENT_SPRITE,NULL, NULL, NULL)){
		/*	failure	*/
	}
	glUniform1iv(glGetUniformLocation(batch->shader.program,"texture"),sizeof(texture) / sizeof(texture[0]),texture);

	/*	enable sprite feature	*/
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	return batch;
}
DECLSPEC int ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch){
	glDeleteBuffers(1,&spritebatch->vbo);

	free(spritebatch->sprite);
	return 	!glIsBuffer(spritebatch->vbo);
}

DECLSPEC int ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch,float* camerapos, float scale){
	int i;
	int rect[4];
	spriteBatch->numDraw = 0;
	spriteBatch->numTexture = 0;
	glGetIntegerv(GL_VIEWPORT,rect);
	spriteBatch->width = rect[2];
	spriteBatch->height = rect[3];

	/*	clean texture*/
	memset(spriteBatch->texture,0, sizeof(spriteBatch->texture));

	return TRUE;
}
DECLSPEC int ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch){
	unsigned int i;



	/*	send buffer	*/
	glBindBuffer(GL_ARRAY_BUFFER,spriteBatch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,0, spriteBatch->numDraw * sizeof(ExSprite), spriteBatch->sprite);


	for(i = 0; i < spriteBatch->numTexture; i++){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(spriteBatch->texture[i]->target, spriteBatch->texture[i]->texture);
	}

	glUseProgram(spriteBatch->shader.program);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(ExSprite), NULL);
	glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 3);
	glVertexAttribPointer(2,4,GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 4);
	glVertexAttribPointer(3,1,GL_INT ,  GL_FALSE, sizeof(ExSprite), sizeof(float) * 8);

	glDrawArrays(GL_POINTS,0,spriteBatch->numDraw);



	return 1;
}

DECLSPEC int ELTAPIENTRY ExDrawSprite(ExSpriteBatch* batch, ExTexture* texture,float* position,float* rect, float angle, float depth){
	ExTexture* tex;
	int i;
	int index;


	batch->sprite[batch->numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f;
	batch->sprite[batch->numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f;
	batch->sprite[batch->numDraw].pos[2] = depth;
	if(rect){
		batch->sprite[batch->numDraw].rect[0] = rect[0];
		batch->sprite[batch->numDraw].rect[1] = rect[1];
		batch->sprite[batch->numDraw].rect[2] = rect[2];
		batch->sprite[batch->numDraw].rect[3] = rect[3];
	}
	else{
		batch->sprite[batch->numDraw].rect[0] = 0.0f;
		batch->sprite[batch->numDraw].rect[1] = 0.0f;
		batch->sprite[batch->numDraw].rect[2] = 1.0f;
		batch->sprite[batch->numDraw].rect[3] = 1.0f;
	}
	batch->sprite[batch->numDraw].angle = angle;



	for(i = 0; i < batch->numMaxTextures; i ++){
		if(batch->texture[i] == texture)
			break;
		else{
			if(batch->texture[i] == NULL){
				batch->texture[i] = texture;
				batch->numTexture++;
				break;
			}
		}
		continue;
	}
	batch->sprite[batch->numDraw].texture = i;//texture;


	batch->numDraw++;
	if(batch->numDraw >= batch->num){
		ExEndSpriteBatch(batch);
		ExBeginSpriteBatch(batch,0,0);
	}

	return TRUE;
}
