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
#include <regex>


using json = nlohmann::json;
bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password);
static bool doesmatch(const std::string &path, std::smatch &matches, const std::regex &regex) {
	return std::regex_match(path.begin(), path.end(), matches, regex, std::regex_constants::match_default);
}
static InitFunction initFunction([]()
{
	fx::ServerInstanceBase::OnServerCreate.Connect([](fx::ServerInstanceBase *instance)
	{
		//TODO: add update checker
		static auto console = instance->GetComponent<console::Context>();
		static auto infoData = std::make_shared<InfoData>(instance);
		static auto playerData = std::make_shared<PlayerData>(instance);
		static auto serverData = std::make_shared<ServerData>(instance);
		static auto resourceData = std::make_shared<ResourceData>(instance);
		trace("creating fs server", "fs-web");
		static std::regex playersNETID("^\/fsdata\/players\/(\\d{1,3})", std::regex::ECMAScript);
		static std::regex players("^\/fsdata\/players", std::regex::ECMAScript);
		static std::regex server("^\/fsdata\/server", std::regex::ECMAScript);
		static std::regex resources("^\/fsdata\/resources", std::regex::ECMAScript);
		static std::regex logregex("^\/fsdata\/log",std::regex::ECMAScript);
		static std::regex logAction("^\/fsdata\/log\/actions\/(.*)", std::regex::ECMAScript);
		static std::smatch l;
		instance->GetComponent<fx::HttpServerManager>()->AddEndpoint("/fsdata", [=](const fwRefContainer<net::HttpRequest>&request, const fwRefContainer<net::HttpResponse>& response)
		{
			if (fs::isAuthed(request, response, instance)) {
				if (request->GetRequestMethod() == "GET")
				{
					if (doesmatch(request->GetPath(), l, players)) {
						playerData->update();
						response->SetStatusCode(200);
						response->End(playerData->jsonData.dump());
					}

					if (doesmatch(request->GetPath(), l, playersNETID)) {
						//TODO: add /players/{net_id}
					}

					//TODO: add /players/{net_id}/actions

					if (doesmatch(request->GetPath(), l, server)) {
						serverData->update();
						response->SetStatusCode(200);
						response->End(serverData->info.dump());
					}

					if (doesmatch(request->GetPath(), l, resources)) {
						resourceData->update();
						response->End(resourceData->info.dump());
					}


					if (doesmatch(request->GetPath(), l, logregex))
					{
						std::string line;
						std::ifstream logFile;
						logFile.open(MakeRelativeCitPath(L"CitizenFX.log").c_str());
						std::string log;

						while (logFile.is_open())
						{
							while (std::getline(logFile, line))
							{
								log += line;
							}
							logFile.close();
						}
						response->SetHeader("Content-Type", "text/plain");
						response->End(log);
					}
					if (doesmatch(request->GetPath(), l, logAction))
					{
						if (l[1] == "clear") {
							std::fstream logFile;
							logFile.open(MakeRelativeCitPath(L"CitizenFX.log").c_str(), std::ios::out | std::ios::trunc);
							logFile.close();
							response->End("");
						}
					}

					return;
				}
			}
		});
	}, 1500);
}
);
