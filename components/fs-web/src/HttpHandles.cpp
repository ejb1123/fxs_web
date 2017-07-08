#include "StdInc.h"
#include <ServerInstanceBase.h>
#include <HttpServerManager.h>
#include <GameServer.h>
#include <ResourceManager.h>
#include <VFSManager.h>

#include <botan\bcrypt.h>
#include <base64.h>
#include <json.hpp>
#include <fs_utils.h>
#include <console\Console.VariableHelpers.h>
#include <InfoData.h>
using json = nlohmann::json;
bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password);

static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		static auto infoData = std::make_shared<InfoData>(instance);
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>& request, const fwRefContainer<net::HttpResponse>& response)
		{			
			if (fs::isAuthed(request, response, instance)) 
			{
				infoData->Update();
				response->End(infoData->infoJson.dump());

			}
		});
		
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>&request, const fwRefContainer<net::HttpResponse>& response)
		{
			if (request->GetRequestMethod() == "POST")
			{

			}
		});
	}, 1500);
}
);
