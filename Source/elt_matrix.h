/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef MATRICES_H
#define MATRICES_H
#include"System/elt_gl.h"
#ifdef EX_WINDOWS
	#include"System/Win32/win_directX.h"
#endif

#ifndef MODELVIEW
#define MODELVIEW 0x1
#endif
#ifndef VIEW
#define VIEW 0x2
#endif
#ifndef PROJECTION 
#define PROJECTION 0x4
#endif

#if defined(EX_INCLUDE_DIRECTX) && defined(WOW_)
#ifdef EX_CPP
extern "C"{
#endif
// DirectX Matrix Function
extern DECLSPEC Void ELTAPIENTRY DXLoadIdentity(const Enum MatrixMode);
extern DECLSPEC Void ELTAPIENTRY DXTranslatef(Float x, Float y, Float z);
extern DECLSPEC Void ELTAPIENTRY DXScalef(Float x, Float y, Float z);
extern DECLSPEC Void ELTAPIENTRY DXRotate(Float Angle, Float x, Float y,Float z);
extern DECLSPEC Void ELTAPIENTRY DXRotateQ(const quat_t rotation);
extern DECLSPEC Void ELTAPIENTRY DXOrth(Float Left, Float Right,  Float Bottom, Float Top, Float Near,Float Far);
extern DECLSPEC Void ELTAPIENTRY DXPushMatrix(Void);
extern DECLSPEC Void ELTAPIENTRY DXPopMatrix(Void);
extern DECLSPEC Void ELTAPIENTRY DXMatrixMode(Enum MatrixMode);
extern DECLSPEC Void ELTAPIENTRY DXPerspective(Float Fov, Float Aspect, Float Far, Float Near);
extern DECLSPEC Void ELTAPIENTRY DXLoadMatrix(const Float* mat);
extern DECLSPEC Void ELTAPIENTRY DXGetMatrix(const Enum matrixMode, Float* matrixf);
//extern DECLSPEC Void ELTAPIENTRY MatrixMode(Enum matrixMode);
}
#endif

#ifdef EX_CPP

#endif

#ifndef NOFIXEPIPELINEMATRIX
	#if(GRAPHICDEVICE == OPENGL)
	#define fMatrixMode MatrixMode
	#define fPopMatrix glPopMatrix
	#define fLoadIdentity glLoadIdentity
	#define fPushMatrix glPushMatrix
	#define fPerspective gluPerspective
	#define fOrth glOrtho
	#define fTranslatef glTranslatef
	#define fScalef glScalef
	#define fRotatef glRotatef
	#define fLoadMatrix glLoadMatrixf
	#define fGetMatrix glGetFloatv
	#elif(GRAPHICDEVICE == DIRECTX)
	#define fMatrixMode DXMatrixMode
	#define fLoadIdentity DXLoadIdentity
	#define fPopMatrix  DXPopMatrix
	#define fPushMatrix DXPushMatrix
	#define fPerspective DXPerspective 
	#define fOrth DXOrth
	#define fTranslatef  DXTranslatef
	#define fScalef	DXScalef
	#define fRotatef DXRotate
	#define fLoadMatrix DXLoadMatrix
	#define fGetMatrix DXGetMatrix
	#endif
#else
	// No Support for Fixed PipeLine Matrix
	#define fMatrixMode(mode) ((void)0)
	#define fPopMatrix ((void)0)
	#define fLoadIdentity ((void)0)
	#define fPushMatrix ((void)0)
	#define fPerspective(fovy, aspect, near, far) ((void)0)
	#define fOrth(left, right, bottom,top, near,far) ((void)0)
	#define fTranslatef(x,y,z) ((void)0)
	#define fScalef(x,y,z) ((void)0)
	#define fRotatef(angle,x,y,z) ((void)0)
	#define fLoadMatrix(mat) ((void)0)
	#define fGetMatrix(pname, params) ((void)0)
#endif
#endif