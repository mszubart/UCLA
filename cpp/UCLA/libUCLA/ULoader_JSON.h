#ifndef ULOADER_JSON_H
#define ULOADER_JSON_H

#include "UClient.h"
#include "UServer.h"
#include "UException.h"
#include <memory>

namespace UCLA{

	class ULoader_JSON
	{
	private:		
		void *clientConfig;
		void *serverConfig;

	public:
		ULoader_JSON(char *configFile);

		std::unique_ptr<UConfig> GetServerConfig(char *serverName);
		std::unique_ptr<UServer> GetServer(char *serverName);

		std::unique_ptr<UConfig> GetClientConfig(char *serverName);
		std::unique_ptr<UClient> GetClient(char *serverName);
	};
}

#endif
