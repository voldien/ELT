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
#include<stdio.h>
typedef struct shader_header{
	unsigned int ver;
	unsigned int fra;
	unsigned int geo;
	unsigned int tesc;
	unsigned int tese;
	unsigned int program;
	unsigned int flag;
}ShaderHeader;
#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif 
/*
 */
extern int ExGetShaderProgramSize(unsigned int program);
/*
 */
extern int ExGetShaderSourceSize(unsigned int shader);
/*
 */
extern int ExLoadShader(ShaderHeader* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename);
/*
 */
extern int ExLoadShaderv(ShaderHeader* shad, const char* cvertexSource,const char* cfragmentSource,const char* cgeometry_source,const char* ctess_c_source, const char* ctess_e_source);

extern int ExCompileShaderSource(const char* strPath,char** source, unsigned int flag);

/*	*/
extern int ExCompileShaderSourcev(const char** source, unsigned int flag);

extern int ExShaderCompileLog(unsigned int program,unsigned int shaderflag);

extern int ExGetShaderSource(unsigned int program, unsigned int shader_flag, char** source);

/* */
extern int ExGetShaderSourcev(unsigned int program, unsigned int shader_flag, char* source);

/*	*/
extern unsigned int ExGetShaderNumComponent(unsigned int program);
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
"#ifdef GL_ES\n"									\
"precision mediump float;\n"						\
"#endif\n"											\
"layout(location = 0) in vec3 vertex;\n"			\
"layout(location = 1) in float angle;\n"			\
"layout(location = 2) in vec4 rect;\n"				\
"layout(location = 3) in int tex;\n"				\
"uniform sampler2D texture[16];\n"					\
"out float fangle;\n"								\
"out vec4 frect;\n"									\
"out mat2 coord;\n"									\
"out int ftexture;\n"								\
"void main(void){\n"								\
"	gl_PointSize = max(textureSize(texture[0],0).x,"	\
"textureSize(texture[0],0).y);\n"						\
"	gl_Position = vec4(vertex,1.0);\n"				\
"	fangle = angle;\n"								\
"	frect = rect;\n"								\
"	ftexture = tex;\n"								\
"}\n"




#define EX_FRAGMENT_SPRITE ""								\
"#version 330\n"											\
"#ifdef GL_ES\n"											\
"precision mediump float;\n"								\
"#endif\n"													\
"layout(location = 0) out vec4 fragColor;\n"				\
"uniform sampler2D texture[16];\n"							\
"in vec4 frect;\n"											\
"in float fangle;\n"										\
"in int ftexture;\n"										\
"void main(void){\n"										\
"	float sin_theta = sin(fangle + 3.14);\n"						\
"	float cos_theta = cos(fangle + 3.14);\n"						\
"	mat2 rotation_matrix = mat2(cos_theta, sin_theta,\n"			\
"-sin_theta, cos_theta);\n"											\
"	fragColor = texture2D(texture[0],(rotation_matrix * ((gl_PointCoord - vec2(0.5) - frect.xy) + vec2(0.5))) * frect.zw);\n"		\
"}\n"														\


#endif 
