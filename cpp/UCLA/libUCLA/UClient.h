#ifndef UCLIENT_H
#define UCLIENT_H

#ifdef UCLA_HAVE_UNIX
#include <xs/xs.hpp>
#else
#include <xs.hpp>
#endif

#include "UConfig.h"

class UClient
{
public:

	/**
	UCLA Client constructor.

	Creates client instance from specified config.

	@param \b config Reference to configuration object
	@param \b autostart Tells if connection will be started automatically. 
	Otherwise you will have to call Start method. Default value = false.
	*/
	UClient(UConfig &config, bool autostart=false);

	/**
	Starts connection to a server.
	*/
	void Start(void);

	/**
	Sends data to a server.

	@param \b buf Buffer with data.
	@param \b len Length of the data.
	@param \b nonBlocking Specifies that the operation should be performed in non-blocking mode. Default value = false.
	@throws xs::error_t exception when something fails.
	*/
	void SendData(const char *buf, size_t len, bool nonBlocking=false);

	~UClient(void);

	/**
	Tells if connection has been started

	@return True if connection has been started
	*/
	bool IsStarted(void);

private:
	const char* _endpoint;
	xs::context_t *_ctx;
    xs::socket_t *_sock;

	bool _isStarted;
};

#endif // UCLIENT_H
