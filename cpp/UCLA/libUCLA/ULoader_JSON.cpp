#include "ULoader_JSON.h"
#include <jansson.h>

using namespace UCLA;

ULoader_JSON::ULoader_JSON(char *configFile){
	json_t *config;
	json_error_t error;
	json_t *inputs, *outputs;
	this->serverConfig = NULL;
	this->clientConfig = NULL;

	try{
		config = json_load_file(configFile, 0, &error);
		if(config) {
			//Inputs
			inputs = json_object_get(config, "inputs");
			if(json_is_object(inputs))
			{
				this->serverConfig = inputs;
			}

			//Outputs
			outputs = json_object_get(config, "outputs");
			if(json_is_object(outputs))
			{
				this->clientConfig = outputs;
			}

		}else
			throw std::exception();

	} catch(...){
		throw UException("Cannot load configuration from file");
	}      
}

std::unique_ptr<UConfig> ULoader_JSON::GetServerConfig(char *serverName) {
	json_t *server, *configInterface, *configPort;

	server = json_object_get(static_cast<json_t*>(this->serverConfig), serverName);
	if(!json_is_object(server))	
		throw UException("There is no such server defined in config file.");

	configInterface = json_object_get(server, "interface");
	if(!json_is_string(configInterface))	
		throw UException("Cannot read 'interface' value from specified configuration.");

	configPort = json_object_get(server, "port");
	if(!json_is_string(configPort))	
		throw UException("Cannot read 'port' value from specified configuration.");

	std::unique_ptr<UConfig> config(new UConfig(json_string_value(configInterface), json_string_value(configPort)));

	return std::move(config);
}

std::unique_ptr<UServer> ULoader_JSON::GetServer(char *serverName, std::function<void(char*, int)> handler) {
	std::unique_ptr<UConfig> config = GetServerConfig(serverName);
	std::unique_ptr<UServer> server(new UServer(*config, handler));	

	return std::move(server);
}

std::unique_ptr<UConfig> ULoader_JSON::GetClientConfig(char *clientName) {
	json_t *server, *configHost, *configPort;

	server = json_object_get(static_cast<json_t*>(this->clientConfig), clientName);
	if(!json_is_object(server))	
		throw UException("There is no such client defined in config file.");

	configHost = json_object_get(server, "host");
	if(!json_is_string(configHost))	
		throw UException("Cannot read 'host' value from specified configuration.");

	configPort = json_object_get(server, "port");
	if(!json_is_string(configPort))	
		throw UException("Cannot read 'port' value from specified configuration.");

	std::unique_ptr<UConfig> config(new UConfig(json_string_value(configHost), json_string_value(configPort)));

	return std::move(config);
}

std::unique_ptr<UClient> ULoader_JSON::GetClient(char *clientName) {
	std::unique_ptr<UConfig> config = GetClientConfig(clientName);
	std::unique_ptr<UClient> client(new UClient(*config));	

	return std::move(client);
}
