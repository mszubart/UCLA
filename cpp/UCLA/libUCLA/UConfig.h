#ifndef UCONFIG_H
#define UCONFIG_H

#include <string.h>
#include <stddef.h>

#include "m_safestring.h"

namespace UCLA{

#define UCLA_DEFAULT_PROTO "tcp"

#define UCLA_ENDPOINT_STR_LEN(i, po, pr) (strlen(pr) + strlen(i) + strlen(po) + 5) // 5 = 1 + strlen("://:")

	class UConfig
	{
	public:

		/**
		UConfig constructor.

		@param \b source IP address of host if client or interface if server(http://www.crossroads.io/1-0:xs-tcp).
		@param \b port Port number (as string).
		*/
		UConfig(const char* source, const char* port){
			this->CreateEndpoint(source, port);
		}

		UConfig(const UConfig &that){
			this->CopyEndpoint(that.Endpoint());
		}

		~UConfig(void){
			delete[] this->_endpoint;
			this->_endpoint = NULL;
		}

		UConfig& operator=(const UConfig& that){
			if (this != &that)
			{
				this->CopyEndpoint(that.Endpoint());
			}

			return *this;
		}

		/**
		Returns Endpoint String
		*/
		const char* Endpoint(void) const{
			return this->_endpoint;
		}

	private:
		char* _source;
		char* _port;

		char* _endpoint;

		void CopyEndpoint(const char* endpoint){
			using namespace Utils;

			delete[] this->_endpoint;

			int strLength = strlen(endpoint) + 1;

			char* tmp_endpoint = new char[strLength];
			this->_endpoint = tmp_endpoint;

			m_strlcpy(this->_endpoint, strLength, endpoint);
		}

		void CreateEndpoint(const char* source, const char* port){
			using namespace Utils;

			int strLength = UCLA_ENDPOINT_STR_LEN(
				source,
				port, 
				UCLA_DEFAULT_PROTO);

			char* tmp_endpoint = new char[strLength];
			this->_endpoint = tmp_endpoint;

			// proto://source:port
			m_strlcpy(this->_endpoint, strLength, UCLA_DEFAULT_PROTO);
			m_strlcat(this->_endpoint, strLength, "://");
			m_strlcat(this->_endpoint, strLength, source);
			m_strlcat(this->_endpoint, strLength, ":");
			m_strlcat(this->_endpoint, strLength, port);
		}
	};
}
#endif // UCONFIG_H
