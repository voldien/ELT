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
#ifndef _ELT_GEOMETRY_H_ 
#define _ELT_GEOMETRY_H_ 1
#include"./../elt_def.h"

/*TODO add some common buffer structure*/
typedef struct ex_vbo{

}ExVBO;


typedef struct ex_uniform_buffer{

}ExUniformBuffer;


#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif 


/*	TODO conclude if function shall follow same naming conventions as opengl or use our own.*/
extern ELTDECLSPEC void ELTAPIENTRY ExGenBuffers(int n, unsigned int* buffers);

/*
 *
 */
extern ELTDECLSPEC int ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode);

/*
 *
 */
extern ELTDECLSPEC void ExSetBufferSize(unsigned int target, unsigned int buffer, unsigned int size, unsigned int mode);


/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGenVertexArrays(int n, unsigned int* arg);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExCreateUniformBuffer(unsigned int size);

/*
 *	@Return
 */
extern ELTDECLSPEC int ExDestroyBuffer(unsigned int buffer);



#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
