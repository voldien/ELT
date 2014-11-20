/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef GL_CACHING_H
#define GL_CACHING_H
#include<Cmd/cmdlib.h>
#include<Cmd/mathlib.h>
#include<gl/glew.h>


#define EX_CACHED_TEXTURE_COUNT 32
struct TextureHandler{
	BYTE textureIndex[EX_CACHED_TEXTURE_COUNT];
	Ushort textureID[EX_CACHED_TEXTURE_COUNT];
};
extern TextureHandler textureCache;
extern Float glClearColorCache[4];
extern Int32 glViewportCache[4];
extern Boolean glColorMaskCach[4];

extern DECLSPEC Void ELTAPIENTRY ExglClearColor(Float red, Float green, Float blue, Float alpha);
extern DECLSPEC Void ELTAPIENTRY ExglViewport(Int x,Int y, Int width, Int height);
extern DECLSPEC Void ELTAPIENTRY ExglColorMask(Float red, Float green, Float blue, Float alpha);


/*
	Get Max Texture Anisotropy for this hardware.
*/
extern DECLSPECFloat ELTAPIFASTENTRY GetMaxTextureAnisotropy(Void);
extern DECLSPECVoid ELTAPIFASTENTRY ExBindTexture(Enum Target, Enum TextureID);
/*
	Bind Texture By Target Of Texture, Texture Activec Index, TextureID
	Cach Current Texture State for performance. 
*/
extern DECLSPEC Void ELTAPIFASTENTRY ExBindTextureIndex(const Enum Target,const Enum TextureID,const Enum TextureIndex);

#endif