#include "AccountBase.h"
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



void AccountBase::onComponentsEnterworld()
{
}

void AccountBase::onComponentsLeaveworld()
{
}

void AccountBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_AccountBase(id(), className());
}

void AccountBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_AccountBase(id(), className());
}

void AccountBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* AccountBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* AccountBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void AccountBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Account");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 4:
		{
			uint16 OnReqAccountInfo_arg1 = stream.readUint16();
			uint64 OnReqAccountInfo_arg2 = stream.readUint64();
			uint64 OnReqAccountInfo_arg3 = stream.readUint64();
			uint64 OnReqAccountInfo_arg4 = stream.readUint64();
			OnReqAccountInfo(OnReqAccountInfo_arg1, OnReqAccountInfo_arg2, OnReqAccountInfo_arg3, OnReqAccountInfo_arg4);
			break;
		}
		case 5:
		{
			ROLE_LIST OnReqRoleList_arg1;
			((DATATYPE_ROLE_LIST*)pMethod->args[0])->createFromStreamEx(stream, OnReqRoleList_arg1);
			OnReqRoleList(OnReqRoleList_arg1);
			break;
		}
		case 6:
		{
			uint8 OnReqUnlockRole_arg1 = stream.readUint8();
			OnReqUnlockRole(OnReqUnlockRole_arg1);
			break;
		}
		default:
			break;
	};
}

void AccountBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Account");

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
			case 4:
			{
				uint64 oldval_Coin = Coin;
				Coin = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onCoinChanged(oldval_Coin);
				}
				else
				{
					if(inWorld())
						onCoinChanged(oldval_Coin);
				}

				break;
			}
			case 2:
			{
				uint64 oldval_Exp = Exp;
				Exp = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onExpChanged(oldval_Exp);
				}
				else
				{
					if(inWorld())
						onExpChanged(oldval_Exp);
				}

				break;
			}
			case 3:
			{
				uint64 oldval_Fame = Fame;
				Fame = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onFameChanged(oldval_Fame);
				}
				else
				{
					if(inWorld())
						onFameChanged(oldval_Fame);
				}

				break;
			}
			case 1:
			{
				uint16 oldval_Level = Level;
				Level = stream.readUint16();

				if(pProp->isBase())
				{
					if(inited())
						onLevelChanged(oldval_Level);
				}
				else
				{
					if(inWorld())
						onLevelChanged(oldval_Level);
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

void AccountBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Account"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint64 oldval_Coin = Coin;
	Property* pProp_Coin = pdatas[4];
	if(pProp_Coin->isBase())
	{
		if(inited() && !inWorld())
			onCoinChanged(oldval_Coin);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Coin->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onCoinChanged(oldval_Coin);
			}
		}
	}

	uint64 oldval_Exp = Exp;
	Property* pProp_Exp = pdatas[5];
	if(pProp_Exp->isBase())
	{
		if(inited() && !inWorld())
			onExpChanged(oldval_Exp);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Exp->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onExpChanged(oldval_Exp);
			}
		}
	}

	uint64 oldval_Fame = Fame;
	Property* pProp_Fame = pdatas[6];
	if(pProp_Fame->isBase())
	{
		if(inited() && !inWorld())
			onFameChanged(oldval_Fame);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Fame->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onFameChanged(oldval_Fame);
			}
		}
	}

	uint16 oldval_Level = Level;
	Property* pProp_Level = pdatas[7];
	if(pProp_Level->isBase())
	{
		if(inited() && !inWorld())
			onLevelChanged(oldval_Level);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Level->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onLevelChanged(oldval_Level);
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

AccountBase::AccountBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	Coin((uint64)FCString::Atoi64(TEXT("10000"))),
	Exp((uint64)FCString::Atoi64(TEXT("0"))),
	Fame((uint64)FCString::Atoi64(TEXT("0"))),
	Level((uint16)FCString::Atoi64(TEXT("1")))
{
}

AccountBase::~AccountBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void AccountBase::attachComponents()
{
}

void AccountBase::detachComponents()
{
}

}