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
#ifndef _ELT_QUATERNION_H_
#define _ELT_QUATERNION_H_ 1
#include"../elt_def.h"
#include"vect.h"


/*
 *
 */
#define EX_PI 3.14159265359F
#define EX_PI_D 3.141592653589793238462
#define EX_PI2 6.28318530718F
#define EX_PI2_D 6.28318530718
#define EX_THETA 1.57079632679F
#define EX_THETAD 1.57079632679
#define EX_E 2.7182818284F
#define EX_E_D 2.7182818284
#define EX_DEG2RAD( a ) ( ( (a) * EX_PI ) / 180.0f )
#define EX_RAD2DEG( a ) ( ( (a) * 180.0f ) / EX_PI )

/*
 *
 */
#define EX_MIN(a,b)	( ( (a) > (b) ) ? (a) : (b) )
#define EX_MAX(a,b)	( ( (a) < (b) ) ? (a) : (b) )
#define EX_CLAMP(a,min,max)	(EX_MAX( ( max ) ,EX_MIN( ( min ) , ( a ) )))
#define EX_LERP(a,b,t)	( ( (a) + ( (b) - (a) )*(t) )

/*
 *
 */
#define QuaternionDirection(x)	{}
#define QuaternionConjugate(x)	{x[1] = -x[1];x[2] = -x[2];x[3] = -x[3];}
#define QuaternionLength(x)	sqrtf((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]) + (x[3] * x[3]))
#define QuaternionLengthSqrt(x)	((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]) + (x[3] * x[3]))
#define QuaternionNormalize(x)	{float length = QuaternionLength(x);x[0] /= length;x[1] /= length;x[2] /= length;x[3] /= length;}
#define QuaternionInverse(x)	{float length = QuaternionLength(x);x[0] /= length;x[1] /= -length; x[2] /= -length; x[3] /= -length;}
#define QuaternionDot(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2] + x[3] * y[3])
#define QuaternionIdentity(x) {x[0] = 1.0f;x[1] = 0.0f;x[2] = 0.0f;x[3] = 0.0f;}
#define QuaternionCopy(a,b) {b[0] = a[0];b[1] = a[1];b[2] = a[2];b[3] = a[3];}
#define QuaternionYaw(lf_quad)  (float)atan2f(2.0f * (lf_quad[QUAD_W] * lf_quad[QUAD_X] + lf_quad[QUAD_Y] * lf_quad[QUAD_W]),( 1.0f - ( 2.0f * (lf_quad[QUAD_X] * lf_quad[QUAD_X] + lf_quad[QUAD_Y] * lf_quad[QUAD_Y]))))
#define QuaternionPitch(lf_quad) (float)asinf(-2.0f * (lf_quad[QUAD_Z] * lf_quad[QUAD_Y] + lf_quad[QUAD_W] * lf_quad[QUAD_X]))
#define QuaternionRoll(lf_quad) (float)atan2f(2.0f * (lf_quad[QUAD_W] * lf_quad[QUAD_Z] + lf_quad[QUAD_X] * lf_quad[QUAD_Y]), 1.0f - (2.0f * (lf_quad[QUAD_Y] * lf_quad[QUAD_Y] + lf_quad[QUAD_Z] * lf_quad[QUAD_Z])))

/*
 *
 */
typedef exvecf_t exquat_t EX_ALIGN_VECTOR(16);
typedef exvecd_t exquatd_t EX_ALIGN_VECTOR(32);

#ifdef __cplusplus  /*  C++ environment   */
extern "C"{
#endif


/*
 *    quaternion multiplication with left quaternion
 */
extern void quad_multi_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad);
/*
 *    quaternion multiplication with left quaternion
 */
extern void quad_add_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad);
/**
    quaternion multiplication with left quaternion
*/

extern void quad_sub_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad);
extern void quad_divi_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad);

extern void quad_multi_vec3(exquat_t lf_quat, exvec3f_t rf_vec, exquat_t out_quat);

/**

*/
extern void quad_direction(exquat_t lf_quad, exvec3f_t dir);
extern void quad_directionv(exquat_t lf_quad, exvec3f_t dir, const exvec3f_t _dir);

extern void quad_axis_angle(exquat_t lf_quad, const exvec3f_t axis, float f_angle);
extern void quad_axis(exquat_t lf_quad, float pitch_rad, float yaw_rad, float roll_rad);
extern void quad_lookrotation(exquat_t f_quad, exvec3f_t f_dir);
extern void quad_rotate(const exquat_t lf_quad, exquat_t rf_quad[4], exquat_t out_quad);
extern void quad_rotate_vec(const exquat_t lf_quad, exvec3f_t vec3);


extern void quad_slerp(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t outf_quad, float f_time);

/*
	// quaternion x rotation in radian
*/
extern float quad_pitch(const exquat_t lf_quad);
/*
	// quaternion y rotation in radian
*/
extern float quad_yaw(const exquat_t lf_quad);
/*
	// quaternion z rotation in radian
*/
extern float quad_roll(const exquat_t lf_quad);




#ifdef __cplusplus
}
#endif


#endif
