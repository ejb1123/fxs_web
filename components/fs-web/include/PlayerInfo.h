#pragma once
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