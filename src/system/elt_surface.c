#include"system/elt_surface.h"
#include"system/elt_win.h"
#ifdef EX_LINUX
#include"system/unix/unix_win.h"
#	include<X11/Xlib.h>
#endif

static int surface_bits_per_pixel(unsigned int format){
    switch(format){
        case EX_RGB:return 24;
        case EX_RGBA:return 32;
        default:return -1;
    }
}


DECLSPEC void* ExCreatSurface(unsigned int width, unsigned height, unsigned int format){
#ifdef EX_WINDOWS
    HBITMAP hbit;

    hbit = CreateBitmap(width, height, 1, 24,NULL);

    return hbit;
#elif defined(EX_LINUX)
    XImage* image;
    char* buffer;
    buffer = (char*)malloc(surface_bits_per_pixel(format) * width * height);

    image = XCreateImage(display,CopyFromParent,
         surface_bits_per_pixel(format),
         ZPixmap, 0, (char*)buffer,width,height,8,0  );
    return image;
#elif defined(EX_ANDROID)

#endif
}


DECLSPEC int ExDestroySurface(void* handle){
#ifdef EX_WINDOWS
    return DeleteObject(handle);
#elif defined(EX_LINUX)
    return XDestroyImage((XImage*)handle);
#elif defined(EX_ANDROID)

#endif
}



DECLSPEC int ExSetSurfacePixel(void* handle, unsigned int x, unsigned int y, long pixel){
#ifdef EX_WINDOWS
    return SetPixel(handle,x,y,pixel);
#elif defined(EX_LINUX)
    return XPutPixel((XImage*)handle, x,y, pixel);
#elif defined(EX_ANDROID)

#endif
}

DECLSPEC int ExFillRect(void* handle,struct exrect* rect, unsigned int  color){
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)

#elif defined(EX_ANDROID)

#endif
}
