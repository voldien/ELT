#include"system/elt_surface.h"
#include"system/elt_win.h"
#include"system/elt_errorhandler.h"

#include<assert.h>
#include<X11/Xlib.h>
#include<X11/extensions/XShm.h>

static int private_surface_bits_per_pixel(unsigned int format){
    switch(format){
        case EX_RGB:return 24;
        case EX_RGBA:return 32;
        default:return -1;
    }
}


void* ExCreateSurface(unsigned int width, unsigned height, unsigned int format){
    XImage* image;
    char* buffer;
    unsigned int size;

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
    size = private_surface_bits_per_pixel(format) * width * height;
    buffer = (char*)malloc(size);
    assert(buffer);

    image = XCreateImage(display,CopyFromParent,
         private_surface_bits_per_pixel(format),
         ZPixmap, 0, (char*)buffer, width, height, 8,0  );


    return image;
}

int ExDestroySurface(void* handle){
    return XDestroyImage((XImage*)handle);
}


void ExDisplaySurfaceToWindow(ExWin window, ExSurface surface){
	ExRect rect;
	GC gc;

	if(ExGetSurfaceRect(surface, &rect)){

		gc = XDefaultGC(display, XDefaultScreen(display));
		XSetFillStyle(display, gc, FillSolid);
		XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
		XSetBackground(display, gc, WhitePixel(display, DefaultScreen(display)));
		//XSync(display, False);

		XPutImage(display, window, gc, surface , 0, 0, 0, 0, rect.width, rect.height);
	}
}

ERESULT ExResizeSurface(ExSurface surface, unsigned int width, unsigned height){
	((XImage*)surface)->data = realloc( ((XImage*)surface)->data,width * height * ((XImage*)surface)->bitmap_pad);
	if( ((XImage*)surface)->data){
		((XImage*)surface)->width = width;
		((XImage*)surface)->height = height;
	}

	return EX_FALSE;
}


ERESULT ExGetSurfaceRect(ExSurface surface, ExRect* rect){
	if(rect == NULL){
		return E_INVALID_ARGUMENT;
	}

	rect->x = ((XImage*)surface)->xoffset;
	rect->y = ((XImage*)surface)->xoffset;
	rect->width = ((XImage*)surface)->width;
	rect->height = ((XImage*)surface)->height;
	return EX_TRUE;
}


int ExSetSurfacePixel(void* surface, unsigned int x, unsigned int y, unsigned long pixel){
    return XPutPixel((XImage*)surface, x,y, pixel);
}

void ExFillRect(ExSurface surface, ExRect* rect, unsigned int color){
	GC gc;
	ExRect mrect;

	if(!rect){
		ExGetSurfaceRect(surface, &mrect);
	}

	XAddPixel(surface,color);
	//XFillRectangle(display, m_window, gc,0,0,this->getWidth(),this->getHeight());
}
