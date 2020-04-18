#pragma once
#include "Engine/KBECommon.h"
#include "Engine/AccountBase.h"



namespace KBEngine
{
	class Account :public AccountBase {

	public:
		Account();

		virtual ~Account();

		virtual void __init__() override;

		virtual void onDestroy() override;

		virtual void OnReqAccountInfo(uint16 arg1, uint64 arg2, uint64 arg3, uint64 arg4) override;

		virtual void OnReqRoleList(const ROLE_LIST& arg1) override;

		virtual void OnReqUnlockRole(uint8 arg1) override;

	public:
		//�����Ա��Ϣ�б�������
		ROLE_LIST RoleList;

	};
}