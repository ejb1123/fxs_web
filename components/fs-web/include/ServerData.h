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
#pragma once
#include "StdInc.h"
#include "ServerInstanceBase.h"
#include <json.hpp>
#include "GameServer.h"
#include "ResourceManager.h"
#include "fs_utils.h"
using json = nlohmann::json;

struct ResourceData
{
	json info;
	std::shared_ptr<fx::ServerInstanceBase> instace;
	fwRefContainer<fx::ResourceManager> resman;

	explicit ResourceData(fx::ServerInstanceBase *instace) : info({}), instace(instace)
	{
		resman = instace->GetComponent<fx::ResourceManager>();
	}

	void update()
	{
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


struct ServerData
{
	json info;
	std::shared_ptr<fx::ServerInstanceBase> instace;
	std::shared_ptr<ResourceData> resourceData;

	explicit ServerData(fx::ServerInstanceBase *instace) : info({}), instace(instace),resourceData(std::make_shared<ResourceData>(instace))
	{
		//resourceData = std::make_shared<ResourceData>(instace);
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
		resourceData->update();
		info["resources"] = resourceData->info["resources"];
	}
};
