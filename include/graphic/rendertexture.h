/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_RENDER_TEXTURE_H_
#define _ELT_RENDER_TEXTURE_H_ 1
#include"texture.h"
#include"../ExCommon.h"

#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

typedef struct ex_frame_buffer{
	/**/
	ExTexture texture;
	unsigned int framebuffer;
	unsigned int attachment;
}ExFrameBuffer,ExRenderTexture;

typedef struct ex_render_buffer{
	/**/
	unsigned int renderbuffer;
}ExRenderBuffer;



/*	TODO resolve the issues with the parameters.*/
extern ExFrameBuffer* ExCreateRenderTexture2D(ExFrameBuffer* texture, unsigned int width, unsigned int height, unsigned int attachment);
extern void ExDestroyRenderTexture(ExFrameBuffer* framebuffer);
extern ExBoolean ExIsFramebuffer(ExFrameBuffer* framebuffer);
extern void ExBindRenderTexture(ExFrameBuffer* framebuffer);


extern ExFrameBuffer* ExFrameBufferAddTextureAttachment(ExFrameBuffer* framebuffer, unsigned int attachment, ExTexture* texture);
extern ExFrameBuffer* ExFrameBufferAddRenderBuffer(ExFrameBuffer* framebuffer, unsigned int attachment, ExRenderBuffer* texture);



extern void ExCreateRenderBuffer(ExRenderBuffer* renderbuffer);
extern ExBoolean ExIsRenderBuffer(ExRenderBuffer* renderbuffer);
extern void ExRenderBufferSize(ExRenderBuffer* renderbuffer, ExSize* size, unsigned int format);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif



#endif
