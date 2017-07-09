#pragma once
#include <json.hpp>
#include "StdInc.h"
#include <ServerInstanceBase.h>
#include <GameServer.h>
#include <ResourceManager.h>
#include <fs_utils.h>
#include <console\Console.VariableHelpers.h>
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