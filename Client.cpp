
#include "thread.h"
#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace Sync;
using namespace std;

int main(void)
{
	string inputData;
	bool socketCreated = true;
	int socketReturn;
	// Welcome the user 
	std::cout << "SE3313 Lab 3 Client" << std::endl;
	
	// Create our socket
	Socket socket("127.0.0.1", 3000);
	//attempt to initiate connection
	//if socket creation failed, set the flag and print the error
	try {socket.Open();}
	catch (...){
		socketCreated = false;
		cout << "Socket cannot be created" <<endl;
	}
	
	//main program loop
	while(inputData!="done" && socketCreated){
		std::cout << "Please enter a string" << std::endl;
		getline(cin,inputData);
	
		//convert inputData to ByteArray data
		ByteArray data(inputData);

		//To write to socket and read from socket. You may use ByteArray 
		socket.Write(data);
		socket.Read(data);
		
		//end server connection and exit based on server reply
		if (data.ToString() == "endtheclients"){
			cout << "Server connection terminated" <<endl;
			break;
		}
		
		
		//print the received data
		std::cout << data.ToString() <<endl;
	}
	
	//close the socket
	socket.Close();
	
	return 0;
}
