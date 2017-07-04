#include "StdInc.h"
#include <ServerInstanceBase.h>
#include <HttpServerManager.h>
#include <GameServer.h>
#include <ResourceManager.h>
#include <VFSManager.h>

#include <botan/base64.h>
#include <json.hpp>
#include <fs_utils.h>
using json = nlohmann::json;

static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		// TODO: make instanceable
		static auto instanceRef = instance;
		static auto ivVar = instance->AddVariable<int>("sv_infoVersion", ConVar_ServerInfo, 0);
		static auto maxClientsVar = instance->AddVariable<int>("sv_maxClients", ConVar_ServerInfo, 30);
		auto epPrivacy = instance->AddVariable<bool>("sv_endpointPrivacy", ConVar_None, false);

		// max clients cap
		maxClientsVar->GetHelper()->SetConstraints(1, 32);

		struct InfoData
		{
			json infoJson;
			int infoHash;

			InfoData()
				: infoHash(0), infoJson({ { "server", "FXServer-pre" },{ "enhancedHostSupport", true },{ "resources",{} } })
			{
				Update();
			}

			void Update()
			{
				auto varman = instanceRef->GetComponent<console::Context>()->GetVariableManager();

				infoJson["vars"] = json::object();

				varman->ForAllVariables([&](const std::string& name, int flags, const std::shared_ptr<internal::ConsoleVariableEntryBase>& var)
				{
					// don't return more variable information
					if (name == "sv_infoVersion" || name == "sv_hostname")
					{
						return;
					}

					infoJson["vars"][name] = var->GetValue();
				}, ConVar_ServerInfo);



				infoJson["version"] = 0;

				infoHash = static_cast<int>(std::hash<std::string>()(infoJson.dump()) & 0x7FFFFFFF);
				infoJson["version"] = infoHash;

				infoJson["resources"] = json::object();
				infoJson["resources"]["hardcap"] = json::object();

				auto resman = instanceRef->GetComponent<fx::ResourceManager>();
				resman->ForAllResources([&](fwRefContainer<fx::Resource> resource)
				{
					// we've already listed hardcap, no need to actually return it again
					if (resource->GetName() == "hardcap")
					{
						return;
					}
					//if (resource->GetState == fx::ResourceState::)
					infoJson["resources"][resource->GetName()] = json::object();
					char* state = fs::StateToString(resource);
					infoJson["resources"][resource->GetName()]["state"] = (state);
				});



				ivVar->GetHelper()->SetRawValue(infoHash);
			}
		};

		static auto infoData = std::make_shared<InfoData>();
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>& request, const fwRefContainer<net::HttpResponse>& response)
		{
			auto auth = request->GetHeader("auth");

			auto rcon_password = instance->GetComponent<fx::GameServer>()->GetRconPassword();
			trace(rcon_password.c_str(),"fivem-web");

			if(auth.compare(rcon_password)){
				response->SetStatusCode(403);
				response->Write("");
				response->End();
			}
			else
			{
				infoData->Update();
				response->End(infoData->infoJson.dump());
			}
				
		});

		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [](const fwRefContainer<net::HttpRequest>&request, const fwRefContainer<net::HttpResponse>& response)
		{
			if (request->GetRequestMethod() == "POST")
			{

			}
		});
	}, 1500);
}
);