#include"system/elt_vulkan.h"
#define VK_USE_PLATFORM_XLIB_KHR
#include<vulkan/vulkan.h>
#include<vulkan/vk_layer.h>

VkInstance instance = NULL;


ExVulkanContext ExCreateVulkanContext(ExWin window, ExVulkanContext share){
	int x = 0;
	VkResult results;
	uint32_t pPhysicalDeviceCount;
	VkPhysicalDevice pPhysicalDevice[10];
	VkPhysicalDeviceFeatures features;
	VkDevice device;
	ExChar application[255];

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

    return device;
}



ExVulkanContext ExCreateVulkanShareContext(ExVulkanContext share){
	return ExCreateVulkanContext(0, share);
}

