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
#include <ServerInstanceBase.h>
#include <GameServer.h>
#include <ResourceManager.h>
#include <fs_utils.h>
using json = nlohmann::json;

struct InfoData
{
	json infoJson;
	int infoHash;
	fx::ServerInstanceBase *instanceRef;

	InfoData(fx::ServerInstanceBase *instance)
		: infoHash(0), infoJson({ { "server", "FXServer-pre" },{ "enhancedHostSupport", true },{ "resources",{} } }),instanceRef(instance)
	{
		static auto instanceRef = instance;
		
		Update();
	}

	void Update()
	{
		auto varman = instanceRef->GetComponent<console::Context>()->GetVariableManager();
		//TODO the below varibles
		infoJson["vars"] = json::object();
		varman->ForAllVariables([&](const std::string& name, int flags, const std::shared_ptr<internal::ConsoleVariableEntryBase>& var)
		{
			// don't return more variable information
			if (name == "sv_infoVersion" || name == "sv_hostname")
			{
				return;
			}

			infoJson["vars"][name] = var->GetValue();
		}, 0b111);



		infoJson["version"] = 0;

		infoHash = static_cast<int>(std::hash<std::string>()(infoJson.dump()) & 0x7FFFFFFF);
		infoJson["version"] = infoHash;

		infoJson["resources"] = json::object();
		infoJson["resources"]["hardcap"] = json::object();

		auto resman = instanceRef->GetComponent<fx::ResourceManager>();
		resman->ForAllResources([&](fwRefContainer<fx::Resource> resource)
		{
			// we've already listed hardcap, no need to actually return it again
			if (resource->GetName() == "hardcap")
			{
				return;
			}
			//if (resource->GetState == fx::ResourceState::)
			infoJson["resources"][resource->GetName()] = json::object();
			char* state = fs::StateToString(resource);
			infoJson["resources"][resource->GetName()]["state"] = (state);
		});
	}
};