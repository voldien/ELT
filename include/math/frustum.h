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
#ifndef _ELT_FRUSTUM_H_
#define _ELT_FRUSTUM_H_ 1
#include"vect.h"
#include"matrix.h"

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

struct frustum{

};
//struct frustum_sphere
extern int frustum_create(struct frustum* f);

extern int frustum_AABB(const float* b, struct frustum* f);
extern int frustum_sphere(const float* pos,float radius, struct frustum* f);
extern int frustum_point(const vec3_t point, struct frustum* f);




#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
