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
#ifndef _ELT_SHADER_H_
#define _ELT_SHADER_H_ 1
#include"./../elt_def.h"


/*
 *
 */
typedef struct ex_shader{
	unsigned int ver;		/**/
	unsigned int fra;		/**/
	unsigned int geo;		/**/
	unsigned int tesc;		/**/
	unsigned int tese;		/**/
	unsigned int program;	/**/
	unsigned int flag;		/**/
}ExShader,ShaderHeaderr;

#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

/**
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderProgramSize(unsigned int program);

/**
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderSourceSize(unsigned int shader);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExSetProgramShader(int program, int shader);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExLoadShader(ExShader* shad, const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename);

/*
 *
 *	@Return 0 if failed.
 */
extern ELTDECLSPEC int ELTAPIENTRY ExLoadShaderv(ExShader* shad, const char* cvertexSource, const char* cfragmentSource, const char* cgeometry_source, const char* ctess_c_source, const char* ctess_e_source);

/**
 *
 * 	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExIsShader(const ExShader* shader);

/**
 *
 *	@Return 0 if failed
 */
extern ELTDECLSPEC int ExDeleteShaderProgram(ExShader* header);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ExCompileShaderSource(const char* strPath, char** source, unsigned int flag);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ExCompileShaderSourcev(const char** source, unsigned int flag);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExShaderCompileLog(unsigned int program,unsigned int shaderflag);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExShaderCompileLogv(unsigned int program,unsigned int shaderflag, char* log);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderSource(unsigned int shader, char** source);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderSourcev(unsigned int shader, char* source);

/*
 *	@Return
 */
extern ELTDECLSPEC unsigned int ExGetShaderNumComponent(unsigned int program);

#ifdef __cplusplus
}
#endif 


/*	opengl shader	*/

#define EX_VERTEX_UNLIT	""		\


/*



 */

#define EX_FRAGMENT_UNLIT ""	\

/*



 */

#define EX_VERTEX_DIFFUSE	""
/*
#version 330

#ifdef GL_ES
precision mediump float;
#endif
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 ModelViewProjection;


out vec2 UV;


void main(void){
	glPosition = ModelViewProjection * vec4(vertex);
	UV = uv;
}

 */

#define EX_FRAGMENT_DIFFUSE	""
/*
#version 330

#ifdef GL_ES
precision mediump float;
#endif
layout(location = 0) out vec4 fragColor;

uniform vec4 color;
uniform sampler diffuseTexture;

int vec2 UV;
void main(void){
	fragColor = texture(diffuseTexture, UV) * color;

}

 */


#define EX_VERTEX_TRANSPARENT ""

/*

 */
#define EX_FRAGMENT_TRANSPARENT ""
/*

 */


#define EX_VERTEX_SPRITE	""						\
"#version 330\n"									\
"#extension GL_EXT_gpu_shader4 : enable\n"			\
"#ifdef GL_ES\n"									\
"precision mediump float;\n"						\
"#endif\n"											\
"layout(location = 0) in vec3 vertex;\n"			\
"layout(location = 1) in float angle;\n"			\
"layout(location = 2) in vec4 rect;\n"								\
"layout(location = 3) in int tex;\n"								\
"layout(location = 4) in float scale;\n"								\
"layout(location = 5) in vec4 color;\n"								\
"uniform mat3 gmat;\n"												\
"uniform float gscale;\n"										\
"uniform sampler2D textures[64];\n"									\
"smooth out float fangle;\n"												\
"smooth out vec4 frect;\n"													\
"smooth out mat2 coord;\n"													\
"flat out int ftexture;\n"												\
"smooth out vec4 fcolor;\n"												\
"sampler2D getTexture(const in int index){\n"				\
"	switch(index){\n"				\
"		case 0:\n"				\
"		return textures[0];\n"				\
"		case 1:\n"				\
"		return textures[1];\n"				\
"		case 2:\n"				\
"		return textures[2];\n"				\
"		case 3:\n"				\
"		return textures[3];\n"				\
"		case 4:\n"				\
"		return textures[4];\n"				\
"		case 5:\n"				\
"		return textures[5];\n"				\
"		case 6:\n"				\
"		return textures[6];\n"				\
"		case 7:\n"				\
"		return textures[7];\n"				\
"		case 8:\n"				\
"		return textures[8];\n"				\
"		case 9:\n"				\
"		return textures[9];\n"				\
"		case 10:\n"				\
"		return textures[10];\n"				\
"		case 11:\n"				\
"		return textures[11];\n"				\
"		default:\n"				\
"		return textures[0];\n"				\
"	}\n"				\
"}\n"				\
"void main(void){\n"												\
"	float sin_theta = sin(angle);\n"								\
"	float cos_theta = cos(angle);\n"								\
"	coord = mat2(cos_theta, sin_theta,\n"							\
"-sin_theta, cos_theta);\n"											\
"	vec2 uv = coord * vec2(float(textureSize(getTexture(tex),0).x) * rect.z * scale,float(textureSize2D(getTexture(tex),0).y) * rect.w * scale );\n"					\
"	gl_PointSize = float(max(abs(uv.x * sin(angle)) + abs(uv.y * cos(angle) ),"	\
"abs(uv.x * cos(angle)) + abs(uv.y * sin(angle)) )); \n"						\
"	gl_PointSize *= gscale;\n"													\
"	gl_Position = vec4( (gmat * vec3(vertex.xy,1.0)).xy, vertex.z ,1.0f);\n"							\
"	fangle = angle;\n"								\
"	frect = rect;\n"								\
"	ftexture = tex;\n"								\
"	fcolor = color;\n"								\
"}\n"




#define EX_FRAGMENT_SPRITE ""								\
"#version 330\n"											\
"#ifdef GL_ES\n"											\
"precision mediump float;\n"								\
"#endif\n"													\
"layout(location = 0) out vec4 fragColor;\n"				\
"uniform sampler2D textures[64];\n"							\
"smooth in vec4 frect;\n"											\
"smooth in float fangle;\n"										\
"flat in int ftexture;\n"										\
"smooth in mat2 coord;\n"											\
"smooth in vec4 fcolor;\n"											\
"sampler2D getTexture(in int texIndex){\n"				\
"	switch(texIndex){\n"				\
"		case 0:\n"				\
"		return textures[0];\n"				\
"		case 1:\n"				\
"		return textures[1];\n"				\
"		case 2:\n"				\
"		return textures[2];\n"				\
"		case 3:\n"				\
"		return textures[3];\n"				\
"		case 4:\n"				\
"		return textures[4];\n"				\
"		case 5:\n"				\
"		return textures[5];\n"				\
"		case 6:\n"				\
"		return textures[6];\n"				\
"		case 7:\n"				\
"		return textures[7];\n"				\
"		case 8:\n"				\
"		return textures[8];\n"				\
"		case 9:\n"				\
"		return textures[9];\n"				\
"		case 10:\n"				\
"		return textures[10];\n"				\
"		case 11:\n"				\
"		return textures[11];\n"				\
"		default:\n"				\
"		return textures[0];\n"				\
"	}\n"				\
"}\n"				\
"void main(void){\n"										\
"	float texwidth = float(textureSize(getTexture(ftexture),0).x);\n"			\
"	float texheight = float(textureSize(getTexture(ftexture),0).y);\n"			\
"	vec2 fragscale = vec2(clamp( texheight / texwidth ,1.0,10.0 ) , clamp( texwidth / texheight ,1.0,10.0) );\n"														\
"	fragColor = texture2D(getTexture(ftexture), frect.xy  + ((vec2(1.0) - frect.zw) / 2) * vec2(-1,1)  + vec2(0.5) + coord * ((gl_PointCoord - vec2(0.5) ) * frect.zw * fragscale.xy)) * fcolor;\n"		\
"	//fragColor.rg += (frect.xy  + vec2(0.5) + coord * ((gl_PointCoord - vec2(0.5) ) * frect.zw * fragscale.xy)).xy;\n"		\
"}\n"														\

#endif 
