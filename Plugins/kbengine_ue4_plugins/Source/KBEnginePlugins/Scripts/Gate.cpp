#include "Gate.h"
#include "Engine/KBEngine.h"
#include "LoginEvents.h"	
KBEngine::Gate::Gate() :GateBase()
{
}
KBEngine::Gate::~Gate()
{
}
//登录成功就会创建Gate，然后执行该函数
void KBEngine::Gate::__init__()
{
	
}
void KBEngine::Gate::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}