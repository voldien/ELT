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
	exvec3f_t pos;
	exvec3f_t dir;
};

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

extern int line_intersec_line(const exvec3f_t pos1_1,const exvec3f_t pos1_2,const exvec3f_t pos2_1,const  exvec3f_t pos2_2,exvec3f_t pos);

extern int ray_intersect_ray(const exvec3f_t origin1, const exvec3f_t dir1, const exvec3f_t origin2, const exvec3f_t dir2, exvec3f_t pos);

extern int line_intersec_box(const exvec3f_t pos,const exvec3f_t dir,const exvec3f_t size,const exvec3f_t center);

extern float ray_intersec_box(const exvec3f_t pos,const exvec3f_t dir,const exvec3f_t size,const exvec3f_t center);

extern float ray_intersec_sphere(const exvec3f_t pos,const  exvec3f_t dir, const exvec3f_t center, float radius);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
