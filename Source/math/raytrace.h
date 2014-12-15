
#ifndef _RAY_TRACE_H
#define _RAY_TRACE_H
#include"vect.h"

struct ray{
	vec3_t pos;
	vec3_t dir;
};

extern int line_intersec_line(const vec3_t pos1_1,const vec3_t pos1_2,const vec3_t pos2_1,const  vec3_t pos2_2,vec3_t pos);

extern int line_intersec_box(const vec3_t pos,const vec3_t dir,const vec3_t size,const vec3_t center);

extern int line_intersec_sphere(const vec3_t pos,const  vec3_t dir, const vec3_t center, const vec3_t radius);


#endif
