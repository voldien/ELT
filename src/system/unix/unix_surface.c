#include"system/elt_surface.h"
#include"system/elt_win.h"

#include"system/unix/unix_win.h"
#	include<X11/Xlib.h>
#	include <X11/extensions/XShm.h>


static int surface_bits_per_pixel(unsigned int format){
    switch(format){
        case EX_RGB:return 24;
        case EX_RGBA:return 32;
        default:return -1;
    }
}



DECLSPEC void* ExCreateSurface(unsigned int width, unsigned height, unsigned int format){
	int use_mitshm = 1;
    XImage* image;
    char* buffer;

#ifndef NO_SHARED_MEMORY
	//try_mitshm(this, screen);
    /*
	if(use_mitshm) {
		image = XShmCreateImage(display, SDL_Visual,
						 this->hidden->depth, ZPixmap,
						 shminfo.shmaddr, &shminfo,
						 screen->w, screen->h);
		if(!image) {
			XShmDetach(SDL_Display, &shminfo);
			XSync(SDL_Display, False);
			shmdt(shminfo.shmaddr);
			screen->pixels = NULL;
			goto error;
		}
		this->UpdateRects = X11_MITSHMUpdate;
	}*/
	//if(!use_mitshm)
#endif

    buffer = (char*)malloc(surface_bits_per_pixel(format) * width * height);

    image = XCreateImage(display,CopyFromParent,
         surface_bits_per_pixel(format),
         ZPixmap, 0, (char*)buffer,width,height,8,0  );


    return image;
}

DECLSPEC int ExDestroySurface(void* handle){
    return XDestroyImage((XImage*)handle);
}


DECLSPEC int ExSetSurfacePixel(void* handle, unsigned int x, unsigned int y, long pixel){
    return XPutPixel((XImage*)handle, x,y, pixel);
}

DECLSPEC int ExFillRect(ExSurface handle, ExRect* rect, unsigned int color){
	//XFillRectangle(display, m_window, gc,0,0,this->getWidth(),this->getHeight());
}
