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
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif



ExSpriteBatch* ExCreateSpriteBatch(ExSpriteBatch* spritebatch){
	int x;
	int texture[512];
	if(!spritebatch)
		return NULL;

	/*	*/
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &spritebatch->numMaxTextures);



	/*	*/
	ExGenVertexArrays(1,&spritebatch->vao);
	glBindVertexArray(spritebatch->vao);
	ExGenBuffers(1, &spritebatch->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, spritebatch->vbo);

	/**/
	spritebatch->scale = 1.0f;
	spritebatch->num = ExGetPageSize() * 10;
	spritebatch->sprite = NULL;
	ExSpriteBatchAllocateSprite(spritebatch, spritebatch->num);


	/**/
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ExSprite), NULL);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ExSprite), (const void*)(sizeof(float) * 3 ));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 3 + sizeof(float) * 1);
	glVertexAttribPointer(3, 1, GL_INT,   GL_FALSE, sizeof(ExSprite), (const void*)( sizeof(float) * 3 + sizeof(float) + sizeof(float) * 4 ) );
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * 3 + sizeof(float) * 1 + sizeof(float) * 4 + sizeof(int));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(ExSprite), sizeof(float) * (3 + 4 + 1 + 1 + 1));

	glBindVertexArray(0);

	/*	Load sprite shader.	*/
	if(!ExLoadShaderv(&spritebatch->spriteShader, EX_VERTEX_SPRITE, EX_FRAGMENT_SPRITE, NULL, NULL, NULL)){
		/*	failure	*/
		ExReleaseSpriteBatch(spritebatch);
		return NULL;
	}

	/*	cache sprite uniform location.	*/
	spritebatch->locationViewMatrix = glGetUniformLocation(spritebatch->spriteShader.program, "gmat");
	spritebatch->locationScale  = glGetUniformLocation(spritebatch->spriteShader.program, "gscale");
	spritebatch->locationTexture  = glGetUniformLocation(spritebatch->spriteShader.program, "textures");

	/**/
	glUseProgram(spritebatch->spriteShader.program);
	glUniform1f(spritebatch->locationScale, spritebatch->scale);
	for(x = 0; x < spritebatch->numMaxTextures; x++){
		texture[x] = x;
	}
	glUniform1iv(spritebatch->locationTexture, 32, &texture[0]);
	glUseProgram(0);


	/*	enable sprite feature	*/
#if !defined(GL_ES_VERSION_2_0)
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
	//glPointParameterf(GL_POINT_SIZE_MIN, 0.0f);
	//glPointParameterf(GL_POINT_SIZE_MAX, 2048.0f);
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
#endif


	/*	initialize the batch	*/
	ExBeginSpriteBatch(spritebatch, NULL, 1.0f);

	return spritebatch;
}

int ExReleaseSpriteBatch(ExSpriteBatch* spritebatch){
	int status;

	glDeleteBuffers(1, &spritebatch->vbo);
	ExDeleteShaderProgram(&spritebatch->spriteShader);
	free(spritebatch->sprite);
	spritebatch->sprite = NULL;
	status = !glIsBuffer(spritebatch->vbo);
	memset(spritebatch, 0, sizeof(*spritebatch));
	return status;
}

void ExSpriteBatchAllocateSprite(ExSpriteBatch* spritebatch, unsigned int num){
	//ExFlushSpriteBatch(spritebatch);
	if(spritebatch == NULL)
		return;
	if(glIsBuffer(spritebatch->vbo) == 0){
		ExGenBuffers(1, &spritebatch->vbo);
		glBindBuffer(spritebatch->vbo);
	}
	/**/
	spritebatch->sprite = realloc(spritebatch->sprite, num * sizeof(ExSprite));
	spritebatch->num = num;
	ExSetBufferSize(GL_ARRAY_BUFFER, spritebatch->vbo, spritebatch->num * sizeof(ExSprite), GL_DYNAMIC_DRAW);
}

void ExBeginSpriteBatch(ExSpriteBatch* spriteBatch, const float* camerapos, float scale){
	int i;
	int rect[4];
	spriteBatch->numDraw = 0;
	spriteBatch->numTexture = 0;

	glGetIntegerv(GL_VIEWPORT, rect);
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
	memset(spriteBatch->texture, 0, sizeof(spriteBatch->texture));
}

void ExEndSpriteBatch(ExSpriteBatch* spriteBatch){

	/*	send buffer	*/
	glBindBuffer(GL_ARRAY_BUFFER,spriteBatch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,0, spriteBatch->numDraw * sizeof(ExSprite), spriteBatch->sprite);

	ExDisplaySprite(spriteBatch);

}


void ExDrawSprite(ExSpriteBatch* batch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth){
	ExTexture* tex;
	int i;
	int index;
	register unsigned int numDraw;
	numDraw = batch->numDraw;

	/*	screen coordinate-	*/
	batch->sprite[numDraw].pos[0] = 2.0f * ( (position[0] ) / (float)batch->width) - 1.0f  + ( ((float)texture->width  ) / ((float)batch->width) );
	batch->sprite[numDraw].pos[1] = 2.0f * ( (-position[1] ) / (float)batch->height) + 1.0f  - ( ((float)texture->height  ) / ((float)batch->height) );

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
		if(batch->texture[i] == texture->texture)
			break;
		else{
			if(batch->texture[i] == NULL){
				batch->texture[i] = texture->texture;
				batch->numTexture++;
				break;
			}
		}
	}

	/*	sprite texture index.	*/
	batch->sprite[numDraw].texture = (GLint)i;

	/*	*/
	batch->numDraw++;
	if(batch->numDraw >= batch->num || batch->numTexture >= batch->numMaxTextures){
		ExEndSpriteBatch(batch);
		ExBeginSpriteBatch(batch,0,0);
	}
}

void ExAddSpriteNormalized(ExSpriteBatch* batch,ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth){
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
		if(batch->texture[i] == texture->texture)
			break;
		else{
			if(batch->texture[i] == NULL){
				batch->texture[i] = texture->texture;
				batch->numTexture++;
				break;
			}
		}

	}
	batch->sprite[numDraw].texture = (GLint)i;//texture;


	glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,numDraw * sizeof(ExSprite),sizeof(ExSprite) , &batch->sprite[numDraw]);
	batch->numDraw++;

}

int ExAddSprite(ExSpriteBatch* batch, ExTexture* texture, const float* position, const float* rect, const float* color, float scale, float angle, float depth){
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
		if(batch->texture[i] == texture->texture)
			break;
		else{
			if(batch->texture[i] == NULL){
				batch->texture[i] = texture->texture;
				batch->numTexture++;
				break;
			}
		}
	}
	batch->sprite[numDraw].texture = (GLint)i;//texture;


	glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
	glBufferSubData(GL_ARRAY_BUFFER,numDraw * sizeof(ExSprite), sizeof(ExSprite) , &batch->sprite[numDraw]);
	batch->numDraw++;

	return TRUE;
}

void ExRemoveSprite(ExSpriteBatch* spritebatch, int index){

	/*	set last element in the index that going to be removed.*/
	if(index < spritebatch->numDraw){
		memcpy(&spritebatch->sprite[index], &spritebatch->sprite[spritebatch->numDraw - 1], sizeof(ExSprite));
		spritebatch->numDraw--;

	}
}

inline void ExDisplaySprite(ExSpriteBatch* spriteBatch){
	int i;
	exvec3x3_t matscale;
	exvec3x3_t rotmat;
	exvec3x3_t tranmat;

	/*	*/
	for(i = 0; i < spriteBatch->numTexture; i++){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, spriteBatch->texture[i]);
	}

	/*	*/
	glUseProgram(spriteBatch->spriteShader.program);


	/*	update view matrix and global scale*/	/*TODO*/
	mat3x3_translation(tranmat, spriteBatch->cameraPos[0], spriteBatch->cameraPos[1]);
	mat3x3_scale(matscale, spriteBatch->scale, spriteBatch->scale);
	mat3x3_multi_mat3x3(matscale, tranmat, spriteBatch->viewmatrix);


	/*		*/
	glUniform1fv(spriteBatch->locationScale, 1, &spriteBatch->scale);
	glUniformMatrix3fv(spriteBatch->locationViewMatrix, 1, GL_FALSE, &spriteBatch->viewmatrix[0][0]);


	/*	draw sprites.	*/
	glBindVertexArray(spriteBatch->vao);
	glDrawArrays(GL_POINTS, 0, spriteBatch->numDraw);
	//glDrawArrays(GL_POINTS, (spriteBatch->num -spriteBatch->numlabelDraw) , spriteBatch->numlabelDraw);	/*	labels.	*/
	glBindVertexArray(0);
}

