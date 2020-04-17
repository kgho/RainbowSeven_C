#include "EntityCallAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_AccountBase::EntityBaseEntityCall_AccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_AccountBase::~EntityBaseEntityCall_AccountBase()
{
}

void EntityBaseEntityCall_AccountBase::ReqAccountInfo()
{
	Bundle* pBundleRet = newCall("ReqAccountInfo", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::ReqRoleList()
{
	Bundle* pBundleRet = newCall("ReqRoleList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::ReqUnlockole(uint8 arg1)
{
	Bundle* pBundleRet = newCall("ReqUnlockole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_AccountBase::EntityCellEntityCall_AccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_AccountBase::~EntityCellEntityCall_AccountBase()
{
}


}