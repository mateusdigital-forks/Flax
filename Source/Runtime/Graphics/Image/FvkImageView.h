/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/Image/FvkImage.h>
#include <vulkan/vulkan.h>

#include <vma/vk_mem_alloc.h>

namespace Flax
{
	struct ImageViewProps final
	{
		FvkImage* ownerImage = nullptr;
		VkImageViewType viewType = VK_IMAGE_VIEW_TYPE_2D;
		VkImageAspectFlags aspectFlag = VK_IMAGE_ASPECT_COLOR_BIT;
		u32 baseMipLevel = 0;
		u32 baseArrayLayer = 0;
	};

	class FvkImageView 
	{
	public:
		FvkImageView(const ImageViewProps& desc);
		~FvkImageView();

		inline VkImageView GetVkView() const { return m_view; }
		inline VkImage GetVkImage() const { return m_props.ownerImage->GetVkImage(); }
		inline VkFormat GetVkFormat() const { return m_props.ownerImage->GetFormat(); }
		inline const Math::Vec3u& GetSize() const { return m_props.ownerImage->GetSize(); }

		inline FvkImage* GetImage() const { return m_props.ownerImage; }
		inline VkImageViewType GetType() const { return m_props.viewType; }
		inline VkImageAspectFlags GetAspect() const { return m_props.aspectFlag; }
		inline u32 GetBaseMipLevel() const { return m_props.baseMipLevel; }
		inline u32 GetBaseArrayLayer() const { return m_props.baseArrayLayer; }

	private:
		ImageViewProps m_props;

		VkImageView m_view;
	};
}