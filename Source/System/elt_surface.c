#include"elt_surface.h"
#include"elt_win.h"

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
#endif
}


DECLSPEC int ExDestroySurface(void* handle){
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)
    return XDestroyImage((XImage*)handle);
#endif
}



DECLSPEC int ExSetSurfacePixe(void* handle, unsigned int x, unsigned int y, long pixel){
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)
    return XPutPixel((XImage*)handle, x,y, pixel);
#endif // EX_WINDOWS

}
