/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef FONT_SYSTEM_H
#define FONT_SYSTEM_H
#include"./../../EngineAssembly.h"
#ifdef INTERNAL_ENGINEX
	#include<ft2build.h>
	#include FT_FREETYPE_H
	#include<freetype\ftglyph.h>
	#pragma comment(lib, "freetype.lib")
#endif


struct ExGLFont{
	FT_Face ftFace;
	Uint size;
};
struct ExDxFont{
	FT_Face ftFace;
	Uint size;
};
struct ExFont{
	FT_Face ftFace;
	Uint size;
};

inline int next_p2(int n){int res = 1; while(res < n)res <<= 1; return res;} 
#define FOR(q,n) for(int q=0;q<n;q++)

#ifdef EX_CPP
C_EXTERN{
#endif
extern FT_Library ft_library;

//--------------------------------
DECLSPEC Int ELTAPIENTRY ExInitFontSystem(Void);

//--------------------------------
DECLSPEC Void ELTAPIENTRY ExShutDownFT(Void);
DECLSPEC ERESULT ELTAPIENTRY ExShutDownFT2(FT_Library ft_library);

DECLSPEC Int ELTAPIENTRY ExInitFont(const char* path, Uint size, FT_Face ftFace);

DECLSPEC Int ELTAPIENTRY ExCreateFontChar(Uint charIndex,FT_Face mftFace);


#ifdef EX_CPP
} 
#endif

#endif