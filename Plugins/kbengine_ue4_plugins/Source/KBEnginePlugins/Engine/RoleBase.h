/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class Role : public RoleBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "EntityCallRoleBase.h"

namespace KBEngine
{

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/Role.def
	// Please inherit and implement "class Role : public RoleBase"
class KBENGINEPLUGINS_API RoleBase : public Entity
{
public:
	EntityBaseEntityCall_RoleBase* pBaseEntityCall;
	EntityCellEntityCall_RoleBase* pCellEntityCall;

	FString Name;
	virtual void onNameChanged(const FString& oldValue) {}
	uint8 RoleType;
	virtual void onRoleTypeChanged(uint8 oldValue) {}


	void onComponentsEnterworld() override;
	void onComponentsLeaveworld() override;

	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;


	void onRemoteMethodCall(MemoryStream& stream) override;
	void onUpdatePropertys(MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	RoleBase();
	virtual ~RoleBase();

	void attachComponents() override;
	void detachComponents() override;

};

}