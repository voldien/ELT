#include"system/elt_surface.h"
#include<windows.h>


DECLSPEC void* ExCreateSurface(unsigned int width, unsigned height, unsigned int format){
    HBITMAP hbit;

    hbit = CreateBitmap(width, height, 1, 24,NULL);

    return hbit;
}


DECLSPEC int ExDestroySurface(void* handle){
    return DeleteObject(handle);
}

DECLSPEC int ExSetSurfacePixel(void* handle, unsigned int x, unsigned int y, long pixel){
    return SetPixel(handle,x,y,pixel);
}


DECLSPEC int ExFillRect(ExSurface handle,struct ex_rect* rect, unsigned int color){

}
}
