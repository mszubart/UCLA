#include "stdafx.h"

#include <UServer.h>

using namespace std; 

void OnDataReceived(char *buf, int len);

#ifndef UCLA_HAVE_UNIX
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char** argv)
#endif
{
	cout << "Hi there! You will be receiving a random numbers from remote input.\n";
	cout << "Use them to win the lottery!\n";
	cout << "Waiting for connection...\n";

	try{
		UConfig config("*","5555"); // This should be loaded from a configuration file by a loader class
		UServer server(config);

		server.SetupReceiveHandler(OnDataReceived);

		server.Start();
		server.Run();
	}catch(xs::error_t err){
		cout << "Something went horribly wrong:\n\t" << err.what() << "\n";
	}

	getchar();
	return 0;
}

void OnDataReceived(char *buf, int len){
	cout << "\n";

	for(int i = 0; i<len; i++){
		cout << (int)buf[i] << "\t";
	}
}

