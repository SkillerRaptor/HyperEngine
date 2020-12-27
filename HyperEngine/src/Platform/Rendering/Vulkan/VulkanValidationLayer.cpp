#include "VulkanValidationLayer.hpp"

#include <iostream>
#include <cstring>

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

namespace Hyperion
{
	VulkanValidationLayer::VulkanValidationLayer(VkInstance& instance, VulkanValidationLayerInfo& validationLayerInfo)
		: m_Instance(instance), m_ValidationLayerInfo(validationLayerInfo)
	{
#ifdef HP_DEBUG
		m_ValidationLayerInfo.ValidationLayersEnabled = true;
#endif
		if (m_ValidationLayerInfo.ValidationLayersEnabled && !CheckValidationLayerSupport())
		{
			std::cout << " Validation Layers requested, but not available!" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	void VulkanValidationLayer::SetupInstanceDebugger(VkInstanceCreateInfo& instanceCreateInfo, VkDebugUtilsMessengerCreateInfoEXT& debugInstanceMessengerCreateInfo)
	{
		if (!m_ValidationLayerInfo.ValidationLayersEnabled)
			return;
		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayerInfo.ValidationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames = m_ValidationLayerInfo.ValidationLayers.data();

		debugInstanceMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugInstanceMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugInstanceMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugInstanceMessengerCreateInfo.pfnUserCallback = DebugCallback;
		instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugInstanceMessengerCreateInfo;
	}

	void VulkanValidationLayer::SetupValidationDebugger()
	{
		if (!m_ValidationLayerInfo.ValidationLayersEnabled)
			return;
		VkDebugUtilsMessengerCreateInfoEXT debugValidationMessengerCreateInfo{};
		debugValidationMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugValidationMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugValidationMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugValidationMessengerCreateInfo.pfnUserCallback = DebugCallback;
		debugValidationMessengerCreateInfo.pUserData = nullptr;

		if (CreateDebugUtilsMessengerEXT(m_Instance, &debugValidationMessengerCreateInfo, nullptr, &m_ValidationLayerInfo.DebugMessenger) != VK_SUCCESS)
		{
			std::cout << " Failed to setup the Debug Messenger!" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	void VulkanValidationLayer::Shutdown()
	{
		if (m_ValidationLayerInfo.ValidationLayersEnabled)
			DestroyDebugUtilsMessengerEXT(m_Instance, m_ValidationLayerInfo.DebugMessenger, nullptr);
	}

	bool VulkanValidationLayer::CheckValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_ValidationLayerInfo.ValidationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}

			if (!layerFound)
				return false;
		}
		return true;
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
	std::cerr << " | - Validation Layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}
