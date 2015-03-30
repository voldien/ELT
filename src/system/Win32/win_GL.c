#include"system/win/win_GL.h"

/*
DECLSPEC void ELTAPIENTRY ExInitExtension(ExWin hWnd,WindowContext deviContext,HGLRC hr){
	// temp variable
	HGLRC tempHRC = hr;PIXELFORMATDESCRIPTOR pfd;
	Int majorVer, minorVer;
	// get information
	Int attrib[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
	Int nResults[1] = {0};
	Int pixFmt = 1;

	if(wglGetPixelFormatAttribivARB(deviContext, pixFmt,0, 1, attrib, nResults))
		printf("This Hardware Supports %i PixelFormat.\n", *nResults);
	// Get Current OpenGL Version

	glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
	glGetIntegerv(GL_MINOR_VERSION, &minorVer);
	// version
	Int attribs[] ={
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef EX_DEBUG
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0
	};
	// print out OpenGL Version
	printf("OpenGL Version %i%i0.\n",majorVer,minorVer);


	Int dataSize;
	Int* pixAttribs = EX_NULL;
	// Create Context Attrib
	ExCreateContextAttrib(deviContext,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware


	Int pixelFormat[1];
	if(wglChoosePixelFormatARB(deviContext, &pixAttribs[0], NULL, 1, pixelFormat,(Uint*)&nResults[0]))
		printf("Succedded to Choose PixelFormat With the PixelFormat Number %i.\n",nResults[0]);


	if(!ExDestroyContext(deviContext,hrc))
		ExDevPrint("Failed to delete Temp OpenGL Context.\n");
	deviContext = GetDC(ExReConstructWindow(hWnd));


	if(SetPixelFormat(deviContext, pixelFormat[0], &pfd))
		printf("Succedded to Set PixelFormat With the PixelFormat Number %i.\n",nResults[0] );
	else
		wExDevPrintf(EX_TEXT("Failed to Set PixelFormat : %s \n"),ExGetErrorMessage(GetLastError()));

	// Create OpenGL Context ARB
	if(!(hrc = wglCreateContextAttribsARB(deviContext, EX_NULL,attribs))){
		ExDevPrintf("Failed to Create OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
		MessageBoxA(EX_NULL,  (LPCSTR)glewGetErrorString(glGetError()),"Error | OpenGL Context",MB_OK | MB_ICONERROR);
	}
	// Create a Shared OpenGL Context out of First Device Context
	if(ExIsEngineState(ENGINE_SHARE_RENDERCONTEXT))
		if(!(hrc2 = wglCreateContextAttribsARB(deviContext, hrc,attribs)))
			ExDevPrintf("Failed to Create Shared OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
	if(hr){ // hr valid
		// success
		wglMakeCurrent(NULL, NULL);
		wglMakeCurrent(deviContext, hrc);
	}
	free(pixAttribs);
	return;
}

DECLSPEC OpenGLContext ELTAPIENTRY ExCreateSharedGLContext(HDC openglHDC, OpenGLContext sharedHRC, WindowContext hDC){
	HGLRC hrc2;
	Int majorVer, minorVer;
	Int dataSize;
	Int nResults[1];
	Int* pixAttribs = EX_NULL;
	PIXELFORMATDESCRIPTOR pfd;

	// Create Context Attrib
	ExCreateContextAttrib(hDC,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware
	Int pixelFormat[1];
	if(!wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, pixelFormat,(Uint32*)&nResults[0]))
		ExDevGLPrintfc("Failed to Choose PixelFormat Number %i.\n",EX_CONSOLE_RED,nResults[0]);
	if(!SetPixelFormat(hDC, pixelFormat[0], &pfd))
		ExDevWindowPrintfc(EX_TEXT("Failed to Set PixelFormat Number %i.\n"),EX_CONSOLE_RED,nResults[0]);
	free(pixAttribs);

	glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
	glGetIntegerv(GL_MINOR_VERSION, &minorVer);
	Int attribs[] ={
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef EX_DEBUG
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0
	};
	if(!(hrc2 = wglCreateContextAttribsARB(hDC, sharedHRC,attribs))){
		ExDevPrintf("Failed to Create Shared OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
	}
	wglCopyContext(hrc, hrc2, GL_ALL_ATTRIB_BITS);
	wglShareLists(hrc, hrc2);
	return hrc2;
}

DECLSPEC Uint32 ELTAPIFASTENTRY ExGetGPUMemoryUsage(void){
	Int pvalue;
	glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX ,&pvalue);
	return pvalue;
}
DECLSPEC Int32 ELTAPIFASTENTRY ExMaxCombinedTexture(void){
	Int pvalue;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}
DECLSPEC Int32 ELTAPIFASTENTRY ExMaxTextureUints(void){
	Int pvalue;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}

*/