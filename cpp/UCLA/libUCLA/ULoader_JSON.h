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

		/**
		Loads configuration from file.

		@param \b configFile Configuration file.
		*/
		ULoader_JSON(char *configFile);

		/**
		Creates configuration object for server.

		@param \b serverName Server name.
		@return Configuration object.
		*/
		std::unique_ptr<UConfig> GetServerConfig(char *serverName);

		/**
		Creates server based on configuration.

		@param \b serverName Name of server.
		@return Server object. (no autostart).
		*/
		std::unique_ptr<UServer> GetServer(char *serverName);

		/**
		Creates configuration object for client.

		@param \b clientName Client name.
		@return Configuration object.
		*/
		std::unique_ptr<UConfig> GetClientConfig(char *clientName);

		/**
		Creates client based on configuration.

		@param \b clientName Name of client.
		@return Client object. (no autostart).
		*/
		std::unique_ptr<UClient> GetClient(char *clientName);
	};
}

#endif
