#include "stdafx.h"

#include <UReceiver.h>
#include <ULoader_JSON.h>

using namespace std; 
using namespace UCLA;

int main(int argc, char** argv)
{
	cout << "Hi there! You will be receiving a random numbers from remote input.\n";
	cout << "Use them to win the lottery!\n";
	cout << "Waiting for connection...\n";

	try{
		ULoader_JSON configLoader("config.json");

		// Yes, you can use lambda! Or you can just bind std::function<void(char*, int)>.
		// Whatever :)
		unique_ptr<UReceiver> receiver = configLoader.GetReceiver("input1",[](char* buf, int len){
			cout << "\n";

			for(int i = 0; i<len; i++){
				cout << (int)buf[i] << "\t";
			}
		});

		receiver->Run();
	}catch(UException &err){
		cout << "Something went horribly wrong:\n\t" << err.what() << "\n";
	}

	(void) getchar();
	return 0;
}
