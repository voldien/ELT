#include"system/win/win_directX.h"
#if (defined(EX_VC) || defined(EX_WINDOWS)) && defined(EX_INCLUDE_DIRECTX)
#include"./../elt_win.h"
#ifdef INTERNAL_ENGINEX
	//#include<D3dx9tex.h>
	#include<d3d9.h>
	#pragma comment(lib, "D3d9.lib")
#endif

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 directDevice = NULL;

DECLSPEC void* ELTAPIFASTENTRY ExGetD3D(void){return d3d;}
DECLSPEC void* ELTAPIFASTENTRY ExGetDirect3D(void){return directDevice;}

DECLSPEC ERESULT ELTAPIENTRY ExInitDirectX(ExWin window){
	ERESULT hresult = 0;
	size_t win_size[2];
	D3DCAPS9 m_d3dDevCaps;
	D3DPRESENT_PARAMETERS d3StructInfo = {0};
	// make sure the
	/**
		modular needed for directx
	*/
	if(!GetModuleHandle(EX_TEXT("D3d9.dll")))
		if(!ExLoadLibrary(EX_TEXT("D3d9.dll")))return E_ABI_ERROR;
	if(!GetModuleHandle(EX_TEXT("Gdi32.dll")))
		if(!ExLoadLibrary(EX_TEXT("Gdi32.dll")))return E_ABI_ERROR;


	if(!d3d){// if d3d hasn't been created
		if(!(d3d = Direct3DCreate9(D3D_SDK_VERSION)))
			return E_FAILURE;
	}
	ExGetWindowSizev(window,(exsize*)&win_size[0]);
	if(FAILED(hresult = d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3dDevCaps))){
		//wExDevPrintf(EX_TEXT("Failed to Get DirectX 9 developer compadbility"), ExGetHResultErrorMessage(hresult));
	}
	Int vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	if(m_d3dDevCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// Support HardWare ShaderModel.
	}
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// Emulate the ShaderModel.


	memset(&d3StructInfo,0, sizeof(d3StructInfo));
	d3StructInfo.Windowed = TRUE;
	//d3StructInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	d3StructInfo.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3StructInfo.hDeviceWindow = window;
	d3StructInfo.BackBufferWidth = win_size[0];
	d3StructInfo.BackBufferHeight = win_size[1];
	//d3StructInfo.BackBufferFormat = ((ExGetEngineDescriptionPointer()->PixelType & ENGINE_RGBA) != 0) ? D3DFMT_X8R8G8B8 :
	//	((ExGetEngineDescriptionPointer()->PixelType &  ENGINE_RGB) != 0) ?  D3DFMT_R8G8B8 : D3DFMT_UNKNOWN;

	/*d3StructInfo.BackBufferCount = (ExGetEngineDescriptionPointer()->EngineFlag & ENGINE_SUPPORT_DOUBLEBUFFER) != 0 ? 2 : 1;
	d3StructInfo.MultiSampleQuality = ExGetEngineDescriptionPointer()->SampleQuality;
	d3StructInfo.FullScreen_RefreshRateInHz = (engineDescription.EngineFlag & ENGINE_FULLSCREEN) ? 0 : 0;*/
	d3StructInfo.EnableAutoDepthStencil = TRUE;
	d3StructInfo.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3StructInfo.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	if(FAILED(hresult = d3d->CreateDevice(D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,		// HARDWARE ACCELERATION
							window,				// Window Handle
							vp,					// Behavior Flag (Software or Hardware Acceleration)
							&d3StructInfo,		// D3DirectX struct
							&directDevice))){	//
								ExIsDXError(hresult);
	}
	return (hresult == S_OK) ? (ERESULT)d3d : 0;
}

DECLSPEC void ELTAPIENTRY ExReleaseDirectX(void){
	if(d3d)
		if(FAILED(d3d->Release()))
			ExDevPrintf("Failed to Release D3D");
	if(directDevice)
		if(FAILED(directDevice->Release()))
			ExDevPrintf("Failed to Release D3D");
}

DECLSPEC void ELTAPIFASTENTRY ExDirectXBegin(void){
	directDevice->BeginScene();
}
DECLSPEC void ELTAPIFASTENTRY ExDirectXEnd(void){
	directDevice->EndScene();
}
DECLSPEC void ELTAPIFASTENTRY ExDirectXPresent(void){
	directDevice->Present(0,0,0,0);
}

#endif
