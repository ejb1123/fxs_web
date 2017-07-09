#include "StdInc.h"
#include <ServerInstanceBase.h>
#include <HttpServerManager.h>
#include <GameServer.h>
#include <ResourceManager.h>
#include <json.hpp>
#include <fs_utils.h>
#include <console\Console.VariableHelpers.h>
#include <InfoData.h>
#include "PlayerInfo.h"

using json = nlohmann::json;
bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password);

static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		static auto infoData = std::make_shared<InfoData>(instance);
		static auto playerData = std::make_shared<PlayerData>(instance);
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>&request, const fwRefContainer<net::HttpResponse>& response)
		{
			if (request->GetRequestMethod() == "GET")
			{
				if (request->GetPath().substr(7).length() > 0)
				{
					auto morepath = request->GetPath().substr(7);
					if (morepath == "/players.json")
					{
						playerData->update();
						response->SetStatusCode(200);
						response->End(playerData->jsonData.dump());
					}
				}


			}
		});
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/ffdata", [=](const fwRefContainer<net::HttpRequest>& request, const fwRefContainer<net::HttpResponse>& response)
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
