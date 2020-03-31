#include "EntityCallRoomMgrBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_RoomMgrBase::EntityBaseEntityCall_RoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_RoomMgrBase::~EntityBaseEntityCall_RoomMgrBase()
{
}



EntityCellEntityCall_RoomMgrBase::EntityCellEntityCall_RoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_RoomMgrBase::~EntityCellEntityCall_RoomMgrBase()
{
}


}