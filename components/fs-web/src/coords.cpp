/*
MIT License

Copyright (c) 2017 FiveM-Scripts

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "StdInc.h"
#include "Utils.h"
#include "ScriptEngine.h"
#include "ServerInstanceBase.h"
#include "ResourceCallbackComponent.h"
#include "ClientRegistry.h"
#include "ResourceEventComponent.h"
#include "coords.h"
#include <ResourceManager.h>
static InitFunction initFunction([]()
{

	fx::ScriptEngine::RegisterNativeHandler("GET_COORDS", [](fx::ScriptContext context)
	{
	});

	fx::ServerInstanceBase::OnServerCreate.Connect([&](fx::ServerInstanceBase *instance)
	{
		static auto l = fx::ResourceManager::GetCurrent();

		static auto j = l->GetComponent<fx::ResourceEventManagerComponent>();
		j->OnTriggerEvent.Connect([&](const std::string& eventName, const std::string& eventPayload, const std::string& eventSource, bool* eventCanceled)
		{			
			//trace("%s\n%s\n",eventName,eventPayload);
		});
		static auto clientRegistry = instance->GetComponent<fx::ClientRegistry>();
		fx::ScriptEngine::RegisterNativeHandler("set_loc",[&](fx::ScriptContext& context)
		{			
			auto x = context.CheckArgument<float>(0);
			auto y = context.CheckArgument<float>(1);
			auto z = context.CheckArgument<float>(2);
			auto playerNetID = context.CheckArgument<int>(3);
			clientRegistry->GetClientByNetID(playerNetID)->SetData("coords", std::make_any<coords>(coords(x,y,z)));
			trace(std::to_string(x).c_str());
			//trace(y);
			//instance->GetComponent<fx::ServerInstanceBase>();
		});
		//instance->GetComponent<fx::ServerEventComponent>()->TriggerClientEvent("fx-data:coords:request", "-1");
	},1500);
});

