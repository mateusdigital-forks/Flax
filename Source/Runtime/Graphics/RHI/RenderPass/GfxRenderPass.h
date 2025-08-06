/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/RenderPass/GfxRenderPassDesc.h>

namespace Strand
{
	class GfxRenderPass : public GfxObject
	{
	public:
		GfxRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice);
		virtual ~GfxRenderPass() override = default;

		virtual void* Pass() const = 0;

	private:
		GfxRenderPassDesc m_desc;
	};
}
