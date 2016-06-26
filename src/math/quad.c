#include"math/quad.h"
#include<math.h>

#define QX 0x1
#define QY 0x2
#define QZ 0x3
#define QW 0x0

void quad_multi_quad(const exquatf_t* lf_quad, const exquatf_t* rf_quad, exquatf_t* out_quat){
	/*	w	*/
	out_quat[0][QW] = (lf_quad[0][QW] * rf_quad[0][QW]) - (lf_quad[0][QX] * rf_quad[0][QX]) - (lf_quad[0][QY] * rf_quad[0][QY]) - (lf_quad[0][QZ] * rf_quad[0][QZ]);
	/*	x	*/
    out_quat[0][QX] = (lf_quad[0][QX] * rf_quad[0][QW]) + (lf_quad[0][QW] * rf_quad[0][QX]) + (lf_quad[0][QY] * rf_quad[0][QZ]) - (lf_quad[0][QZ] * rf_quad[0][QY]);
	/*	y	*/
    out_quat[0][QY] = (lf_quad[0][QY] * rf_quad[0][QW]) + (lf_quad[0][QW] * rf_quad[0][QY]) + (lf_quad[0][QZ] * rf_quad[0][QX]) - (lf_quad[0][QX] * rf_quad[0][QZ]);
	/*	z	*/
    out_quat[0][QZ] = (lf_quad[0][QZ] * rf_quad[0][QW]) + (lf_quad[0][QW] * rf_quad[0][QZ]) + (lf_quad[0][QX] * rf_quad[0][QY]) - (lf_quad[0][QY] * rf_quad[0][QX]);
}

void quad_multi_vec3(exquatf_t* lf_quat, exvec3f_t rf_vec, exquatf_t* out_quat){
	out_quat[0][QW] = -(lf_quat[0][QX] * rf_vec[QX]) - (lf_quat[0][QY] * rf_vec[QY]) - (lf_quat[0][QZ] * rf_vec[QZ]);
	out_quat[0][QX] =  (lf_quat[0][QW] * rf_vec[QX]) + (lf_quat[0][QY] * rf_vec[QZ]) - (lf_quat[0][QZ] * rf_vec[QY]);
	out_quat[0][QY] =  (lf_quat[0][QW] * rf_vec[QY]) + (lf_quat[0][QZ] * rf_vec[QX]) - (lf_quat[0][QX] * rf_vec[QZ]);
	out_quat[0][QZ] =  (lf_quat[0][QW] * rf_vec[QZ]) + (lf_quat[0][QX] * rf_vec[QY]) - (lf_quat[0][QY] * rf_vec[QX]);

}

void quad_add_quad(const exquatf_t* lf_quad, const exquatf_t* rf_quad, exquatf_t* out_quat){
	*out_quat = *lf_quad + *rf_quad;
	/*
	out_quat[0][QW] = lf_quad[0][0] + rf_quad[0][0];
	out_quat[0][QX] = lf_quad[0][1] + rf_quad[0][1];
	out_quat[0][QY] = lf_quad[0][2] + rf_quad[0][2];
	out_quat[0][QZ] = lf_quad[0][3] + rf_quad[0][3];
	*/
}

void quad_sub_quad(const exquatf_t* lf_quad, const exquatf_t* rf_quad, exquatf_t* out_quat){
	out_quat[0][QW] = lf_quad[0][QW] - rf_quad[0][QW];
	out_quat[0][QX] = lf_quad[0][QX] - rf_quad[0][QX];
	out_quat[0][QY] = lf_quad[0][QY] - rf_quad[0][QY];
	out_quat[0][QZ] = lf_quad[0][QZ] - rf_quad[0][QZ];
}

void quad_divi_quad(const exquatf_t* lf_quad, const exquatf_t* rf_quad, exquatf_t* out_quat){
	out_quat[0][QW] = lf_quad[0][QW] / rf_quad[0][QW];
	out_quat[0][QX] = lf_quad[0][QX] / rf_quad[0][QX];
	out_quat[0][QY] = lf_quad[0][QY] / rf_quad[0][QY];
	out_quat[0][QZ] = lf_quad[0][QZ] / rf_quad[0][QZ];
}


void quad_axis_angle(exquatf_t* lf_quad,const exvec3f_t axis, float f_angle){
	const float half_angle = sinf(f_angle * 0.5f);
	lf_quad[0][QX] = axis[0] * half_angle;
	lf_quad[0][QY] = axis[1] * half_angle;
	lf_quad[0][QZ] = axis[2] * half_angle;
	lf_quad[0][QW] = cosf(half_angle);
}

void quad_axis(exquatf_t* lf_quad, float pitch_rad,float yaw_rad,float roll_rad){
	const float num1 = roll_rad * 0.5f;
	const float num2 = (float)sinf((float)num1);
	const float num3 = (float)cosf((float)num1);
	const float num4 = pitch_rad * 0.5f;
	const float num5 = (float)sinf((float)num4);
	const float num6 = (float)cosf((float)num4);
	const float num7 = yaw_rad * 0.5f;
	const float num8 = (float)sinf((float)num7);
	const float num9 = (float)cosf((float)num7);

	lf_quad[0][QX] = (float)((double)num9 * (double)num5 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
	lf_quad[0][QY] = (float)((double)num8 * (double)num6 * (double)num3 - (double)num9 * (double)num5 * (double)num2);
	lf_quad[0][QZ] = (float)((double)num9 * (double)num6 * (double)num2 - (double)num8 * (double)num5 * (double)num3);
	lf_quad[0][QW] = (float)((double)num9 * (double)num6 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
}



void quad_direction(exquatf_t* lf_quad, exvec3f_t dir){
	exquatf_t quad;
	exquatf_t quad_t;
	exvec3f_t targetup;
	exvec3f_t targetforward;
	exvec3f_t forward = VEC3_UNIT_Z;
	exvec3f_t up = VEC3_UNIT_Y;

	quad_multi_vec3(&lf_quad, forward, &targetforward);
	quad_multi_vec3(&lf_quad, up, &targetup);


	CrossProduct(targetforward,targetup,dir);
	VectorNormalize(dir);
}
void quad_directionv(exquatf_t* lf_quad, exvec3f_t dir, const exvec3f_t _dir){
	exquatf_t quad;
	exquatf_t quad_t;
	exquatf_t quad_t2;
/*
	quat_multiplyVec3(lf_quad[0],_dir,dir);
	return;
	VectorNegate(_dir);
	mulit_quat_vec3(lf_quad[0],_dir,quad_t2);
	*/
	//QuaternionCopy(lf_quad[0],quad);
	//QuaternionConjugate(quad);
	quad_multi_quad(&quad_t2, &quad, &quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}


float quad_pitch(const exquatf_t* lf_quad){
	return (float)asinf(-2.0f * (lf_quad[0][QZ] * lf_quad[0][QY] + lf_quad[0][QW] * lf_quad[0][QX]));
}


float quad_yaw(const exquatf_t* lf_quad){
    return (float)atan2f(2.0f * (lf_quad[0][QW] * lf_quad[0][QX] + lf_quad[0][QY] * lf_quad[0][QW]),( 1.0f - ( 2.0f * (lf_quad[0][QX] * lf_quad[0][QX] + lf_quad[0][QY] * lf_quad[0][QY]))));
}


float quad_roll(const exquatf_t* lf_quad){
	return (float)atan2f(2.0f * ( (lf_quad[0][QW]) * (lf_quad[0][QZ]) + ( lf_quad[0][QX] ) * (  lf_quad[0][QY] )), 1.0f - (2.0f * ( (  lf_quad[0][QY] ) * ( lf_quad[0][QY] ) + ( lf_quad[0][QZ]) * ( lf_quad[0][QZ] ) )));
}

void quad_slerp(const exquatf_t* lf_quad, const exquatf_t* rf_quad, exquatf_t* outf_quad, float f_time){

}

