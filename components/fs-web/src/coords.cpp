#include "StdInc.h"
#include "ScriptEngine.h"
#include "ServerInstanceBase.h"
#include "ServerEventComponent.h"
#include "ResourceCallbackComponent.h"
static InitFunction initFunction([]()
{
	fx::ScriptEngine::RegisterNativeHandler("GET_COORDS", [](fx::ScriptContext context)
	{
		trace("called");
	});

	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		//instance->GetComponent<fx::ServerEventComponent>()->TriggerClientEvent("fx-data:coords:request", "-1");
	});

});

