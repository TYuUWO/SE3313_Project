#include <iostream>
#include "sqlite3.h"

//compile via g++ -o initDB initDB.cpp -lsqlite3
using namespace std;

int main(int argc, char** argv)
{
	sqlite3* DB;
	std::string deleteTable = "DROP TABLE stats;";
	std::string sql = "CREATE TABLE stats("
			"level INTEGER NOT NULL, "
			"exp INTEGER NOT NULL, "
			"hp INTEGER NOT NULL, "
			"attack INTEGER NOT NULL, "
			"defense INTEGER NOT NULL);";
	
	std::string insertTable = "INSERT INTO stats VALUES";
	
	int exit = 0;
	exit = sqlite3_open("userDB.db", &DB);
	char* messageError;
	
	exit = sqlite3_exec(DB, deleteTable.c_str(), NULL, 0, &messageError);
	
	if (exit != SQLITE_OK) {
		std::cerr << "Error: Table is not deleted." << endl;
		sqlite3_free(messageError);
		
	}
	else {
		std::cout << "Table Deleted Successfully" << endl;
	}
	///////////////////////////////////////////////////////////////////apple
	
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	
	if (exit != SQLITE_OK) {
		std::cerr << "Error: Table is not created." << endl;
		sqlite3_free(messageError);
		
	}
	else {
		std::cout << "Table Created Successfully" << endl;
	}
	
	sqlite3_close(DB);
	return 0;
}
