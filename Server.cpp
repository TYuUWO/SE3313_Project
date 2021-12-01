#include "thread.h"
#include "socketserver.h"
#include "sqlite3.h"
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

namespace{
	string lootArray[10] = {"shortsword", "axe", "dagger", "spear", "greatsword", "leather armor", "chain mail armor", "steel plate armor", "leather helmet", "steel helmet"};
}

class ClientThread : public Thread
{
private:
    Socket& socket;
    ByteArray data;
    sqlite3* DB;
    //user stats are lvl, xp, hp, atk, def
    int userStats[5];
    //user can have at most 3 equips; empty by default but can change when data is loaded
    string userEquips[3] = {"empty","empty","empty"};
    //user can have at most 3 skills
    string userSkills[3];

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
    	
    	//create randomizer seed
    	srand(time(NULL));
    	
    	int floors = (rand() % 11 + 5); //minimum of 5 floors, max of 15
    	
    	ByteArray response = ByteArray("You have entered the dungeon.");
    	try {socket.Write(response);}
    	catch (...) {
    		cout << "Entry failed (Server end)" <<endl;
    	}
    	
    	return floors;
    }
    
    int enemyEncounter(int floor){
    	//code to generate a random enemy
    	
    	string encounters[10] = {"goblin", "slime", "skeleton", "zombie", "giant snake", "orc", "wraith", "demon", "dragon", "behemoth"};
    	string encounter;
    	//stats are hp, attack, defense, speed (determine how likely monster is to go first, player speed fixed)
    	int encounterStats[4] = {0,0,0,0};
    	
    	//create randomizer seed
    	srand(time(NULL));
    	
    	if (floor % 5 == 0) {
    		//boss floor
    		encounter = encounters[(rand() % 3 + 7)];
    	}
    	else{
    		//ordinary floor
    		encounter = encounters[rand() % 7 + 0];
    	}
    	
    	//setup encounter according to enemy; use the same seed for convenience
    	if (encounter == "goblin"){
    		//set hp
    		encounterStats[0] = 10;
    		//set atk
    		encounterStats[1] = 3;
    		//set def
    		encounterStats[2] = 4;
    		//set spd
    		encounterStats[3] = 1;
    	}
    	else if (encounter == "slime"){
    		//set hp
    		encounterStats[0] = 5;
    		//set atk
    		encounterStats[1] = 2;
    		//set def
    		encounterStats[2] = 2;
    		//set spd
    		encounterStats[3] = 2;
    	}
    	else if (encounter == "skeleton"){
    		//set hp
    		encounterStats[0] = 11;
    		//set atk
    		encounterStats[1] = 2;
    		//set def
    		encounterStats[2] = 5;
    		//set spd
    		encounterStats[3] = 1;
    	}
    	else if (encounter == "zombie"){
    		//set hp
    		encounterStats[0] = 9;
    		//set atk
    		encounterStats[1] = 5;
    		//set def
    		encounterStats[2] = 5;
    		//set spd
    		encounterStats[3] = 1;
    	}
    	else if (encounter == "giant snake"){
    		//set hp
    		encounterStats[0] = 7;
    		//set atk
    		encounterStats[1] = 4;
    		//set def
    		encounterStats[2] = 2;
    		//set spd
    		encounterStats[3] = 3;
    	}
    	else if (encounter == "orc"){
    		//strongest normal monster; stats should be close to a boss monster's stats
    		//set hp
    		encounterStats[0] = 15;
    		//set atk
    		encounterStats[1] = 7;
    		//set def
    		encounterStats[2] = 7;
    		//set spd
    		encounterStats[3] = 1;
    	}
    	else if (encounter == "wraith"){
    		//set hp
    		encounterStats[0] = 5;
    		//set atk
    		encounterStats[1] = 5;
    		//set def
    		encounterStats[2] = 3;
    		//set spd
    		encounterStats[3] = 3;
    	}
    	else if (encounter == "demon"){
    		//boss monster
    		//set hp
    		encounterStats[0] = 20;
    		//set atk
    		encounterStats[1] = 7;
    		//set def
    		encounterStats[2] = 5;
    		//set spd
    		encounterStats[3] = 3;
    	}
    	else if (encounter == "dragon"){
    		//boss monster
    		//set hp
    		encounterStats[0] = 20;
    		//set atk
    		encounterStats[1] = 7;
    		//set def
    		encounterStats[2] = 7;
    		//set spd
    		encounterStats[3] = 2;
    	}
    	else{
    		//this is the behemoth; this monster is stronger than all other monsters
    		//set hp
    		encounterStats[0] = 20;
    		//set atk
    		encounterStats[1] = 10;
    		//set def
    		encounterStats[2] = 10;
    		//set spd
    		encounterStats[3] = 0;
    	}
    	
    	//code to do combat with the enemy
    	
    	ByteArray response = ByteArray("You encountered a "+encounter+"!");
    		try {socket.Write(response);}
    		catch (...) {
    			cout << "Battle failed (Server end)" <<endl;
    		}
    	
    	while(userStats[2] > 0&&encounterStats[0]>0){
    		//do battle
    		response = ByteArray("What will you do? (attack, skill, flee)");
    		try {socket.Write(response);}
    		catch (...) {
    			cout << "Battle failed (Server end)" <<endl;
    		}
    		try {socket.Read(data);}
    		catch (...) {
    			cout << "Battle failed (Client end)" <<endl;
    		}
    		if (data.ToString()=="attack"){
    			//damage = player attack - enemy def
    			//order of attacks based on enemy spd stat
    			if((rand() % 4 + 0)>encounterStats[3]){
    				//attack first
    				
    			}
    			else{
    				//take damage first
    			}
    		}
    		else if(data.ToString() == "skill"){
    			//display skills
    			
    			//await response
    			
    			//skill activates
    		}
    		else{
    			//flee success based on enemy spd stat
    			if((rand() % 4 + 0)>encounterStats[3]){
    				//flee successfully
    				response = ByteArray("You fled successfully");
    				try {socket.Write(response);}
    				catch (...) {
    					cout << "Battle failed (Server end)" <<endl;
    				}
    				return 0;
    			}
    			else{
    				//take damage
    			}
    		}
    	}
    	
    	//generate random loot
    	int drop = ((rand() % 11 + 0) - 1);
    	if (drop<0){
    		//no drop
    	}
    	else{
    		string loot = lootArray[drop];
    		response = ByteArray("You obtained a "+loot+"!\nWould you like to equip?\n[0]"+userEquips[0]+"\n[1]"+userEquips[1]+"\n[2]"+userEquips[2]+"\n[3] discard the item");
    		try {socket.Write(response);}
    		catch (...) {
    			cout << "Loot failed (Server end)" <<endl;
    		}
    		// Wait for user info
		try {socket.Read(data);}
		catch (...) {
			cout << "Loot failed (Client end)" <<endl;
		}
    		if (stoi(data.ToString())==3){
    			//discard the item
    			loot = "empty";
    		}
    		else {
    			userEquips[stoi(data.ToString())] = loot;
    		}
    	}
    	
    	//code for xp gain
    	if(floor%5==0){
    		//boss floor gives 20xp
    		userStats[1] += 20;
    		while(userStats[1]>=15){
    			//level up
    			userStats[0] += 1;
    			userStats[1] -= 15;
    		}
    	}
    	else{
    		//normal encounter gives 5xp
    		userStats[1] += 5;
    		while(userStats[1]>=15){
    			//level up
    			userStats[0] += 1;
    			userStats[1] -= 15;
    		}
    	}
    	
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
    
    int dbTask(string action){ // makes DB perform an exec task
    	int exit = 0;
    	char* messageError;
    	exit = sqlite3_exec(DB, action.c_str(), NULL, 0, &messageError);
	
	if (exit != SQLITE_OK) {
		std::cerr << "Error: Task not completed." << endl;
		sqlite3_free(messageError);
		
	}
	else {
		std::cout << "Task is finished" << endl;
	}
	return 0;
    }
    
    int loginUser(string username){
    	int exit = 0;
	string dbFile = "DB/" + username + ".db";
	char* messageError;
	exit = sqlite3_open(dbFile.c_str(), &DB); //c_str converts string to const char
	
	
	if (exit != SQLITE_OK) {
		std::cerr << "Error: Database not found." << endl;
		sqlite3_free(messageError);
		
	}
	else {
		std::cout << "Database is open for " << username <<endl;
	}
	
	//test if the user's data exists while creating a new database for a potential
	// new user of the app
	string addStats = "CREATE TABLE stats("
			"level INTEGER NOT NULL, "
			"exp INTEGER NOT NULL, "
			"hp INTEGER NOT NULL, "
			"attack INTEGER NOT NULL, "
			"defense INTEGER NOT NULL);";
			
	exit = sqlite3_exec(DB, addStats.c_str(), NULL, 0, &messageError);
	
	if (exit != SQLITE_OK) {
		std::cerr << "Error: Table is not added, or "<< username <<" already has data." << endl;
		sqlite3_free(messageError);
		
	}
	else { // If a table was added, update to level 1 values for stats, equips and skills for new user
		std::cout << "Table Added Successfully" << endl;
		
		string insertStats = "INSERT INTO stats VALUES(0,0,15,4,4)"; //Stats initialize here;
		string createEquips = "CREATE TABLE equips ("
					"name TEXT NOT NULL) ";
		string insertEquips = "INSERT INTO equips VALUES('empty')";
		string createSkills = "CREATE TABLE skills ("
					"name TEXT NOT NULL)";
		string insertSkills = "INSERT INTO skills VALUES('empty')";
		
		dbTask(insertStats);
		
		dbTask(createEquips);
		
		dbTask(insertEquips);
		dbTask(insertEquips);
		dbTask(insertEquips);
		
		dbTask(createSkills);
		
		dbTask(insertSkills);
		dbTask(insertSkills);
		dbTask(insertSkills);
									
		
	}
	return 0;
    }
    
	int getUserData(string username) {
		
	return 0;
	}
    
    ////////////////////////////Main Thread//////////////////////////////////////////////////////////////////////////////
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
	string username = data.ToString();
	loginUser(username);
	
	getUserData(username);
	
	
	
	 response = ByteArray("Ready to begin? ");
    	//Prompt user login
    	try {socket.Write(response);}
    	catch (...) {
    		cout << "Server fails " <<endl;
    	}
	// Wait for user info
	try {socket.Read(data);}
	catch (...) {
		cout << "Client fails" <<endl;
	}
	cout << data.ToString() << endl;
	//code for initialization
	
	while(data.ToString() != "done"){
		//initialize dungeon
		int totalFloors = enterDungeon();
		int floor = 1;
		int battles = 0;
		//create randomizer seed
    		srand(time(NULL));

		while(floor< totalFloors){
			//dungeon needs to be cleared to exit this loop
			enemyEncounter(floor);
			battles += 1;
			if((rand() % 4 + 0)<battles){
				battles = 0;
				floor += 1;
			}
			
			//save prompt before every boss floor
			if((floor+1)%5==0){
				saveData();
			}
			
			//allow the user to exit
			response = ByteArray("Type \"done\" if you would like to exit");
    			try {socket.Write(response);}
    			catch (...) {
    				cout << "exit prompt failed (Server end)" <<endl;
    			}
			// Wait for user info
			try {socket.Read(data);}
			catch (...) {
				cout << "exit prompt failed (Client end)" <<endl;
			}
			if (data.ToString() == "done"){
				break;
			}
		}
		//dungeon clear
		if (floor > totalFloors){
			saveData();
			response = ByteArray("You cleared this dungeon!\nWould you like to exit? (type \"done\" to exit, otherwise go again)");
    			try {socket.Write(response);}
    			catch (...) {
    				cout << "clear prompt failed (Server end)" <<endl;
    			}
			// Wait for user info
			try {socket.Read(data);}
			catch (...) {
				cout << "clear prompt failed (Client end)" <<endl;
			}
		}
	}
	
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
