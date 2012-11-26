#include "stdafx.h"

#include <UClient.h>
#include <ULoader_JSON.h>

using namespace std;
using namespace UCLA;

#define RND_LEN 8

void MakeItRandom(char *ar, int len);

int main(int argc, char** argv)
{
	char r[RND_LEN];
	srand((unsigned int)time(NULL));

	cout << "Me is client. Me is input. Me sending random number things.\n";
	cout << "Me waiting connection...\n";
	
	try{
		
		ULoader_JSON configLoader("config.json");
		unique_ptr<UClient> client = configLoader.GetClient("output1");
		client->Start();

		for(int i = 0; i < 3; i++){
			MakeItRandom(r, RND_LEN);

			client->SendData(r, RND_LEN);
		}

		cout << "Data sent successfully. Me exiting after you pressing return.\n";
	}catch(std::exception &err){
		cout << "Something went horribly wrong:\n\t" << err.what() <<"\n";
	}

	getchar();
	return 0;
}

void MakeItRandom(char *ar, int len){
	for(int i = 0; i < RND_LEN; i++){
		ar[i] = (rand()%48) + 1;
	}
}
