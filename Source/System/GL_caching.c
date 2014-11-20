#include"GL_caching.h"

TextureHandler textureCache = {0};

ENGINE_EX_DLL Void BROODAPI ExglClearColor(Float red, Float green, Float blue, Float alpha){
	glClearColor(red,green,blue,alpha);
}
ENGINE_EX_DLL Void BROODAPI ExglViewport(Int x,Int y, Int width, Int height){
	glViewport(x,y,width,height);
}
ENGINE_EX_DLL Void BROODAPI ExglColorMask(Float red, Float green, Float blue, Float alpha){
	glColorMask(red,green, blue, alpha);
}


ENGINE_EX_DLL Float BROODAPIFAST GetMaxTextureAnisotropy(Void){
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	return fLargest;
}
ENGINE_EX_DLL Void BROODAPIFAST ExBindTexture(Enum Target, Enum TextureID){
	if(CurrentTextureID == TextureID)return;
	else{
		glBindTexture(Target,TextureID);
		CurrentTextureID = TextureID;
	}
}

ENGINE_EX_DLL Void BROODAPIFAST ExBindTextureIndex(const Enum Target,const Enum TextureID,const Enum TextureIndex){
	if(textureCach.textureID[TextureIndex] == TextureID){
		return;
	}
	else{
		glActiveTexture(GL_TEXTURE0 + TextureIndex);
		glBindTexture(Target, TextureID);
		textureCach.textureID[TextureIndex] = TextureID;
		textureCach.textureIndex[TextureIndex] = TextureID;
	}
}