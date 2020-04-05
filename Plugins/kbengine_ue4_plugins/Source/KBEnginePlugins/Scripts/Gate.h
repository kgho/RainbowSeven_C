#pragma once
#include "Engine/KBECommon.h"
#include "Engine/GateBase.h"
namespace KBEngine
{
	class Gate :public GateBase {
	public:
		Gate();
		virtual ~Gate();
	public:
		virtual void __init__() override;
		virtual void onDestroy() override;
	};
}