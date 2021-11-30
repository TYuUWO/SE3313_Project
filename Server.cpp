#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace Sync;
using namespace std;
namespace{
	volatile bool typeYes = true;
}

class ClientThread : public Thread
{
private:
    Socket& socket;
    ByteArray data;

public:
    ClientThread(Socket& socket)
    : socket(socket)
    {}
    
    Socket& GetSocket()
    {
    	return socket;
    }
    
    int enterDungeon(void){
    	//code to create randomized dungeon
    	return 0;
    }
    
    int enemyEncounter(void){
    	//code to generate a random enemy
    	
    	//code to do combat with the enemy
    	
    	return 0;
    }
    
    virtual long ThreadMain()
    {
    	ByteArray response = ByteArray("Please enter your username: ");
    	//Prompt user login
    	try {socket.Write(response);}
    	catch (...) {
    		cout << "Login failed (Server end)" <<endl;
    	}
	// Wait for user info
	try {socket.Read(data)}
	catch (...) {
		cout << "Login failed (Client end)" <<endl;
	}
	
	//code for login process
	
	//code for initialization
	
	do {
        socket.Read(data);

        //Convert it to a string and capitalize the string
        string str = data.ToString();
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        
        //Convert it back to a ByteArray type
        ByteArray response = ByteArray(str);
        
        // Send it back
        socket.Write(response);
        }
        while (data.ToString() !="done");
	return 1;
    }
};
    
// This thread handles the server operations
class ServerThread : public Thread
{
private:
    SocketServer& server;
    ByteArray data;
    vector<ClientThread *> threads;
public:
    ServerThread(SocketServer& server)
    : server(server)
    {}

    ~ServerThread()
    {
        // Cleanup
	//...
	for(ClientThread* client : threads){
		Socket& terminate = client->GetSocket();
		//terminate.Read(data);
		std::string stringer = "endtheclients";
		ByteArray response = ByteArray(stringer);
		terminate.Write(response);
		
		//terminate.Close();
	}
    }

    virtual long ThreadMain()
    {
    while(true){
        // Wait for a client socket connection
        Socket* newConnection = new Socket(server.Accept());

        // A reference to this pointer 
        Socket& socketReference = *newConnection;
	//You can use this to read data from socket and write data to socket. You may want to put this read/write somewhere else. You may use ByteArray
	threads.push_back(new ClientThread(socketReference));
	
	}
	return 1;
    }
};

int main(void)
{
	
    std::cout << "I am a server." << std::endl;
	sData = "Hello from server.";
	
    std::cout << "Press 'enter' to terminate" << std::endl;
    // Create our server
    SocketServer server(3000);    
	
    // Need a thread to perform server operations
    ServerThread serverThread(server);
	
    // This will wait for input to shutdown the server
    FlexWait cinWaiter(1, stdin);
    cinWaiter.Wait();
    
    // Shut down and clean up the server
    server.Shutdown();

}
