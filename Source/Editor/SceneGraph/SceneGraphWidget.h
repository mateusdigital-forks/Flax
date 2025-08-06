/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Strand
{
	class SceneGraphTreeView;
	class SceneGraphModel;

	class SceneGraphWidget : public QWidget
	{
		Q_OBJECT
	public:
		SceneGraphWidget(QWidget* pParent = nullptr);
		~SceneGraphWidget();

	private:
		SceneGraphTreeView* m_treeView;
		SceneGraphModel* m_sgModel;
	};
}
