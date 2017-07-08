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
	 bool isAuthed(fwRefContainer<net::HttpRequest> const request, fwRefContainer<net::HttpResponse> const response, std::string rcon_password)
	{
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
			auto const pass = ":" + rcon_password;
			auto buf_sz = size_t();
			auto const buf_ptr
				= base64_encode
				(reinterpret_cast<const unsigned char*>(pass.c_str())
					, pass.size()
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
}
std::string GetUserName()
{
	return "";
}