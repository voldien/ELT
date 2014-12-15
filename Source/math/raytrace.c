#include"raytrace.h"

int line_intersec_line(const vec3_t pos1_1,const vec3_t pos1_2,const vec3_t pos2_1,const  vec3_t pos2_2,vec3_t pos){


    return 1;

}
int line_intersec_box(const vec3_t pos,const vec3_t dir,const vec3_t size,const vec3_t center){


}


int line_intersec_sphere(const vec3_t pos,const  vec3_t dir, const vec3_t center, float radius){
    vec3_t rc;
    float b,c,d, t;
    VectorSubtract(dir,center,rc);

    c = DotProduct(rc,rc) - (radius * radius);
    b = DotProduct(dir,rc);
    d = b*b - c;
    t = -b - sqrt(abs(d));
    if(t > 0.0)
        return 1;
    else
        return 0;

    return t;
}
