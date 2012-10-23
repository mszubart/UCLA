#pragma once

#include <xs.hpp>

#include "UConfig.h"

#define UCLA_MAX_MESSAGE_LEN 256

typedef void(*UCLA_RECEIVE_HANDLER)(char *buff, int len);

class UServer
{
public:
	/**
	UCLA Server constructor.

	Creates server instance from specified config.

	@param \b config Reference to configuration object
	@param \b autostart Tells if server will be started automatically. 
	Otherwise you will have to call Start method. Default value = false.
	*/
	UServer(UConfig &config, bool autostart=false);

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

	@param \b handler Pointer to void (char*, int) function.
	*/
	void SetupReceiveHandler(UCLA_RECEIVE_HANDLER handler);

	/**
	Tells if server has been started

	@return True if server has been started
	*/
	bool IsStarted(void);

	~UServer(void);

private:
	UCLA_RECEIVE_HANDLER _receive_handler;

	const char* _endpoint;
	xs::context_t *_ctx;
	xs::socket_t *_sock;

	bool _isStarted;
};

