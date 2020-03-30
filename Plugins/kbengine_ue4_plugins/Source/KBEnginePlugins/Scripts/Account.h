#pragma once
#include "Engine/KBECommon.h"
#include "Engine/AccountBase.h"
namespace KBEngine
{
	class Account :public AccountBase {
	public:
		Account();
		virtual ~Account();
	public:
		virtual void __init__() override;
		virtual void onDestroy() override;
		virtual void OnSay(const CHAT_INFO& arg1) override;
	};
}