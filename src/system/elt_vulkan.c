#include"system/elt_vulkan.h"
#define VK_USE_PLATFORM_XLIB_KHR
#include<vulkan/vulkan.h>
#include<vulkan/vk_layer.h>
#include<vulkan/vk_platform.h>

VkInstance instance = NULL;

ExVulkanDevice ExCreateVulkanContext(ExWin window, ExVulkanContext share){
	int x = 0;
	VkResult results;
	uint32_t pPhysicalDeviceCount;
	VkPhysicalDevice pPhysicalDevice[10];
	VkPhysicalDeviceFeatures features;
	VkDevice device;
	ExChar application[255];
	VkAllocationCallbacks callbacks;

	callbacks.pUserData = NULL;
	callbacks.pfnFree = free;
	callbacks.pfnInternalFree = free;
	callbacks.pfnAllocation = malloc;
	callbacks.pfnReallocation = realloc;


    const char* extension[] = {
    		VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#ifdef EX_DEBUG
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME
#endif
    };

    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = ExGetApplicationName(application, sizeof(application));
	app_info.applicationVersion = VK_MAKE_VERSION(EX_VERSION_MAJOR, EX_VERSION_MINOR, EX_VERSION_REVISION);
	app_info.pEngineName = ExGetApplicationName(application, sizeof(application));
	app_info.engineVersion = VK_MAKE_VERSION(EX_VERSION_MAJOR, EX_VERSION_MINOR, EX_VERSION_REVISION);
	app_info.apiVersion = VK_API_VERSION;

	VkInstanceCreateInfo instance_info = {0};
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pApplicationInfo = &app_info;
	instance_info.flags = 0;
	instance_info.enabledLayerCount = 0;
	instance_info.ppEnabledLayerNames = NULL;
	instance_info.enabledExtensionCount = sizeof(extension) / sizeof(extension[0]);//(uint32_t)global_extensions_.size();
	instance_info.ppEnabledExtensionNames = extension;//global_extensions_.data();


    results = vkCreateInstance(&instance_info, 0, &instance);
    if(results != VK_SUCCESS){
    	return NULL;
    }

    results = vkEnumeratePhysicalDevices(instance, &pPhysicalDeviceCount, NULL);
    if(results != VK_SUCCESS){
    	return NULL;
    }


    results = vkEnumeratePhysicalDevices(instance, &pPhysicalDeviceCount, pPhysicalDevice);

	for(x = 0; x < pPhysicalDeviceCount; x++){
		vkGetPhysicalDeviceFeatures(pPhysicalDevice[x], &features);
	}

    VkQueueFamilyProperties queueProps[10];
    int graphicsQueueIndex = 0;
    int queueCount;
    vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice[0], &queueCount, NULL);
    vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice[0], &queueCount, &queueProps[0]);
    for (graphicsQueueIndex = 0; graphicsQueueIndex < queueCount; graphicsQueueIndex++){
		if (queueProps[graphicsQueueIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			break;
	}


	VkDeviceQueueCreateInfo queueInfo = {0};
	queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueInfo.queueFamilyIndex = graphicsQueueIndex;
	queueInfo.queueCount = 1;
	queueInfo.pQueuePriorities = queueProps;

    VkDeviceCreateInfo pCreateInfo = {0};
    pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    pCreateInfo.pNext = NULL;
    pCreateInfo.queueCreateInfoCount = 1;
    pCreateInfo.pQueueCreateInfos = &queueInfo;
    pCreateInfo.pEnabledFeatures = NULL;

    results = vkCreateDevice(pPhysicalDevice[0], &pCreateInfo, NULL, &device);
    if(results != VK_SUCCESS){
    	return NULL;
    }

    VkPhysicalDeviceMemoryProperties memProp;
    vkGetPhysicalDeviceMemoryProperties(pPhysicalDevice[0], &memProp);


    VkCommandPoolCreateInfo cmd_pool_info = {};
    cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_pool_info.pNext = NULL;



    VkSurfaceKHR surface;
    VkXlibSurfaceCreateInfoKHR surfaceCreateInfo = {};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    surfaceCreateInfo.dpy = display;
    surfaceCreateInfo.window = window;
    results = vkCreateXlibSurfaceKHR(instance, &surfaceCreateInfo, NULL, &surface);

    vkCreateSwapchainKHR(device, NULL, 0, 0);


    /*
    VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = NULL;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapChain;
	presentInfo.pImageIndices = &currentBuffer;
    vkQueuePresentKHR(queue, &presentInfo);

    */
    return device;
}


void ExDestroyVulkanContext(ExVulkanContext vulkan){
	if(!vulkan)
		return;

	VkDevice device = vulkan;

	vkDestroyDevice(vulkan, NULL);
}



ExVulkanContext ExCreateVulkanShareContext(ExVulkanContext share){
	return ExCreateVulkanContext(0, share);
}

ExVulkanQueue ExCreateVulkanQueue(ExVulkanContext vulkan){

}

void* ExCreateVulkanCommandBuffer(ExVulkanContext vulkan){
	VkResult result;
	VkCommandPool pool;
	VkCommandPoolCreateInfo cmdPoolCreateInfo = {0};
	cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolCreateInfo.pNext = NULL;
	cmdPoolCreateInfo.queueFamilyIndex = 0;
	cmdPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	result = vkCreateCommandPool(vulkan, &cmdPoolCreateInfo, NULL, &pool);

	VkCommandBufferAllocateInfo alloc = {0};
	alloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc.commandBufferCount = 1;
	alloc.commandPool = pool;
	alloc.level = 1;
	alloc.pNext = NULL;


	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(vulkan, &alloc, &commandBuffer);
	return commandBuffer;
}

void* ExCreateVulkanSwapChain(ExVulkanContext vulkan){
	VkSwapchainKHR chain;
	VkSwapchainCreateInfoKHR chainAlloc;
	chainAlloc.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;


	vkCreateSwapchainKHR(vulkan, &chainAlloc, NULL, NULL);
}






int ExGetVulkanVersion(void){

}

