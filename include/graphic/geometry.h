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

/*
 *
 */
extern int ExCreateVBO(unsigned int target, unsigned int size, unsigned int mode);

/*
 *
 */
extern int ExCreateVAO(void);

/*
 *
 */
extern int ExCreateUniformBuffer(unsigned int size);

/*
 *
 */
extern int ExDestroyBuffer(unsigned int buffer);



#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
