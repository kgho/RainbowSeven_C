#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

namespace KBEngine
{

void DATATYPE_CHAT_INFO::createFromStreamEx(MemoryStream& stream, CHAT_INFO& datas)
{
	datas.Name = stream.readUnicode();
	datas.Time = stream.readUnicode();
	datas.Msg = stream.readUnicode();
}

void DATATYPE_CHAT_INFO::addToStreamEx(Bundle& stream, const CHAT_INFO& v)
{
	stream.writeUnicode(v.Name);
	stream.writeUnicode(v.Time);
	stream.writeUnicode(v.Msg);
}


}