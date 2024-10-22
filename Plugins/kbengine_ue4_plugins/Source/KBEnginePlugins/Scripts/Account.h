﻿#pragma once
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

		virtual void OnReqAccountInfo(const FString& arg1, uint16 arg2, uint64 arg3, uint64 arg4, uint64 arg5) override;

		virtual void OnReqRoleInfo(const ROLE_INFO& arg1) override;

		virtual void OnReqRoleList(const ROLE_LIST& arg1) override;

		virtual void OnReqUnlockRole(uint8 arg1, uint8 arg2) override;

		void OnReqRoomList(const ROOM_LIST& arg1);

		void OnReqCreateRoom(uint8 arg1, const ROOM_INFO& arg2) override;

		virtual void OnReqEnterRoom(uint8 arg1, const PLAYER_LIST& arg2, const PLAYER_LIST& arg3)  override;

		virtual void OnReqLeaveRoom(uint8 arg1) override;

		virtual void OnReqChangeState(uint8 arg1) override;

		virtual void OnReqSelectRole(uint8 arg1, uint8 arg2) override;

		virtual void OnAllReady(uint8 arg1) override;

		virtual void OnReqEnterGame(uint8 arg1) override;

		virtual void OnReqStartGame(uint8 arg1) override;

	public:
		//保存干员信息列表到本地
		ROLE_LIST RoleList;

		// 名称
		FString accountName;
	};
}