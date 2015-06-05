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
#ifndef _ELT_MATRIX_H_
#define _ELT_MATRIX_H_ 1
#include"vect.h"
#include"quad.h"


// matrix = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
typedef vec_t vec4x4_t[4][4];
typedef struct vec4x4_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat4;
#define vec4x4 ALIGN(16) vec4x4_t

// matrix = {{0,0,0},{0,0,0},{0,0,0}};
typedef vec_t vec3x3_t[3][3];
typedef struct vec3x3_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat3;
#define vec3x3 ALIGN(9) vec3x3_t

// matrix = {{0,0},{0,0}};
typedef vec_t vec2x2_t[2][2];
typedef struct vec2x2_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat2;
#define vec2x2 ALIGN(4) vec2x2_t

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif


/*

*/
extern void mat4x4_multi_vec4(const vec4x4_t lf_mat4,const float rf_vec4[4],float out_vec4[4]);
/*
*/
extern void mat4x4_multi_mat4x4(const vec4x4_t lf_mat4,const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

extern void mat4x4_divs_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);
extern void mat4x4_addi_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);
extern void mat4x4_subt_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

extern void mat4x4_identity(vec4x4_t f_mat4);
extern void mat4x4_transpose(vec4x4_t f_mat4);
extern float mat4x4_determinant(vec4x4_t f_mat4);
extern float mat4x4_inverse(vec4x4_t f_mat4);
extern void mat4x4_decompose(const vec4x4_t f_mat4, vec3_t f_position, quat_t f_rotation, vec3_t f_scale);

/**
*/
extern void mat4x4_translation(vec4x4_t f_mat4,float x, float y, float z);
extern void mat4x4_translationv(vec4x4_t f_mat4,const vec3_t translation);

/**
*/
extern void mat4x4_scale(vec4x4_t f_mat4, float x,float y, float z);
extern void mat4x4_scalev(vec4x4_t f_mat4, vec3_t scale);

extern void mat4x4_rotation(vec4x4_t f_mat4,float angle,const vec3_t axis);
extern void mat4x4_rotationX(vec4x4_t f_mat4, float x_radi);
extern void mat4x4_rotationY(vec4x4_t f_mat4, float y_radi);
extern void mat4x4_rotationZ(vec4x4_t f_mat4, float z_radi);
extern void mat4x4_rotationQ(vec4x4_t f_mat4, vec4_t quad);

/*

*/
extern void mat4x4_multi_translation(vec4x4_t f_mat4,const vec3_t translate);
extern void mat4x4_multi_scale(vec4x4_t f_mat4,const vec3_t scale);
extern void mat4x4_multi_rotationx(vec4x4_t f_mat4, float f_x_radi);
extern void mat4x4_multi_rotationy(vec4x4_t f_mat4, float f_y_radi);
extern void mat4x4_multi_rotationz(vec4x4_t f_mat4, float f_z_radi);

extern void mat4x4_multi_rotationQ(vec4x4_t f_mat4,const float f_quad[4]);



extern void mat4x4_proj(vec4x4_t f_mat4, float f_fov, float f_aspect, float f_near, float f_far);
extern void mat4x4_orth(vec4x4_t f_mat4,float f_right, float f_left, float f_top, float f_bottom, float f_far,float f_near);

extern int mat4x4_unproj(float winx, float winy, float winz,const vec4x4_t projection,const vec4x4_t modelview,const int* viewport,vec3_t pos);


#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
