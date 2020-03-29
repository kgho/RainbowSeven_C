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



EntityCellEntityCall_AccountBase::EntityCellEntityCall_AccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_AccountBase::~EntityCellEntityCall_AccountBase()
{
}

void EntityCellEntityCall_AccountBase::Say(const FString& arg1)
{
	Bundle* pBundleRet = newCall("Say", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}


}