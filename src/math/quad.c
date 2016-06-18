#include"math/quad.h"

#define QX 0x1
#define QY 0x2
#define QZ 0x3
#define QW 0x0

void quad_multi_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad){
	// w
    out_quad[QW] = (lf_quad[QW] * rf_quad[QW]) - (lf_quad[QX] * rf_quad[QX]) - (lf_quad[QY] * rf_quad[QY]) - (lf_quad[QZ] * rf_quad[QZ]);
	// x
    out_quad[QX] = (lf_quad[QX] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QX]) + (lf_quad[QY] * rf_quad[QZ]) - (lf_quad[QZ] * rf_quad[QY]);
	// y
    out_quad[QY] = (lf_quad[QY] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QY]) + (lf_quad[QZ] * rf_quad[QX]) - (lf_quad[QX] * rf_quad[QZ]);
	// z
    out_quad[QZ] = (lf_quad[QZ] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QZ]) + (lf_quad[QX] * rf_quad[QY]) - (lf_quad[QY] * rf_quad[QX]);
}

void quad_multi_vec3(exquat_t lf_quat, exvec3f_t rf_vec, exquat_t out_quat){
	out_quat[QW] = -(lf_quat[QX] * rf_vec[QX]) - (lf_quat[QY] * rf_vec[QY]) - (lf_quat[QZ] * rf_vec[QZ]);
	out_quat[QX] =  (lf_quat[QW] * rf_vec[QX]) + (lf_quat[QY] * rf_vec[QZ]) - (lf_quat[QZ] * rf_vec[QY]);
	out_quat[QY] =  (lf_quat[QW] * rf_vec[QY]) + (lf_quat[QZ] * rf_vec[QX]) - (lf_quat[QX] * rf_vec[QZ]);
	out_quat[QZ] =  (lf_quat[QW] * rf_vec[QZ]) + (lf_quat[QX] * rf_vec[QY]) - (lf_quat[QY] * rf_vec[QX]);

}

void quad_add_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad){
	out_quad[QW] = lf_quad[0] + rf_quad[0];
	out_quad[QX] = lf_quad[1] + rf_quad[1];
	out_quad[QY] = lf_quad[2] + rf_quad[2];
	out_quad[QZ] = lf_quad[3] + rf_quad[3];
}

void quad_sub_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad){
	out_quad[QW] = lf_quad[QW] - rf_quad[QW];
	out_quad[QX] = lf_quad[QX] - rf_quad[QX];
	out_quad[QY] = lf_quad[QY] - rf_quad[QY];
	out_quad[QZ] = lf_quad[QZ] - rf_quad[QZ];
}

void quad_divi_quad(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t out_quad){
	out_quad[QW] = lf_quad[QW] / rf_quad[QW];
	out_quad[QX] = lf_quad[QX] / rf_quad[QX];
	out_quad[QY] = lf_quad[QY] / rf_quad[QY];
	out_quad[QZ] = lf_quad[QZ] / rf_quad[QZ];
}


void quad_axis_angle(exquat_t lf_quad,const exvec3f_t axis, float f_angle){
	const float half_angle = sinf(f_angle * 0.5f);
	lf_quad[QX] = axis[0] * half_angle;
	lf_quad[QY] = axis[1] * half_angle;
	lf_quad[QZ] = axis[2] * half_angle;
	lf_quad[QW] = cosf(half_angle);
}

void quad_axis(exquat_t lf_quad, float pitch_rad,float yaw_rad,float roll_rad){
	const float num1 = roll_rad * 0.5f;
	const float num2 = (float)sinf((float)num1);
	const float num3 = (float)cosf((float)num1);
	const float num4 = pitch_rad * 0.5f;
	const float num5 = (float)sinf((float)num4);
	const float num6 = (float)cosf((float)num4);
	const float num7 = yaw_rad * 0.5f;
	const float num8 = (float)sinf((float)num7);
	const float num9 = (float)cosf((float)num7);

	lf_quad[QX] = (float)((double)num9 * (double)num5 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
	lf_quad[QY] = (float)((double)num8 * (double)num6 * (double)num3 - (double)num9 * (double)num5 * (double)num2);
	lf_quad[QZ] = (float)((double)num9 * (double)num6 * (double)num2 - (double)num8 * (double)num5 * (double)num3);
	lf_quad[QW] = (float)((double)num9 * (double)num6 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
}



void quad_direction(exquat_t lf_quad, exvec3f_t dir){
	float quad[4];
	float quad_t[4];
	exvec3f_t targetup;
	exvec3f_t targetforward;
	exvec3f_t forward = VEC3_UNIT_Z;
	exvec3f_t up = VEC3_UNIT_Y;

	quad_multi_vec3(lf_quad, forward,targetforward);
	quad_multi_vec3(lf_quad, up,targetup);


	CrossProduct(targetforward,targetup,dir);
	VectorNormalize(dir);
}
void quad_directionv(exquat_t lf_quad, exvec3f_t dir, const exvec3f_t _dir){
	exquat_t quad;
	exquat_t quad_t;
	exquat_t quad_t2;

	//quat_multiplyVec3(lf_quad,_dir,dir);
	//return;
	//VectorNegate(_dir);
	//mulit_quat_vec3(lf_quad,_dir,quad_t2);
	QuaternionCopy(lf_quad,quad);
	QuaternionConjugate(quad);
	quad_multi_quad(quad_t2,quad,quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}


float quad_pitch(const exquat_t lf_quad){
	return (float)asinf(-2.0f * (lf_quad[QZ] * lf_quad[QY] + lf_quad[QW] * lf_quad[QX]));
}


float quad_yaw(const exquat_t lf_quad){
    return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QX] + lf_quad[QY] * lf_quad[QW]),( 1.0f - ( 2.0f * (lf_quad[QX] * lf_quad[QX] + lf_quad[QY] * lf_quad[QY]))));
}


float quad_roll(const exquat_t lf_quad){
	return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QZ] + lf_quad[QX] * lf_quad[QY]), 1.0f - (2.0f * (lf_quad[QY] * lf_quad[QY] + lf_quad[QZ] * lf_quad[QZ])));
}

void quad_slerp(const exquat_t lf_quad, const exquat_t rf_quad, exquat_t outf_quad, float f_time){

}

