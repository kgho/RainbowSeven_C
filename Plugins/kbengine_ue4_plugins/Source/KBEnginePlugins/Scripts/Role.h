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
	};
}