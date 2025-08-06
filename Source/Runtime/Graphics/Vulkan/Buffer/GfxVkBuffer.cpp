#include "GfxVkBuffer.h"

#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>
#include <Runtime/Graphics/Vulkan/Device/GfxVkDevice.h>
#include <Runtime/Graphics/Vulkan/Util/VkMemoryUtils.h>
#include <Runtime/Graphics/Vulkan/Util/VkBufferUtils.h>

namespace Strand
{
	GfxVkBuffer::GfxVkBuffer(const GfxBufferDesc& desc, GfxDevice* pDevice) : GfxBuffer(desc, pDevice)
	{
		VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
		bufferInfo.size = desc.sizeInBytes;
		bufferInfo.usage = VkBufferUtils::GetVkBufferUsage(desc.usage);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VmaAllocationCreateInfo allocInfo{};
		allocInfo.usage = VmaUtils::GetVmaUsage(desc.memUsage);
		allocInfo.flags = VmaUtils::GetVmaFlags(desc.allocFlags);

		VDebug::VkAssert(vmaCreateBuffer(VmaAllocator(Root()->Allocator()), &bufferInfo, &allocInfo, 
			&m_buffer, &m_allocation, &m_allocationInfo), "GfxVkBuffer");

		vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice(Root()->Adapter()), &m_memProps);
	}

	GfxVkBuffer::~GfxVkBuffer()
	{
		if (m_buffer != VK_NULL_HANDLE)
		{
			vmaDestroyBuffer(VmaAllocator(Root()->Allocator()), m_buffer, m_allocation);
			m_buffer = VK_NULL_HANDLE;
			m_allocation = VK_NULL_HANDLE;
			m_allocationInfo.pMappedData = nullptr;
		}
	}

	void GfxVkBuffer::Update(const ReadArray<u8>& data)
	{
		Update((void*)data.Data(), data.SizeInBytes());
	}

	void GfxVkBuffer::Update(void* buffer, usize size)
	{
		u32 memoryTypeIndex = m_allocationInfo.memoryType;
		VkMemoryType memoryType = m_memProps.memoryTypes[memoryTypeIndex];
		VkMemoryPropertyFlags props = memoryType.propertyFlags;

		if (props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			if (m_allocationInfo.pMappedData)
			{
				std::memcpy(m_allocationInfo.pMappedData, buffer, size);
				if (!(props & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
				{
					VkMappedMemoryRange range = {};
					range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
					range.memory = m_allocationInfo.deviceMemory;
					range.offset = 0;
					range.size = size;
					VDebug::VkAssert(vkFlushMappedMemoryRanges(VkDevice(Root()->Device()), 1, &range), "GfxBuffer::Update");
				}
			}
			else
			{
				void* mapped = nullptr;
				VDebug::VkAssert(vmaMapMemory(VmaAllocator(Root()->Allocator()), m_allocation, &mapped), "GfxBuffer::Update");
				std::memcpy(mapped, buffer, size);

				if (!(props & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
				{
					VkMappedMemoryRange range = {};
					range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
					range.memory = m_allocationInfo.deviceMemory;
					range.offset = 0;
					range.size = size;
					vkFlushMappedMemoryRanges(VkDevice(Root()->Device()), 1, &range);
				}
				vmaUnmapMemory(VmaAllocator(Root()->Allocator()), m_allocation);
			}
		}
		else
			Log::Error(LogType::GraphicsAPI, "Buffer bind is not VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT. It needs staging buffer copy!");
	}

	void GfxVkBuffer::Map(const ReadArray<u8>& data)
	{
		Map((void*)data.Data(), data.SizeInBytes());
	}

	void GfxVkBuffer::Map(void* buffer, usize size)
	{
		if (m_allocationInfo.pMappedData)
		{
			Log::Error(LogType::GraphicsAPI, "GfxVkBuffer::Map - Buffer is reBAR (host visible + persistent). Mapping is not allowed.");
			return;
		}

		void* mapped = nullptr;
		VDebug::VkAssert(vmaMapMemory(VmaAllocator(Root()->Allocator()), m_allocation, &mapped), "GfxVkBuffer::Map");
		std::memcpy(mapped, buffer, size);

		u32 memoryTypeIndex = m_allocationInfo.memoryType;
		VkMemoryPropertyFlags props = m_memProps.memoryTypes[memoryTypeIndex].propertyFlags;

		if (!(props & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
		{
			VkMappedMemoryRange range{};
			range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			range.memory = m_allocationInfo.deviceMemory;
			range.offset = 0;
			range.size = size;

			VDebug::VkAssert(vkFlushMappedMemoryRanges(VkDevice(Root()->Device()), 1, &range), "GfxVkBuffer::Map::Flush");
		}
	}

	void GfxVkBuffer::Unmap()
	{
		if (m_allocationInfo.pMappedData)
		{
			Log::Error(LogType::GraphicsAPI, "GfxVkBuffer::Unmap - Buffer is reBAR (persistently mapped). Unmapping is not allowed.");
			return;
		}

		vmaUnmapMemory(VmaAllocator(Root()->Allocator()), m_allocation);
	}

	void* GfxVkBuffer::Buffer() const { return static_cast<void*>(m_buffer); }
}
