#include "RoleBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void RoleBase::onComponentsEnterworld()
{
}

void RoleBase::onComponentsLeaveworld()
{
}

void RoleBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_RoleBase(id(), className());
}

void RoleBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_RoleBase(id(), className());
}

void RoleBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* RoleBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* RoleBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void RoleBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void RoleBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Role");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 2:
			{
				FString oldval_Name = Name;
				Name = stream.readUnicode();

				if(pProp->isBase())
				{
					if(inited())
						onNameChanged(oldval_Name);
				}
				else
				{
					if(inWorld())
						onNameChanged(oldval_Name);
				}

				break;
			}
			case 3:
			{
				uint8 oldval_RoleType = RoleType;
				RoleType = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onRoleTypeChanged(oldval_RoleType);
				}
				else
				{
					if(inWorld())
						onRoleTypeChanged(oldval_RoleType);
				}

				break;
			}
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void RoleBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Role"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	FString oldval_Name = Name;
	Property* pProp_Name = pdatas[4];
	if(pProp_Name->isBase())
	{
		if(inited() && !inWorld())
			onNameChanged(oldval_Name);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Name->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onNameChanged(oldval_Name);
			}
		}
	}

	uint8 oldval_RoleType = RoleType;
	Property* pProp_RoleType = pdatas[5];
	if(pProp_RoleType->isBase())
	{
		if(inited() && !inWorld())
			onRoleTypeChanged(oldval_RoleType);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_RoleType->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onRoleTypeChanged(oldval_RoleType);
			}
		}
	}

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

RoleBase::RoleBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	Name(TEXT("")),
	RoleType((uint8)FCString::Atoi64(TEXT("0")))
{
}

RoleBase::~RoleBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void RoleBase::attachComponents()
{
}

void RoleBase::detachComponents()
{
}

}