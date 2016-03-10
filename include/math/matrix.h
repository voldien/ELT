/*
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
#include"../elt_def.h"
#include"vect.h"
#include"quad.h"


// matrix = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
typedef exvec4f_t vec4x4_tt[4];
typedef exvecf_t vec4x4_t[4][4];
typedef struct vec4x4_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat4;
//typedef vec4x4 vec4x4_t;

// matrix = {{0,0,0},{0,0,0},{0,0,0}};
typedef exvecf_t vec3x3_t[3][3];
typedef struct vec3x3_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat3;
//typedef vec3x3 vec3x3_t;

// matrix = {{0,0},{0,0}};
typedef exvecf_t vec2x2_t[2][2];
typedef struct vec2x2_s{float m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;}mat2;
//typedef vec2x2 vec2x2_t;

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

/*

*/
extern void mat4x4_multi_vec4(const vec4x4_t lf_mat4,const float rf_vec4[4],float out_vec4[4]);

/*
*/
extern void mat4x4_multi_mat4x4(const vec4x4_t lf_mat4,const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

/*
 *
 */
extern void mat4x4_divs_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

/*
 *
 */
extern void mat4x4_addi_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

/*
 *
 */
extern void mat4x4_subt_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);

extern void mat4x4_identity(vec4x4_t f_mat4);
extern void mat4x4_transpose(vec4x4_t f_mat4);
extern float mat4x4_determinant(vec4x4_t f_mat4);
extern float mat4x4_inverse(vec4x4_t f_mat4);
extern void mat4x4_decompose(const vec4x4_t f_mat4, exvec3f_t f_position, exquat_t f_rotation, exvec3f_t f_scale);

/**
*/
extern void mat4x4_translation(vec4x4_t f_mat4,float x, float y, float z);
extern void mat4x4_translationv(vec4x4_t f_mat4,const exvec3f_t translation);

/**
*/
extern void mat4x4_scale(vec4x4_t f_mat4, float x,float y, float z);
extern void mat4x4_scalev(vec4x4_t f_mat4, exvec3f_t scale);

extern void mat4x4_rotation(vec4x4_t f_mat4,float angle,const exvec3f_t axis);
extern void mat4x4_rotationX(vec4x4_t f_mat4, float x_radi);
extern void mat4x4_rotationY(vec4x4_t f_mat4, float y_radi);
extern void mat4x4_rotationZ(vec4x4_t f_mat4, float z_radi);
extern void mat4x4_rotationQ(vec4x4_t f_mat4, exvec4f_t quad);

/*

*/
extern void mat4x4_multi_translation(vec4x4_t f_mat4,const exvec3f_t translate);
extern void mat4x4_multi_scale(vec4x4_t f_mat4,const exvec3f_t scale);
extern void mat4x4_multi_rotationx(vec4x4_t f_mat4, float f_x_radi);
extern void mat4x4_multi_rotationy(vec4x4_t f_mat4, float f_y_radi);
extern void mat4x4_multi_rotationz(vec4x4_t f_mat4, float f_z_radi);

extern void mat4x4_multi_rotationQ(vec4x4_t f_mat4,const exvec4f_t f_quad);



extern void mat4x4_proj(vec4x4_t f_mat4, float f_fov, float f_aspect, float f_near, float f_far);
extern void mat4x4_orth(vec4x4_t f_mat4,float f_right, float f_left, float f_top, float f_bottom, float f_far,float f_near);

extern int mat4x4_unproj(float winx, float winy, float winz,const vec4x4_t projection,const vec4x4_t modelview,const int* viewport,exvec3f_t pos);




extern void mat3x3_translation(vec3x3_t f_mat2,float x, float y);
extern void mat3x3_scale(vec3x3_t f_mat2, float x,float y);
extern void mat3x3_rotation(float rotation_pi);
extern void mat3x3_multi_mat3x3(const vec3x3_t lf_mat4,const vec3x3_t rf_mat4, vec3x3_t outf_mat4);




extern void mat2x2_translation(vec2x2_t f_mat2,float x, float y);
extern void mat2x2_scale(vec2x2_t f_mat2, float x,float y);
extern void mat2x2_rotation(float rotation_pi);
extern void mat2x2_multi_mat2x2(const vec2x2_t lf_mat4,const vec2x2_t rf_mat4, vec2x2_t outf_mat4);

#ifdef __cplusplus /* C++ environment */
}
#endif

#endif
