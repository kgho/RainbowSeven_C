#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

namespace KBEngine
{

void DATATYPE_ROLE_INFO::createFromStreamEx(MemoryStream& stream, ROLE_INFO& datas)
{
	datas.Dbid = stream.readUint64();
	datas.RoleType = stream.readUint8();
	datas.IsLock = stream.readUint8();
	datas.Kill = stream.readUint32();
	datas.Death = stream.readUint32();
	datas.Assist = stream.readUint32();
	datas.Point = stream.readUint32();
	datas.PlayCount = stream.readUint32();
}

void DATATYPE_ROLE_INFO::addToStreamEx(Bundle& stream, const ROLE_INFO& v)
{
	stream.writeUint64(v.Dbid);
	stream.writeUint8(v.RoleType);
	stream.writeUint8(v.IsLock);
	stream.writeUint32(v.Kill);
	stream.writeUint32(v.Death);
	stream.writeUint32(v.Assist);
	stream.writeUint32(v.Point);
	stream.writeUint32(v.PlayCount);
}

void DATATYPE_ROLE_LIST::createFromStreamEx(MemoryStream& stream, ROLE_LIST& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_ROLE_LIST::addToStreamEx(Bundle& stream, const ROLE_LIST& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}


}