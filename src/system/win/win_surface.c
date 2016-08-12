#include"system/elt_surface.h"
#include<windows.h>


 void* ExCreateSurface(unsigned int width, unsigned height, unsigned int format){
    HBITMAP hbit;

    hbit = CreateBitmap(width, height, 1, 24,NULL);

    return hbit;
}


int ExDestroySurface(void* handle){
    return DeleteObject(handle);
}


void ExDisplaySurfaceToWindow(ExWin window,ExSurface surface){


}

int ExResizeSurface(ExSurface surface, unsigned int width, unsigned height){


}

int ExSetSurfacePixel(void* surface, unsigned int x, unsigned int y, unsigned long pixel){
    return SetPixel(surface, x, y, pixel);
}


 void ExFillRect(ExSurface handle,struct ex_rect* rect, unsigned int color){
	//XFillRectangle(display,handle,gc)

}
