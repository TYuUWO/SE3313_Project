
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
	string ipAddress;
	

	ByteArray data;
	// Welcome the user 
	std::cout << "SE3313 Lab 3 Client" << std::endl;
	cout << "Enter the server IP address: " << endl;
	getline(cin,ipAddress);
	
	// Create our socket
	//localhost: 127.0.0.1
	Socket socket(ipAddress, 3000);
	//attempt to initiate connection
	//if socket creation failed, set the flag and print the error
	try {socket.Open();}
	catch (...){
		socketCreated = false;
		cout << "Socket cannot be created" <<endl;
	}
	
	//main program loop
	while(inputData!="done" && socketCreated){
		socket.Read(data);
		
		//end server connection abruptly and exit based on server reply
		if (data.ToString() == "endtheclients"){
			cout << "Server connection terminated" <<endl;
			break;
		}
		if (data.ToString() == "\nyou died!"){
			break;
		}
		//print the received data
		std::cout << data.ToString() << endl;
		
		getline(cin,inputData);
	
		//convert inputData to ByteArray data
		ByteArray response(inputData);

		//To write to server socket and read from socket. You may use ByteArray 
		socket.Write(response);
		
	}
	
	//close the socket
	socket.Close();
	
	return 0;
}
