#include "EntityCallRoleBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_RoleBase::EntityBaseEntityCall_RoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_RoleBase::~EntityBaseEntityCall_RoleBase()
{
}



EntityCellEntityCall_RoleBase::EntityCellEntityCall_RoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_RoleBase::~EntityCellEntityCall_RoleBase()
{
}


}