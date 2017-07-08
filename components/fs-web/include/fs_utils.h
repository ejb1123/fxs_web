#include <ResourceManager.h>
#include <console\Console.VariableHelpers.h>
#include "StdInc.h"
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
	std::string GetPassword(fx::ServerInstanceBase *instance);
	std::string GetUserName(fx::ServerInstanceBase *instance);

	bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, fx::ServerInstanceBase *instance)
	{
		auto fx_password = fs::GetPassword(instance);
		auto fx_username = fs::GetUserName(instance);
		if (fx_username.length() == 0 && fx_password.length() == 0) {
			return true;
		}
		if (request->GetHeader("Authorization") == std::string()) {
			response->SetStatusCode(401);
			response->SetHeader("WWW-Authenticate", "BASIC realm=\"hdhdn\"");
			response->Write("");
			response->End();
			return false;
		}
		else if (request->GetHeader("Authorization").length() > 0)
		{


			auto auth = request->GetHeader("Authorization");
			std::string srvpass("Basic ");
			auto const UserPass = fx_username + ":" + fx_password;
			auto buf_sz = size_t();
			auto const buf_ptr
				= base64_encode
				(reinterpret_cast<const unsigned char*>(UserPass.c_str())
					, UserPass.size()
					, &buf_sz
				);
			srvpass.append(buf_ptr, buf_ptr + buf_sz);
			free(buf_ptr);

			if (!srvpass.compare(auth))
			{
				return true;
			}
			else
			{
				response->SetStatusCode(403);
				response->End("");
				return false;
			}
		}
	}
	std::string GetUserName(fx::ServerInstanceBase *instance)
	{
		auto varman = instance->GetComponent<console::Context>()->GetVariableManager();
		{
			auto u = varman->FindEntryRaw("FX_USERNAME");
			if (u != nullptr) {
				return u->GetValue();
			}
		}
		return "";
	}

	std::string GetPassword(fx::ServerInstanceBase *instance)
	{
		auto varman = instance->GetComponent<console::Context>()->GetVariableManager();
		{
			auto u = varman->FindEntryRaw("FX_PASSWORD");
			if (u != nullptr) {
				return u->GetValue();
			}
		}
		return "";
	}
}

