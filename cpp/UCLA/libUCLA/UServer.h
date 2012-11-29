#ifndef USERVER_H
#define USERVER_H

#include "UConfig.h"
#include "UException.h"
#include <functional>

namespace UCLA{

	typedef void(*UCLA_RECEIVE_HANDLER)(char *buff, int len);

	class UServer
	{
	public:
		/**
		UCLA Server constructor.

		Creates server instance from specified config.

		@param \b config Reference to configuration object.
		@param \b handler Receive handler.
		@param \b autostart Tells if server will be started automatically. 
		Otherwise you will have to call Start method. Default value = false.
		*/
		UServer(UConfig &config, std::function<void(char*, int)> handler, bool autostart=false);

		/**
		Move constructor.
		*/
		UServer(UServer &&that);

		/**
		Move operator.
		*/
		UServer& operator=(UServer&& that);

		/**
		Starts a server.
		*/
		void Start(void);

		/**
		Receives single message

		\b NOTE: This is blocking.
		*/
		void Receive(void);

		/**
		Run in loop and receive messages.

		\b NOTE: This is infinite loop - just don't expect this to end.
		*/
		void Run(void);

		/**
		Sets ReceiveHandler

		This handler is called every time when message is received
		\b NOTE: Handler shouldn't be blocking.

		@param \b handler std::function<void(char*, int)>.
		*/
		void SetupReceiveHandler(std::function<void(char*, int)> handler);

		/**
		Tells if server has been started

		@return True if server has been started
		*/
		bool IsStarted(void) const;

		/**
		Returns endpoint string.
		*/
		const char* Endpoint() const{
			return this->_endpoint;
		}

		~UServer(void);

	private:
		std::function<void(char*, int)> _receive_handler;

		char* _endpoint;
		void *_ctx;
		void *_sock;

		bool _isStarted;

		void CopyEndpoint(const char* endpoint);
		void CleanUpXS(void);
	};
}
#endif // USERVER_H
