#include"graphic/sprite.h"
#include"graphic/geometry.h"
#include"math/vect.h"
#include"math/matrix.h"


#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
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





ELTDECLSPEC ExSpriteBatch* ExCreateSpriteBatch(ExSpriteBatch* batch){
	int x;
	int texture[256];
	if(!batch)
		return NULL;

	/*	*/	/*	TODO change into opengl core profile by using VAO.	*/
	batch->vbo = ExCreateVBO(GL_ARRAY_BUFFER, ExGetPageSize() * sizeof(ExSprite) * 10, GL_DYNAMIC_DRAW);
	batch->num = ExGetPageSize() * 10;
	batch->sprite = malloc(batch->num * sizeof(ExSprite));
	batch->scale = 1.0f;

	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&batch->numMaxTextures);
	for(x = 0; x < batch->numMaxTextures; x++){
		texture[x] = x;

		continue;
	}


	if(!ExLoadShaderv(&batch->shader, EX_VERTEX_SPRITE, EX_FRAGMENT_SPRITE,NULL, NULL, NULL)){
		/*	failure	*/
		ExReleaseSpriteBatch(batch);
		return NULL;
	}


	batch->locationViewMatrix = glGetUniformLocation(batch->shader.program, "gmat");
	batch->locationScale  = glGetUniformLocation(batch->shader.program, "gscale");
	batch->locationTexture  = glGetUniformLocation(batch->shader.program, "textures");
	glUniform1f(batch->locationScale, batch->scale);


	glUniform1iv(batch->locationTexture, 32, texture);


	/*	enable sprite feature	*/
#if !defined(GL_ES_VERSION_2_0)
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
	glPointParameterf(GL_POINT_SIZE_MIN, 0.0f);
	glPointParameterf(GL_POINT_SIZE_MAX, 2048.0f);
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
#endif
	/*	initialize the batch	*/
	ExBeginSpriteBatch(batch,NULL,1.0f);

	return batch;
}

ELTDECLSPEC int ELTAPIENTRY ExReleaseSpriteBatch(ExSpriteBatch* spritebatch){
	int status;
	glDeleteBuffers(1,&spritebatch->vbo);
	ExDeleteShaderProgram(&spritebatch->shader);
	free(spritebatch->sprite);
	status = !glIsBuffer(spritebatch->vbo);
	memset(spritebatch, 0, sizeof(*spritebatch));
	return status;
}

ELTDECLSPEC int ELTAPIENTRY ExBeginSpriteBatch(ExSpriteBatch* spriteBatch,float* camerapos, float scale){
	int i;
	int rect[4];
	spriteBatch->numDraw = 0;
	spriteBatch->numTexture = 0;
	glGetIntegerv(GL_VIEWPORT,rect);
	spriteBatch->width = rect[2] - rect[0];
	spriteBatch->height = rect[3] - rect[1];
	spriteBatch->scale = scale;

	/*	camera view position*/
	if(camerapos){
		spriteBatch->cameraPos[0] = camerapos[0];
		spriteBatch->cameraPos[1] = camerapos[1];
	}else{
		spriteBatch->cameraPos[0] = 0;
		spriteBatch->cameraPos[1] = 0;
	}
	/*	clean texture*/
	memset(spriteBatch->texture,0, sizeof(spriteBatch->texture));

	return TRUE;
}

ELTDECLSPEC int ELTAPIENTRY ExEndSpriteBatch(ExSpriteBatch* spriteBatch){

	/*	send buffer	*/
	glBindBuffer(GL_ARRAY_BUFFER,spriteBatch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,0, spriteBatch->numDraw * sizeof(ExSprite), spriteBatch->sprite);

	ExDisplaySprite(spriteBatch);

	return 1;
}


ELTDECLSPEC int ELTAPIENTRY ExDrawSprite(ExSpriteBatch* batch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth){
	ExTexture* tex;
	int i;
	int index;
	register unsigned int numDraw;	/*TODO I'm not sure if this will actually improve performance.*/
	numDraw = batch->numDraw;

	batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f  + ( ((float)texture->width  ) / ((float)batch->width) );
	batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f  - ( ((float)texture->height  ) / ((float)batch->height) );

	//batch->sprite[batch->numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f;
	//batch->sprite[batch->numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f;

	//batch->sprite[batch->numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 0.0f;
	//batch->sprite[batch->numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + -1.0f;
	batch->sprite[numDraw].pos[2] = depth;
	if(rect){
		batch->sprite[numDraw].rect[0] = rect[0];
		batch->sprite[numDraw].rect[1] = rect[1];
		batch->sprite[numDraw].rect[2] = rect[2];
		batch->sprite[numDraw].rect[3] = rect[3];
	}
	else{
		batch->sprite[numDraw].rect[0] = 0.0f;
		batch->sprite[numDraw].rect[1] = 0.0f;
		batch->sprite[numDraw].rect[2] = 1.0f;
		batch->sprite[numDraw].rect[3] = 1.0f;
	}
	if(color){
		batch->sprite[numDraw].color[0] = color[0];
		batch->sprite[numDraw].color[1] = color[1];
		batch->sprite[numDraw].color[2] = color[2];
		batch->sprite[numDraw].color[3] = color[3];
	}
	else{
		batch->sprite[numDraw].color[0] = 1.0f;
		batch->sprite[numDraw].color[1] = 1.0f;
		batch->sprite[numDraw].color[2] = 1.0f;
		batch->sprite[numDraw].color[3] = 1.0f;
	}
	batch->sprite[numDraw].angle = angle;
	batch->sprite[numDraw].scale = scale;



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
	batch->sprite[numDraw].texture = i;//texture;


	batch->numDraw++;
	if(batch->numDraw >= batch->num || batch->numTexture >= batch->numMaxTextures){
		ExEndSpriteBatch(batch);
		ExBeginSpriteBatch(batch,0,0);
	}

	return TRUE;
}




ELTDECLSPEC int ELTAPIENTRY ExAddSpriteNormalized(ExSpriteBatch* batch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth){
	ExTexture* tex;
	int i;
	int index;
	unsigned int numDraw = batch->numDraw;

	batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] )  ) - 1.0f;
	batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) ) + 1.0f;

	//batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f;
	//batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f;


	batch->sprite[numDraw].pos[2] = depth;
	if(rect){
		batch->sprite[numDraw].rect[0] = rect[0];
		batch->sprite[numDraw].rect[1] = rect[1];
		batch->sprite[numDraw].rect[2] = rect[2];
		batch->sprite[numDraw].rect[3] = rect[3];
	}
	else{
		batch->sprite[numDraw].rect[0] = 0.0f;
		batch->sprite[numDraw].rect[1] = 0.0f;
		batch->sprite[numDraw].rect[2] = 1.0f;
		batch->sprite[numDraw].rect[3] = 1.0f;
	}
	if(color){
		batch->sprite[numDraw].color[0] = color[0];
		batch->sprite[numDraw].color[1] = color[1];
		batch->sprite[numDraw].color[2] = color[2];
		batch->sprite[numDraw].color[3] = color[3];
	}else{
		batch->sprite[numDraw].color[0] = 1.0f;
		batch->sprite[numDraw].color[1] = 1.0f;
		batch->sprite[numDraw].color[2] = 1.0f;
		batch->sprite[numDraw].color[3] = 1.0f;
	}
	batch->sprite[numDraw].angle = angle;
	batch->sprite[numDraw].scale = scale;

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
	batch->sprite[numDraw].texture = i;//texture;


	glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,numDraw * sizeof(ExSprite),sizeof(ExSprite) , &batch->sprite[numDraw]);
	batch->numDraw++;

	return TRUE;
}


ELTDECLSPEC int ELTAPIENTRY ExAddSprite(ExSpriteBatch* batch,ExTexture* texture,float* position,float* rect,float* color, float scale, float angle, float depth){
	ExTexture* tex;
	int i;
	int index;
	unsigned int numDraw = batch->numDraw;

	batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f  + ( ((float)texture->width  ) / ((float)batch->width) );
	batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f  - ( ((float)texture->height  ) / ((float)batch->height) );

	//batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f;
	//batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f;


	batch->sprite[numDraw].pos[2] = depth;
	if(rect){
		batch->sprite[numDraw].rect[0] = rect[0];
		batch->sprite[numDraw].rect[1] = rect[1];
		batch->sprite[numDraw].rect[2] = rect[2];
		batch->sprite[numDraw].rect[3] = rect[3];
	}
	else{
		batch->sprite[numDraw].rect[0] = 0.0f;
		batch->sprite[numDraw].rect[1] = 0.0f;
		batch->sprite[numDraw].rect[2] = 1.0f;
		batch->sprite[numDraw].rect[3] = 1.0f;
	}
	if(color){
		batch->sprite[numDraw].color[0] = color[0];
		batch->sprite[numDraw].color[1] = color[1];
		batch->sprite[numDraw].color[2] = color[2];
		batch->sprite[numDraw].color[3] = color[3];
	}else{
		batch->sprite[numDraw].color[0] = 1.0f;
		batch->sprite[numDraw].color[1] = 1.0f;
		batch->sprite[numDraw].color[2] = 1.0f;
		batch->sprite[numDraw].color[3] = 1.0f;
	}
	batch->sprite[numDraw].angle = angle;
	batch->sprite[numDraw].scale = scale;

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
	batch->sprite[numDraw].texture = i;//texture;


	glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,numDraw * sizeof(ExSprite),sizeof(ExSprite) , &batch->sprite[numDraw]);
	batch->numDraw++;

	return TRUE;
}


ELTDECLSPEC int ELTAPIENTRY ExRemoveSprite(ExSpriteBatch* spritebatch, int index){
	/*	set last element in the index that going to be removed.*/
	memcpy(&spritebatch->sprite[index],&spritebatch->sprite[spritebatch->numDraw],sizeof(ExSprite));
	spritebatch->numDraw--;

	return TRUE;
}



ELTDECLSPEC inline  int ELTAPIENTRY ExDisplaySprite(ExSpriteBatch* spriteBatch){
	int i;
	float matscale[3][3];
	float rotmat[3][3];
	float tranmat[3][3];

	glBindBuffer(GL_ARRAY_BUFFER,spriteBatch->vbo);

	for(i = 0; i < spriteBatch->numTexture; i++){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(spriteBatch->texture[i]->target, spriteBatch->texture[i]->texture);
	}

	glUseProgram(spriteBatch->shader.program);



	/*	update view matrix and global scale*/	/*TODO*/
	mat3x3_translation(tranmat,spriteBatch->cameraPos[0],spriteBatch->cameraPos[1]);
	mat3x3_scale(matscale,spriteBatch->scale,spriteBatch->scale);
	mat3x3_multi_mat3x3(matscale,tranmat,spriteBatch->viewmatrix);

	/**/
	glUniform1fv(spriteBatch->locationScale,1, &spriteBatch->scale);
	glUniformMatrix3fv(spriteBatch->locationViewMatrix,1,GL_FALSE,spriteBatch->viewmatrix);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ExSprite), NULL);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 3);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 4);
	glVertexAttribPointer(3, 1, GL_INT,   GL_FALSE, sizeof(ExSprite), sizeof(float) * (3 + 4 + 1));
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * (3 + 4 + 1 + 1));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * (3 + 4 + 1 + 1 + 1));

	glDrawArrays(GL_POINTS, 0, spriteBatch->numDraw);

	return TRUE;
}
