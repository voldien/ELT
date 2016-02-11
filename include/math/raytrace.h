/*
========================================================================
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
#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_ 1
#include"vect.h"

struct ray{
	vec3_t pos;
	vec3_t dir;
};

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

extern int line_intersec_line(const vec3_t pos1_1,const vec3_t pos1_2,const vec3_t pos2_1,const  vec3_t pos2_2,vec3_t pos);

extern int ray_intersect_ray(const vec3_t origin1, const vec3_t dir1, const vec3_t origin2, const vec3_t dir2, vec3_t pos);

extern int line_intersec_box(const vec3_t pos,const vec3_t dir,const vec3_t size,const vec3_t center);

extern float ray_intersec_box(const vec3_t pos,const vec3_t dir,const vec3_t size,const vec3_t center);

extern float ray_intersec_sphere(const vec3_t pos,const  vec3_t dir, const vec3_t center, float radius);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
