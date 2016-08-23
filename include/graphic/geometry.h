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
/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGenBuffers(int n, unsigned int* buffers);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetBufferSize(unsigned int target, unsigned int buffer, unsigned int size, unsigned int mode);


/**
 *	Generate vertex arrays.
 *
 *	\n
 *
 *	\arg
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGenVertexArrays(int n, unsigned int* arg);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateUniformBuffer(unsigned int size);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExDestroyBuffer(unsigned int buffer);


#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
