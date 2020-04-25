#pragma once

#include "Engine/KBECommon.h"
#include "Engine/RoleBase.h"

namespace KBEngine
{
	class Role :public RoleBase
	{
	public:
		Role();
		virtual ~Role();
		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;

		virtual void onBaseHPChanged(int16 oldValue) override;

		virtual void onHPChanged(int16 oldValue) override;

	};
}