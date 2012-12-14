#ifndef UCLIENT_H
#define UCLIENT_H

#include "UConfig.h"
#include "UException.h"

namespace UCLA{

	class USender
	{
	public:

		/**
		UCLA Sender constructor.

		Creates sender instance from specified config.

		@param \b config Reference to configuration object
		@param \b autostart Tells if connection will be started automatically. 
		Otherwise you will have to call Start method. Default value = false.
		*/
		USender(UConfig& config, bool autostart=false);

		/**
		Move constructor.
		*/
		USender(USender&& that);

		/**
		Move operator.
		*/
		USender& operator=(USender&& that);

		/**
		Starts connection to a receiver.
		*/
		void Start(void);

		/**
		Sends data to a receiver.

		@param \b buf Buffer with data.
		@param \b len Length of the data.
		@param \b nonBlocking Specifies that the operation should be performed in non-blocking mode. Default value = false.
		@throws xs::error_t exception when something fails.
		*/
		void SendData(const char* buf, size_t len, bool nonBlocking=false);

		/**
		Tells if connection has been started

		@return True if connection has been started
		*/
		bool IsStarted(void) const;

		/**
		Returns endpoint string.
		*/
		const char* Endpoint() const{
			return this->_endpoint;
		}

		~USender(void);

	private:
		char* _endpoint;
		void *_ctx;
		void *_sock;

		bool _isStarted;

		void CopyEndpoint(const char* endpoint);
		void CleanUpXS(void);
	};
}
#endif // UCLIENT_H
