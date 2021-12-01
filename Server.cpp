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
    	
    	int floors = 5; //minimum of 5 floors, max of 15
    	
    	//create randomizer seed
    	srand(time(NULL));
    	
    	floors += (rand() % 10 + 0);
    	
    	ByteArray response = ByteArray("You have entered the dungeon.");
    	try {socket.Write(response);}
    	catch (...) {
    		cout << "Entry failed (Server end)" <<endl;
    	}
    	
    	return 0;
    }
    
    int enemyEncounter(int floor){
    	//code to generate a random enemy
    	
    	string encounters[10] = {"goblin", "slime", "skeleton", "zombie", "giant snake", "orc", "wraith", "demon", "dragon", "behemoth"};
    	string encounter;
    	
    	//create randomizer seed
    	srand(time(NULL));
    	
    	if (floor % 5 == 0) {
    		//boss floor
    		encounter = encounters[(rand() % 10 + 7)];
    	}
    	else{
    		//ordinary floor
    		encounter = encounters[rand() % 7 + 0];
    	}
    	
    	//code to do combat with the enemy
    	
    	return 0;
    }
    
    int saveData(void){
    	//prompt user to save
    	ByteArray response = ByteArray("Would you like to save? (y/n): ");
    	try {socket.Write(response);}
    	catch (...) {
    		cout << "Save failed (Server end)" <<endl;
    	}
	// Wait for user info
	try {socket.Read(data);}
	catch (...) {
		cout << "Save failed (Client end)" <<endl;
	}
	response = ByteArray("Saving... please wait");
	try {socket.Write(response);}
    	catch (...) {
    		cout << "Save failed (Server end)" <<endl;
    	}
    	//code to save data
    	
    	response = ByteArray("Saved");
	try {socket.Write(response);}
    	catch (...) {
    		cout << "Save failed (Server end)" <<endl;
    	}
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
	try {socket.Read(data);}
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
