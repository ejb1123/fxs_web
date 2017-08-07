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
*/#pragma once
#include <json.hpp>
#include "StdInc.h"
#include "ServerInstanceBase.h"
#include "ClientRegistry.h"
#include "coords.h"
using json = nlohmann::json;

struct PlayerData
{
	fx::ServerInstanceBase *instance_base_;
	json jsonData;
	PlayerData(fx::ServerInstanceBase *instance) : jsonData({}), instance_base_(instance)
	{
		client_registry = instance->GetComponent<fx::ClientRegistry>();
		update();
	}
	void update()
	{
		jsonData["players"] = json::array();
		client_registry->ForAllClients([&](const std::shared_ptr<fx::Client> client)
		{
			auto jsonclient = json::object();
			auto name = client->GetName();
			jsonclient["name"] = name;

			if (client->GetData("coords").has_value()) {
				auto jsoncoords = json::object();
				jsoncoords["x"]= std::any_cast<coords>(client->GetData("coords")).x;
				jsoncoords["y"] = std::any_cast<coords>(client->GetData("coords")).y;
				jsoncoords["z"] = std::any_cast<coords>(client->GetData("coords")).z;
				jsonclient["coords"] = jsoncoords;
			}
			jsonclient["lastseen"] = client->GetLastSeen().count();
			jsonclient["identifiers"] = client->GetIdentifiers();
			jsonclient["netid"] = client->GetNetId();
			jsonclient["adress"] = client->GetAddress().ToString();
			jsonclient["guid"] = client->GetGuid();
			jsonclient["netbase"] = client->GetNetBase();
			//jsonclient["peer"] = client->GetPeer();
			jsonclient["tcpendpoint"] = client->GetTcpEndPoint();
			jsonData["players"].push_back(jsonclient);
		});
	}
private:
	fwRefContainer<fx::ClientRegistry> client_registry;

	auto GetPlayers()
	{
		json playerArray = {};
		client_registry->ForAllClients([&](const std::shared_ptr<fx::Client> client)
		{
			playerArray.push_back(json({ "name",client->GetName() }));
		});
		return  playerArray.dump();
	}
};