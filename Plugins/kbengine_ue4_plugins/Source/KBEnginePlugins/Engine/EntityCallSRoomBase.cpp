#include "EntityCallSRoomBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SRoomBase::EntityBaseEntityCall_SRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SRoomBase::~EntityBaseEntityCall_SRoomBase()
{
}



EntityCellEntityCall_SRoomBase::EntityCellEntityCall_SRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SRoomBase::~EntityCellEntityCall_SRoomBase()
{
}


}