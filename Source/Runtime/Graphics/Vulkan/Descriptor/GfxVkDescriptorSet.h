/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorSet.h>

#include <vulkan/vulkan.h >

namespace Strand
{
	class GfxVkDescriptorSet : public GfxDescriptorSet
	{
	public:
		GfxVkDescriptorSet(const GfxDescriptorSetDesc& desc, GfxDevice* pDevice);
		~GfxVkDescriptorSet() override final;

		void* DescSet() const override final;
		void Update(const GfxSetUpdateDesc& update) const override final;

	private:
		VkDescriptorSet m_set;
	};
}
