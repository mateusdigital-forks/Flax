/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Framebuffer/GfxFramebuffer.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkFramebuffer final : public GfxFramebuffer
	{
	public:
		GfxVkFramebuffer(const GfxFramebufferDesc& desc, GfxDevice* pDevice);
		~GfxVkFramebuffer() override final;

		void* Framebuffer(usize index = 0) const override final;
		void Resize(const Math::Vec3u& size) override final;

	private:
		Vector<VkFramebuffer> m_framebuffers;
	};
}
