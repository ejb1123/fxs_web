#pragma once
#include "StdInc.h"
#include "ServerInstanceBase.h"
#include <json.hpp>
#include "GameServer.h"
#include "ResourceManager.h"
#include "fs_utils.h"
using json = nlohmann::json;
struct ServerData
{
	json info;
	fx::ServerInstanceBase *instace;
	ServerData(fx::ServerInstanceBase *instace) : info({}), instace(instace)
	{

	}

	void update()
	{
		info["name"] = instace->GetComponent<console::Context>()->GetVariableManager()->FindEntryRaw("sv_hostname")->GetValue();
		unsigned char clients = 0;
		instace->GetComponent<fx::ClientRegistry>()->ForAllClients([&clients](auto client)
		{
			clients++;
		});
		info["totalPlayers"] = clients;
		auto resman = instace->GetComponent<fx::ResourceManager>();
		resman->ForAllResources([&](fwRefContainer<fx::Resource> resource)
		{
			// we've already listed hardcap, no need to actually return it again
			if (resource->GetName() == "hardcap")
			{
				return;
			}
			//if (resource->GetState == fx::ResourceState::)
			info["resources"][resource->GetName()] = json::object();
			char* state = fs::StateToString(resource);
			info["resources"][resource->GetName()]["state"] = (state);
		});
	}
};
