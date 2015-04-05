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
#include<math.h>
#include"vect.h"

#define PI 3.14159265359F
#define EX_PI 3.14159265359F
#define PI_D 3.141592653589793238462
#define PI2 6.28318530718F
#define PI2_D 6.28318530718
#define THETA 1.57079632679F
#define THETAD 1.57079632679
#define E_E 2.7182818284F
#define E_E_D 2.7182818284
#define DEG2RAD( a ) ( ( (a) * PI ) / 180.0F )
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / PI )

#define MIN(a,b)	( ( (a) > (b) ) ? (a) : (b) )
#define MAX(a,b)	( ( (a) < (b) ) ? (a) : (b) )
#define CLAMP(a,min,max)	(MAX( ( max ) ,MIN( ( min ) , ( a ) )))
#define LERP(a,b,t)	( ( (a) + ( (b) - (a) )*(t) )



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

// quaternion = {w, x,y,z}
typedef float quat_t[4];

#ifdef __cplusplus  /*  C++ environment   */
extern "C"{
#endif


/**
    quaternion multiplication with left quaternion
*/
extern void quad_multi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
/**
    quaternion multiplication with left quaternion
*/
extern void quad_add_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
/**
    quaternion multiplication with left quaternion
*/

extern void quad_sub_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
extern void quad_divi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);

extern void quad_multi_vec3(float lf_quat[4], vec3_t rf_vec,float out_quat[4]);

/**

*/
extern void quad_direction(float lf_quad[4], vec3_t dir);
extern void quad_directionv(float lf_quad[4], vec3_t dir,const vec3_t _dir);

extern void quad_axis_angle(float lf_quad[4],const vec3_t axis, float f_angle);
extern void quad_axis(float lf_quad[4], float pitch_rad,float yaw_rad,float roll_rad);
extern void quad_lookrotation(float f_quad[4], vec3_t f_dir);
extern void quad_rotate(const float lf_quad[4], const float rf_quad[4], float out_quad[4]);
extern void quad_rotate_vec(const float lf_quad[4], vec3_t vec3);


extern void quad_slerp(const float lf_quad[4],const float rf_quad[4], float outf_quad[4],float f_time);

/*
	// quaternion x rotation in radian
*/
extern float quad_pitch(const float lf_quad[4]);
/*
	// quaternion y rotation in radian
*/
extern float quad_yaw(const float lf_quad[4]);
/*
	// quaternion z rotation in radian
*/
extern float quad_roll(const float lf_quad[4]);




#ifdef __cplusplus
}
#endif


#endif
