#include <ResourceManager.h>
#pragma once
namespace fs {
	static char * StateToString(fwRefContainer<fx::Resource> resource) {
		char * state;
		switch (resource->GetState())
		{
		case fx::ResourceState::Started:
			state = "started";
			break;
		case fx::ResourceState::Starting:
			state = "starting";
			break;
		case fx::ResourceState::Stopped:
			state = "stopped";
			break;
		case fx::ResourceState::Stopping:
			state = "stopping";
			break;
		case fx::ResourceState::Uninitialized:
			state = "uninitialized";
			break;
		}
		return state;
	}
}