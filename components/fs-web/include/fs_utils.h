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
#include <ResourceManager.h>
#include <base64.h>
#include "console/Console.VariableHelpers.h"
#include "StdInc.h"
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
			//TODO: fix realm
			response->SetHeader("WWW-Authenticate", "BASIC realm=\"hdhdn\"");
			response->Write("");
			response->End();
			return false;
		}
		if (request->GetHeader("Authorization").length() > 0)
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
			response->SetStatusCode(403);
			response->End("");
			return false;
		}
		response->SetStatusCode(500);
		response->End("An Error has occured in Auth");
		return false;
	}
	std::string GetUserName(fx::ServerInstanceBase *instance)
	{
		auto varman = instance->GetComponent<console::Context>()->GetVariableManager();
		{
			//TODO: Bubble up the nullptr
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
			//TODO: Bubble up the nullptr
			auto u = varman->FindEntryRaw("FX_PASSWORD");
			if (u != nullptr) {
				return u->GetValue();
			}
		}
		return "";
	}
}

