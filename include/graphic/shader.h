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
extern int ExLoadShader(struct shader_header* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename);
/*
 */
extern int ExLoadShaderv(struct shader_header* shad, const char* cvertex_source,const char* cfragment_source,const char* cgeometry_source,const char* ctess_c_source, const char* ctess_e_source);

extern int ExCompileShaderSource(const char* strPath,char** source, unsigned int flag);
/*
 */
extern int ExCompileShaderSourcev(const char** source, unsigned int flag);

extern int ExShaderCompileLog(unsigned int program,unsigned int shaderflag);

extern int ExGetShaderSource(unsigned int program, unsigned int shader_flag, char** source);
/*
 */
extern int ExGetShaderSourcev(unsigned int program, unsigned int shader_flag, char* source);
/*
 */
extern unsigned int ExGetShaderNumComponent(unsigned int program);
#ifdef __cplusplus
}
#endif 

#endif 
