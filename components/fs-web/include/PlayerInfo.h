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
using json = nlohmann::json;

struct PlayerData
{
	fx::ServerInstanceBase *instance_base_;
	json jsonData;
	PlayerData(fx::ServerInstanceBase *instance) :jsonData({})
	{
		this->instance_base_ = instance;
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
			auto coords = json::object();
			coords["x"] = 0;
			coords["y"] = 0;
			coords["z"] = 0;
			jsonclient["coords"] = coords;
			auto identifiers = json::object();
			identifiers = client->GetIdentifiers();
			jsonclient["identifiers"] = identifiers;
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