#include "EntityCallERoomBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ERoomBase::EntityBaseEntityCall_ERoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ERoomBase::~EntityBaseEntityCall_ERoomBase()
{
}



EntityCellEntityCall_ERoomBase::EntityCellEntityCall_ERoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ERoomBase::~EntityCellEntityCall_ERoomBase()
{
}


}