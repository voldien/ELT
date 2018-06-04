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
#ifndef _ELT_SHADER_H_
#define _ELT_SHADER_H_ 1
#include"./../elt_def.h"

/*
 *
 */
typedef struct ex_shader {
	unsigned int ver; /*	vertex shader.	*/
	unsigned int fra; /*	fragment shader.	*/
	unsigned int geo; /*	geometry shader.	*/
	unsigned int tesc; /*	tessellation control shader.	*/
	unsigned int tese; /*	tessellation evaluation shader.	*/
	unsigned int program; /*	shader program.	*/
	unsigned int flag; /**/
} ExShader;

#ifdef __cplusplus	/*	C++ environment	*/
extern "C" {
#endif

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderProgramSize(unsigned int program);

/**
 *
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
extern ELTDECLSPEC int ELTAPIENTRY ExLoadShader(ExShader* shad,
		const char* cvertexfilename, const char* cfragmentfilename,
		const char* cgeometryfilename, const char* ctesscfilename,
		const char* ctessefilename);

/**
 *	Load shader
 *
 *	@Return 0 if failed.
 */
extern ELTDECLSPEC int ELTAPIENTRY ExLoadShaderv(ExShader* shad,
		const char* cvertexSource, const char* cfragmentSource,
		const char* cgeometry_source, const char* ctess_c_source,
		const char* ctess_e_source);

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

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExCompileShaderSource(const char* strPath, char** source,
		unsigned int flag);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExCompileShaderSourcev(const char** source,
		unsigned int flag);

/**
 *
 */
extern ELTDECLSPEC int ExValidateShader(unsigned int program);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExShaderCompileLog(unsigned int program,
		unsigned int shaderflag);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExShaderCompileLogv(unsigned int program,
		unsigned int shaderflag, char* log);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderSource(unsigned int shader, char** source);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ExGetShaderSourcev(unsigned int shader, char* source);

/**
 *
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
"ivec2 getTexture(const in int index){\n"				\
"	switch(index){\n"				\
"		case 0:\n"				\
"		return textureSize(textures[0], 0);\n"				\
"		case 1:\n"				\
"		return textureSize(textures[1], 0);\n"				\
"		case 2:\n"				\
"		return textureSize(textures[2], 0);\n"				\
"		case 3:\n"				\
"		return textureSize(textures[3], 0);\n"				\
"		case 4:\n"				\
"		return textureSize(textures[4], 0);\n"				\
"		case 5:\n"				\
"		return textureSize(textures[5], 0);\n"				\
"		case 6:\n"				\
"		return textureSize(textures[6], 0);\n"				\
"		case 7:\n"				\
"		return textureSize(textures[7], 0);\n"				\
"		case 8:\n"				\
"		return textureSize(textures[8], 0);\n"				\
"		case 9:\n"				\
"		return textureSize(textures[9], 0);\n"				\
"		case 10:\n"				\
"		return textureSize(textures[10], 0);\n"				\
"		case 11:\n"				\
"		return textureSize(textures[11], 0);\n"				\
"		default:\n"				\
"		return textureSize(textures[0], 0);\n"				\
"	}\n"				\
"}\n"				\
"void main(void){\n"												\
"	float sin_theta = sin(angle);\n"								\
"	float cos_theta = cos(angle);\n"								\
"	coord = mat2(cos_theta, sin_theta,\n"							\
"-sin_theta, cos_theta);\n"											\
"	vec2 uv = coord * vec2(float(getTexture(tex).x) * rect.z * scale, float(getTexture(tex).y) * rect.w * scale );\n"					\
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
"uniform sampler2D textures[64];\n"									\
"smooth in vec4 frect;\n"											\
"smooth in float fangle;\n"										\
"flat in int ftexture;\n"										\
"smooth in mat2 coord;\n"											\
"smooth in vec4 fcolor;\n"											\
"ivec2 getTexture(const in int index){\n"				\
"	switch(index){\n"				\
"		case 0:\n"				\
"		return textureSize(textures[0], 0);\n"				\
"		case 1:\n"				\
"		return textureSize(textures[1], 0);\n"				\
"		case 2:\n"				\
"		return textureSize(textures[2], 0);\n"				\
"		case 3:\n"				\
"		return textureSize(textures[3], 0);\n"				\
"		case 4:\n"				\
"		return textureSize(textures[4], 0);\n"				\
"		case 5:\n"				\
"		return textureSize(textures[5], 0);\n"				\
"		case 6:\n"				\
"		return textureSize(textures[6], 0);\n"				\
"		case 7:\n"				\
"		return textureSize(textures[7], 0);\n"				\
"		case 8:\n"				\
"		return textureSize(textures[8], 0);\n"				\
"		case 9:\n"				\
"		return textureSize(textures[9], 0);\n"				\
"		case 10:\n"				\
"		return textureSize(textures[10], 0);\n"				\
"		case 11:\n"				\
"		return textureSize(textures[11], 0);\n"				\
"		default:\n"				\
"		return textureSize(textures[0], 0);\n"				\
"	}\n"				\
"}\n"				\
"vec4 gettextfrag(const in int index, const in vec2 uv){\n"	\
"	switch(index){\n"										\
"	case 0:\n"												\
"		return texture2D(textures[0], uv);\n"				\
"	case 1:\n"												\
"		return texture2D(textures[1], uv);\n"				\
"	case 2:\n"												\
"		return texture2D(textures[2], uv);\n"				\
"	default:\n"												\
"		return vec4(0.0);\n"								\
"	}\n"													\
"}\n"														\
"void main(void){\n"										\
"	float texwidth = float(getTexture(ftexture).x);\n"			\
"	float texheight = float(getTexture(ftexture).y);\n"			\
"	vec2 fragscale = vec2(clamp( texheight / texwidth ,1.0,10.0 ) , clamp( texwidth / texheight ,1.0,10.0) );\n"														\
"	fragColor = gettextfrag(ftexture, frect.xy  + ((vec2(1.0) - frect.zw) / 2) * vec2(-1,1)  + vec2(0.5) + coord * ((gl_PointCoord - vec2(0.5) ) * frect.zw * fragscale.xy)) * fcolor;\n"		\
"}\n"														\


#endif 
