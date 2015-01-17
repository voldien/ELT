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
#ifndef _ELT_VECT_H
#define _ELT_VECT_H

#ifndef ALIGN
#   ifdef _WIN32
        #define ALIGN(x) __declspec(align(x))
#   else
        #define ALIGN(x)	__attribute__ ((aligned(x)))
#   endif
#endif

/*

*/
#define VEC3_UNIT_X {1.0f, 0.0f, 0.0f}
#define VEC3_UNIT_Y {0.0f, 1.0f, 0.0f}
#define VEC3_UNIT_Z {0.0f, 0.0f, 1.0f}
#define VEC3_UNIT_W {0.0f, 0.0f, 0.0f, 1.0f}
#define NVEC3_UNIT_X {-1.0f, 0.0f, 0.0f}
#define NVEC3_UNIT_Y {0.0f, -1.0f, 0.0f}
#define NVEC3_UNIT_Z {0.0f, 0.0f, -1.0f}
#define NVEC3_UNIT_W {0.0f, 0.0f, 0.0f, -1.0f}


#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define CrossProduct(x,y,c)	{c[0] = ((x[1] * y[2]) - (x[2] * y[1])); c[1] = ((x[2] * y[0]) - (x[0] * y[2])); c[2] = ((x[0] * y[1]) - (x[1] * y[0]));}
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
#define VectorScale(a,b,c) {c[0]=b*a[0];c[1]=b*a[1];c[2]=b*a[2];}
#define VectorProduct(a,b,c) {c[0] = a[0]*b[0];c[1] = a[1]*b[1];c[2] = a[2]*b[2];}
#define VectorClear(x) {x[0] = x[1] = x[2] = 0;}
#define	VectorNegate(x) {x[0]=-x[0];x[1]=-x[1];x[2]=-x[2];}
#define VectorNormalize(x) {float length = VectorLength(x); x[0] /= length; x[1] /= length; x[2] /= length;}
#define VectorLength(x)	sqrtf((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]))
#define VectorLengthSqrt(x) ((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]))
#define VectorInverse(x)	{x[0] = 1.0f / x[0]; x[1] = 1.0f /x[1]; x[2] = 1.0 / x[2];}
#define VectorReflect(x,n,y)	{y[0] = 2.0f *( x[0] * n[0]) * n[0] - x[0];y[0] = 2.0f *( x[1] * n[1]) * n[1] - x[1];y[2] = 2.0f *( x[2] * n[2]) * n[2] - x[2];}
#define VectorOrthoNormalize(x,y) { float length;}
#define VectorProj(x,y,c)	{float lengthy = VectorLength(y);float dot = DotProduct(x,y); c[0] = dot * x[0] / lengthy;  c[1] = dot * x[1] / lengthy;  c[2] = dot * x[2] / lengthy; }
#define VectorLerp(x,y,t,c)	{}
#define VectorDefine(a,x,y,z)	{a[0] = x;a[1] = y;a[2] = z;}



#ifdef DOUBLEVEC_T
	typedef double vec_t;
#else
	typedef float vec_t;
#endif
// vector2 = {x,y}
typedef vec_t vec2_t[2];
// vector2 = {x,y,z}
typedef vec_t vec3_t[3];
// vector2 = {x,y,z,w}
typedef vec_t vec4_t[4];



#endif // _ELT_VECT_H
