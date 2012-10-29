#include "stdafx.h"

#include <UClient.h>

using namespace std;

#define RND_LEN 8

void MakeItRandom(char *ar, int len);

#ifndef UCLA_HAVE_UNIX
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char** argv)
#endif
{
	char r[RND_LEN];
	srand((unsigned int)time(NULL));

	cout << "Me is client. Me is input. Me sending random number things.\n";
	cout << "Me waiting connection...\n";

	try{
		UConfig config("127.0.0.1", "5555"); // This should be loaded from a configuration file by a loader class
		UClient client(config);
		client.Start();

		for(int i = 0; i < 3; i++){
			MakeItRandom(r, RND_LEN);

			client.SendData(r, RND_LEN);
		}

	}catch(xs::error_t err){
		cout << "Something went horribly wrong:\n\t" << err.what() <<"\n";
	}

	cout << "Data sent successfully. Me exiting after you pressing return.\n";

	getchar();
	return 0;
}

void MakeItRandom(char *ar, int len){
	for(int i = 0; i < RND_LEN; i++){
		ar[i] = (rand()%48) + 1;
	}
}
