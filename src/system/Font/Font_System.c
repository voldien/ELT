#include"Font_System.h"

using namespace std;
FT_Library ft_library = NULL;
DECLSPEC Int ELTAPIENTRY ExInitFontSystem(Void){
	if(!FT_Init_FreeType(&ft_library)){
		return TRUE;
	}
	else{
		ExDevPrintf("Failed to Initilize FreeType\n");
		return FALSE;
	}
}
DECLSPEC Void ELTAPIENTRY ExShutDownFT(Void){
	if(!ft_library)return;
	// free the FreeType Library 
	if(FT_Done_FreeType(ft_library) != 0){
		ExDevPrint("Failed to Release FreeType");
	}
	return;
}

DECLSPEC Int ELTAPIENTRY ExInitFont(const char* path, Uint size, FT_Face mftFace){
	if(ft_library == NULL){
		return -1;
	}
	Int error = FT_New_Face(ft_library, path,0,&mftFace);
	if(error){
		return FALSE;
	}
	FT_Set_Pixel_Sizes(mftFace,size,size);

	for(Uint x = 0; x < 128; x++){
		ExCreateFontChar(x,mftFace);
		continue;
	}
	return 1;
}

DECLSPEC Int ELTAPIENTRY ExCreateFontChar(Uint iIndex,FT_Face mftFace){
	FT_Load_Glyph(mftFace, FT_Get_Char_Index(mftFace, iIndex), FT_LOAD_DEFAULT); 

   FT_Render_Glyph(mftFace->glyph, FT_RENDER_MODE_NORMAL); 
   FT_Bitmap* pBitmap = &mftFace->glyph->bitmap; 

   int iW = pBitmap->width, iH = pBitmap->rows; 
   int iTW = next_p2(iW), iTH = next_p2(iH); 

   Uint8* bData = new Uint8[iTW*iTH]; 
   // Copy glyph data and add dark pixels elsewhere
   FOR(ch, iTH)FOR(cw, iTW) 
      bData[ch*iTW+cw] = (ch >= iH || cw >= iW) ? 0 : pBitmap->buffer[(iH-ch-1)*iW+cw]; 
  
   // And create a texture from it
   /*
   tCharTextures[iIndex].createFromData(bData, iTW, iTH, 16, GL_DEPTH_COMPONENT, false); 
   tCharTextures[iIndex].setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR); 

   tCharTextures[iIndex].setSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
   tCharTextures[iIndex].setSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
   tCharTextures[iIndex].setSamplerParameter(GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE); 

   // Calculate glyph data
   iAdvX[iIndex] = ftFace->glyph->advance.x>>6; 
   iBearingX[iIndex] = ftFace->glyph->metrics.horiBearingX>>6; 
   iCharWidth[iIndex] = ftFace->glyph->metrics.width>>6; 

   iAdvY[iIndex] = (ftFace->glyph->metrics.height - ftFace->glyph->metrics.horiBearingY)>>6; 
   iBearingY[iIndex] = ftFace->glyph->metrics.horiBearingY>>6; 
   iCharHeight[iIndex] = ftFace->glyph->metrics.height>>6; 

   iNewLine = max(iNewLine, int(ftFace->glyph->metrics.height>>6)); 

   // Rendering data, texture coordinates are always the same, so now we waste a little memory
   glm::vec2 vQuad[] = 
   { 
      glm::vec2(0.0f, float(-iAdvY[iIndex]+iTH)), 
      glm::vec2(0.0f, float(-iAdvY[iIndex])), 
      glm::vec2(float(iTW), float(-iAdvY[iIndex]+iTH)), 
      glm::vec2(float(iTW), float(-iAdvY[iIndex])) 
   }; 
   glm::vec2 vTexQuad[] = {glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}; 

   // Add this char to VBO
   FOR(i, 4) 
   { 
      vboData.addData(&vQuad[i], sizeof(glm::vec2)); 
      vboData.addData(&vTexQuad[i], sizeof(glm::vec2)); 
   } */
   delete[] bData;
	return TRUE;
}