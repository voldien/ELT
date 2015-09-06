#include"math/raytrace.h"

int line_intersec_line(const vec3_t pos1_1,const vec3_t pos1_2,const vec3_t pos2_1,const  vec3_t pos2_2,vec3_t pos){


    return 1;

}
int line_intersec_box(const vec3_t pos,const vec3_t dir,const vec3_t size,const vec3_t center){

    return 1;
}


float ray_intersec_sphere(const vec3_t pos,const  vec3_t dir, const vec3_t center, float radius){
    vec3_t rc;
    float a,b,c,d, t,disc;

    VectorSubtract(dir,center,rc);
    a = DotProduct(dir,dir);
    b = 2.0f * DotProduct(dir,rc);
    c = DotProduct(rc,rc) - (radius * radius);

    disc =  b*b - 4 * a * c;
    if(disc > 0){
        //d = b*b - c;
        t = (-b - d) / (2.0f *a);
        if(t > 0.0){
        	return t;
        }
    }
    return 0;
}
