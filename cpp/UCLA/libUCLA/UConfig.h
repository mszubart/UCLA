#pragma once

#include <string.h>
#include <stddef.h>

#define UCLA_DEFAULT_PROTO "tcp"
#define UCLA_SERVER 0
#define UCLA_CLIENT 1

#define UCLA_ENDPOINT_STR_LEN(i, po, pr) (strlen(pr) + strlen(i) + strlen(po) + 5) // 5 = 1 + strlen("://:")

class UConfig
{
public:

	/**
	UConfig constructor.

	@param \b source IP address of host if client or interface if server(http://www.crossroads.io/1-0:xs-tcp).
	@param \b port Port number (as string).
	*/
	UConfig(const char* source, const char* port): _source(source), _port(port), _proto(UCLA_DEFAULT_PROTO){
		
		int strLength = UCLA_ENDPOINT_STR_LEN(
			this->_source,
			this->_port, 
			this->_proto);

		this->_endpoint = new char[strLength];

		// proto://source:port
		strcpy(this->_endpoint, this->_proto);
		strcat(this->_endpoint, "://");
		strcat(this->_endpoint, this->_source);
		strcat(this->_endpoint, ":");
		strcat(this->_endpoint, this->_port);
	}

	~UConfig(void){
		delete this->_endpoint;
	}

	/**
	Returns Endpoint String
	*/
	const char* Endpoint(void){
		return this->_endpoint;
	}

private:
	const char* _source;
	const char* _port;

	const char* _proto;
	char* _endpoint;
};

