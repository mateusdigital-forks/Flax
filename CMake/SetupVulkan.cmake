function(SetupVulkan TARGET)
	find_package(Vulkan REQUIRED)
	target_link_libraries(${TARGET} PRIVATE Vulkan::Vulkan)
	find_package(Vulkan OPTIONAL_COMPONENTS shaderc_combined)
	if(Vulkan_shaderc_combined_FOUND)
		target_link_libraries(${TARGET} PRIVATE Vulkan::shaderc_combined volk::volk)
	endif()
	
	target_include_directories(${TARGET} PUBLIC ${Vulkan_INCLUDE_DIR})

	if(WIN32)
		target_compile_definitions(${TARGET} PUBLIC VK_USE_PLATFORM_WIN32_KHR)
		target_compile_definitions(${TARGET} PUBLIC VK_NO_PROTOTYPES)
		set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
	endif()

endfunction()