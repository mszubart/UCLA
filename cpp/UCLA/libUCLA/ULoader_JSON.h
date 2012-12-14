#ifndef ULOADER_JSON_H
#define ULOADER_JSON_H

#include "USender.h"
#include "UReceiver.h"
#include "UException.h"
#include <memory>
#include <functional>

namespace UCLA{

	class ULoader_JSON
	{
	private:		
		void *senderConfig;
		void *receiverConfig;

	public:

		/**
		Loads configuration from file.

		@param \b configFile Configuration file.
		*/
		ULoader_JSON(char *configFile);

		/**
		Creates configuration object for receiver.

		@param \b inputName input name.
		@return Configuration object.
		*/
		std::unique_ptr<UConfig> GetReceiverConfig(char *inputName);

		/**
		Creates receiver based on configuration.

		@param \b inputName Name of input.
		@param \b handler Receive handler.
		@return Server object. (no autostart).
		*/
		std::unique_ptr<UReceiver> GetReceiver(char *inputName, std::function<void(char*, int)> handler);

		/**
		Creates configuration object for sender.

		@param \b outputName output name.
		@return Configuration object.
		*/
		std::unique_ptr<UConfig> GetSenderConfig(char *outputName);

		/**
		Creates sender based on configuration.

		@param \b outputName Name of output.
		@return Client object. (no autostart).
		*/
		std::unique_ptr<USender> GetSender(char *outputName);
	};
}

#endif
