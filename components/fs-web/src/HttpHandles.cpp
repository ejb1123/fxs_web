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
#include <ServerInstanceBase.h>
#include <HttpServerManager.h>
#include <ResourceManager.h>
#include <json.hpp>
#include <fs_utils.h>
#include <InfoData.h>
#include "PlayerInfo.h"
#include "ServerData.h"
#include "HttpServer.h"
#include <fstream>


using json = nlohmann::json;
bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password);

static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		//static auto console = std::make_shared<console::Context>();
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
						else if (morepath == "/server.json")
						{
							serverData->update();
							response->SetStatusCode(200);
							response->End(serverData->info.dump());
						}
						else if (morepath == "/resource")
						{
							serverData->update();
							response->End(serverData->resourceData->info.dump());
						}
						else if (morepath == "/log")
						{
							std::string line;
							std::ifstream logFile;
							logFile.open(MakeRelativeCitPath(L"CitizenFX.log").c_str());
							std::string log;

							while (logFile.is_open())
							{
								while (std::getline(logFile,line))
								{
									log += line;
								}
								logFile.close();
							}
							response->SetHeader("Content-Type", "text/plain");
							response->End(log);
						}
						else if(morepath=="/log/clear")
						{
							std::fstream logFile;
							logFile.open(MakeRelativeCitPath(L"CitizenFX.log").c_str(),std::ios::out | std::ios::trunc);
							logFile.close();
							response->End("");
						}
						else
						{
							response->SetStatusCode(404);
							response->End("");
						}
						//if (morepath.substr())
					}
				}
			}
		});
	}, 1500);
}
);
