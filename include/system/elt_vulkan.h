/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _ELT_VULKAN_H_
#define _ELT_VULKAN_H_ 1
#include"./../elt_def.h"
#include"./../window.h"

typedef void* ExVulkanContext;
typedef void* ExVulkanQueue;
typedef void* ExCommandBuffer;
typedef void* ExVulkanDevice;

#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif


/*
 *
 */
extern ELTDECLSPEC ExVulkanDevice ELTAPIENTRY ExCreateVulkanContext(ExWin window, ExVulkanContext share);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyVulkanContext(ExVulkanContext vulkan);


extern ELTDECLSPEC ExVulkanContext ELTAPIENTRY ExCreateVulkanShareContext(ExVulkanContext share);

extern ELTDECLSPEC ExVulkanQueue ELTAPIENTRY ExCreateVulkanQueue(ExVulkanContext vulkan);
extern ELTDECLSPEC void* ELTAPIENTRY ExCreateVulkanCommandBuffer(ExVulkanContext vulkan);
extern ELTDECLSPEC void* ELTAPIENTRY ExCreateVulkanSwapChain(ExVulkanContext vulkan);


extern ELTDECLSPEC int ELTAPIENTRY ExGetVulkanVersion(void);
extern ELTDECLSPEC int ELTAPIENTRY ExGetVulkanShadVersioin(void);


#ifdef __cplusplus	/*	C++ environment	*/
}
#endif


#endif
