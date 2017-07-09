#include "StdInc.h"
#include <ServerInstanceBase.h>
#include <HttpServerManager.h>
#include <ResourceManager.h>
#include <json.hpp>
#include <fs_utils.h>
#include <InfoData.h>
#include "PlayerInfo.h"
#include "ServerData.h"
#include "HttpServer.h"


using json = nlohmann::json;
bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password);

static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		static auto infoData = std::make_shared<InfoData>(instance);
		static auto playerData = std::make_shared<PlayerData>(instance);
		static auto serverData = std::make_shared<ServerData>(instance);
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>&request, const fwRefContainer<net::HttpResponse>& response)
		{
			if (fs::isAuthed(request, response, instance)) {
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
						if (morepath == "/server.json")
						{
							serverData->update();
							response->SetStatusCode(200);
							response->End(serverData->info.dump());
						}
					}
				}
			}
		});
	}, 1500);
}
);
