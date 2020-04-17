#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/Account.h"
#include "Scripts/Role.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new Account();
			break;
		case 2:
			pEntity = new Role();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pAccountModule = new ScriptModule("Account", 1);
	EntityDef::moduledefs.Add(TEXT("Account"), pAccountModule);
	EntityDef::idmoduledefs.Add(1, pAccountModule);

	Property* pAccount_position = new Property();
	pAccount_position->name = TEXT("position");
	pAccount_position->properUtype = 40000;
	pAccount_position->properFlags = 4;
	pAccount_position->aliasID = 1;
	KBVar* pAccount_position_defval = new KBVar(FVector());
	pAccount_position->pDefaultVal = pAccount_position_defval;
	pAccountModule->propertys.Add(TEXT("position"), pAccount_position); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_position->aliasID, pAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(position / 40000).");

	Property* pAccount_direction = new Property();
	pAccount_direction->name = TEXT("direction");
	pAccount_direction->properUtype = 40001;
	pAccount_direction->properFlags = 4;
	pAccount_direction->aliasID = 2;
	KBVar* pAccount_direction_defval = new KBVar(FVector());
	pAccount_direction->pDefaultVal = pAccount_direction_defval;
	pAccountModule->propertys.Add(TEXT("direction"), pAccount_direction); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_direction->aliasID, pAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(direction / 40001).");

	Property* pAccount_spaceID = new Property();
	pAccount_spaceID->name = TEXT("spaceID");
	pAccount_spaceID->properUtype = 40002;
	pAccount_spaceID->properFlags = 16;
	pAccount_spaceID->aliasID = 3;
	KBVar* pAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAccount_spaceID->pDefaultVal = pAccount_spaceID_defval;
	pAccountModule->propertys.Add(TEXT("spaceID"), pAccount_spaceID); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_spaceID->aliasID, pAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(spaceID / 40002).");

	Property* pAccount_Coin = new Property();
	pAccount_Coin->name = TEXT("Coin");
	pAccount_Coin->properUtype = 4;
	pAccount_Coin->properFlags = 32;
	pAccount_Coin->aliasID = 4;
	KBVar* pAccount_Coin_defval = new KBVar((uint64)FCString::Atoi64(TEXT("10000")));
	pAccount_Coin->pDefaultVal = pAccount_Coin_defval;
	pAccountModule->propertys.Add(TEXT("Coin"), pAccount_Coin); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_Coin->aliasID, pAccount_Coin);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(Coin / 4).");

	Property* pAccount_Exp = new Property();
	pAccount_Exp->name = TEXT("Exp");
	pAccount_Exp->properUtype = 2;
	pAccount_Exp->properFlags = 32;
	pAccount_Exp->aliasID = 5;
	KBVar* pAccount_Exp_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pAccount_Exp->pDefaultVal = pAccount_Exp_defval;
	pAccountModule->propertys.Add(TEXT("Exp"), pAccount_Exp); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_Exp->aliasID, pAccount_Exp);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(Exp / 2).");

	Property* pAccount_Fame = new Property();
	pAccount_Fame->name = TEXT("Fame");
	pAccount_Fame->properUtype = 3;
	pAccount_Fame->properFlags = 32;
	pAccount_Fame->aliasID = 6;
	KBVar* pAccount_Fame_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pAccount_Fame->pDefaultVal = pAccount_Fame_defval;
	pAccountModule->propertys.Add(TEXT("Fame"), pAccount_Fame); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_Fame->aliasID, pAccount_Fame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(Fame / 3).");

	Property* pAccount_Level = new Property();
	pAccount_Level->name = TEXT("Level");
	pAccount_Level->properUtype = 1;
	pAccount_Level->properFlags = 32;
	pAccount_Level->aliasID = 7;
	KBVar* pAccount_Level_defval = new KBVar((uint16)FCString::Atoi64(TEXT("1")));
	pAccount_Level->pDefaultVal = pAccount_Level_defval;
	pAccountModule->propertys.Add(TEXT("Level"), pAccount_Level); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_Level->aliasID, pAccount_Level);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(Level / 1).");

	TArray<DATATYPE_BASE*> Account_OnReqAccountInfo_args;
	Account_OnReqAccountInfo_args.Add(EntityDef::id2datatypes[3]);
	Account_OnReqAccountInfo_args.Add(EntityDef::id2datatypes[5]);
	Account_OnReqAccountInfo_args.Add(EntityDef::id2datatypes[5]);
	Account_OnReqAccountInfo_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_OnReqAccountInfo = new Method();
	pAccount_OnReqAccountInfo->name = TEXT("OnReqAccountInfo");
	pAccount_OnReqAccountInfo->methodUtype = 4;
	pAccount_OnReqAccountInfo->aliasID = 1;
	pAccount_OnReqAccountInfo->args = Account_OnReqAccountInfo_args;

	pAccountModule->methods.Add(TEXT("OnReqAccountInfo"), pAccount_OnReqAccountInfo); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_OnReqAccountInfo->aliasID, pAccount_OnReqAccountInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(OnReqAccountInfo / 4).");

	TArray<DATATYPE_BASE*> Account_OnReqRoleList_args;
	Account_OnReqRoleList_args.Add(EntityDef::id2datatypes[23]);

	Method* pAccount_OnReqRoleList = new Method();
	pAccount_OnReqRoleList->name = TEXT("OnReqRoleList");
	pAccount_OnReqRoleList->methodUtype = 5;
	pAccount_OnReqRoleList->aliasID = 2;
	pAccount_OnReqRoleList->args = Account_OnReqRoleList_args;

	pAccountModule->methods.Add(TEXT("OnReqRoleList"), pAccount_OnReqRoleList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_OnReqRoleList->aliasID, pAccount_OnReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(OnReqRoleList / 5).");

	TArray<DATATYPE_BASE*> Account_OnReqUnlockRole_args;
	Account_OnReqUnlockRole_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_OnReqUnlockRole = new Method();
	pAccount_OnReqUnlockRole->name = TEXT("OnReqUnlockRole");
	pAccount_OnReqUnlockRole->methodUtype = 6;
	pAccount_OnReqUnlockRole->aliasID = 3;
	pAccount_OnReqUnlockRole->args = Account_OnReqUnlockRole_args;

	pAccountModule->methods.Add(TEXT("OnReqUnlockRole"), pAccount_OnReqUnlockRole); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_OnReqUnlockRole->aliasID, pAccount_OnReqUnlockRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(OnReqUnlockRole / 6).");

	TArray<DATATYPE_BASE*> Account_ReqAccountInfo_args;

	Method* pAccount_ReqAccountInfo = new Method();
	pAccount_ReqAccountInfo->name = TEXT("ReqAccountInfo");
	pAccount_ReqAccountInfo->methodUtype = 1;
	pAccount_ReqAccountInfo->aliasID = -1;
	pAccount_ReqAccountInfo->args = Account_ReqAccountInfo_args;

	pAccountModule->methods.Add(TEXT("ReqAccountInfo"), pAccount_ReqAccountInfo); 
	pAccountModule->base_methods.Add(TEXT("ReqAccountInfo"), pAccount_ReqAccountInfo);

	pAccountModule->idbase_methods.Add(pAccount_ReqAccountInfo->methodUtype, pAccount_ReqAccountInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(ReqAccountInfo / 1).");

	TArray<DATATYPE_BASE*> Account_ReqRoleList_args;

	Method* pAccount_ReqRoleList = new Method();
	pAccount_ReqRoleList->name = TEXT("ReqRoleList");
	pAccount_ReqRoleList->methodUtype = 2;
	pAccount_ReqRoleList->aliasID = -1;
	pAccount_ReqRoleList->args = Account_ReqRoleList_args;

	pAccountModule->methods.Add(TEXT("ReqRoleList"), pAccount_ReqRoleList); 
	pAccountModule->base_methods.Add(TEXT("ReqRoleList"), pAccount_ReqRoleList);

	pAccountModule->idbase_methods.Add(pAccount_ReqRoleList->methodUtype, pAccount_ReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(ReqRoleList / 2).");

	TArray<DATATYPE_BASE*> Account_ReqUnlockole_args;
	Account_ReqUnlockole_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_ReqUnlockole = new Method();
	pAccount_ReqUnlockole->name = TEXT("ReqUnlockole");
	pAccount_ReqUnlockole->methodUtype = 3;
	pAccount_ReqUnlockole->aliasID = -1;
	pAccount_ReqUnlockole->args = Account_ReqUnlockole_args;

	pAccountModule->methods.Add(TEXT("ReqUnlockole"), pAccount_ReqUnlockole); 
	pAccountModule->base_methods.Add(TEXT("ReqUnlockole"), pAccount_ReqUnlockole);

	pAccountModule->idbase_methods.Add(pAccount_ReqUnlockole->methodUtype, pAccount_ReqUnlockole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(ReqUnlockole / 3).");

	ScriptModule* pRoleModule = new ScriptModule("Role", 2);
	EntityDef::moduledefs.Add(TEXT("Role"), pRoleModule);
	EntityDef::idmoduledefs.Add(2, pRoleModule);

	Property* pRole_position = new Property();
	pRole_position->name = TEXT("position");
	pRole_position->properUtype = 40000;
	pRole_position->properFlags = 4;
	pRole_position->aliasID = 1;
	KBVar* pRole_position_defval = new KBVar(FVector());
	pRole_position->pDefaultVal = pRole_position_defval;
	pRoleModule->propertys.Add(TEXT("position"), pRole_position); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_position->aliasID, pRole_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(position / 40000).");

	Property* pRole_direction = new Property();
	pRole_direction->name = TEXT("direction");
	pRole_direction->properUtype = 40001;
	pRole_direction->properFlags = 4;
	pRole_direction->aliasID = 2;
	KBVar* pRole_direction_defval = new KBVar(FVector());
	pRole_direction->pDefaultVal = pRole_direction_defval;
	pRoleModule->propertys.Add(TEXT("direction"), pRole_direction); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_direction->aliasID, pRole_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(direction / 40001).");

	Property* pRole_spaceID = new Property();
	pRole_spaceID->name = TEXT("spaceID");
	pRole_spaceID->properUtype = 40002;
	pRole_spaceID->properFlags = 16;
	pRole_spaceID->aliasID = 3;
	KBVar* pRole_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pRole_spaceID->pDefaultVal = pRole_spaceID_defval;
	pRoleModule->propertys.Add(TEXT("spaceID"), pRole_spaceID); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_spaceID->aliasID, pRole_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(spaceID / 40002).");

	Property* pRole_Name = new Property();
	pRole_Name->name = TEXT("Name");
	pRole_Name->properUtype = 6;
	pRole_Name->properFlags = 4;
	pRole_Name->aliasID = 4;
	KBVar* pRole_Name_defval = new KBVar(FString());
	pRole_Name->pDefaultVal = pRole_Name_defval;
	pRoleModule->propertys.Add(TEXT("Name"), pRole_Name); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_Name->aliasID, pRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(Name / 6).");

	Property* pRole_RoleType = new Property();
	pRole_RoleType->name = TEXT("RoleType");
	pRole_RoleType->properUtype = 7;
	pRole_RoleType->properFlags = 4;
	pRole_RoleType->aliasID = 5;
	KBVar* pRole_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pRole_RoleType->pDefaultVal = pRole_RoleType_defval;
	pRoleModule->propertys.Add(TEXT("RoleType"), pRole_RoleType); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_RoleType->aliasID, pRole_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(RoleType / 7).");

	pRoleModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("UINT8");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("DBID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("INT32");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("VECTOR3");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("ROLE_INFO");
		DATATYPE_ROLE_INFO* pDatatype = new DATATYPE_ROLE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ROLE_LIST");
		DATATYPE_ROLE_LIST* pDatatype = new DATATYPE_ROLE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}