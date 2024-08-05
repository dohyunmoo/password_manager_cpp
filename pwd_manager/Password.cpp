#include "Password.h"
#include <iostream>
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>
#include <algorithm>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

void SavePassword(const std::vector<Password>& passwords, const std::string& fileName)
{
	// save to file
	std::ofstream ostream(fileName);
	ostream << passwords.size();

	for (const Password& pwd : passwords) {
		std::string website = pwd.website;
		std::string username = pwd.username;
		std::string password = pwd.password;

		ostream << '\n' << website << ' ' << username << ' ' << password;
	}

	// save to mongoDB


}

std::vector<Password> LoadPassword(const std::string& fileName)
{
	// load from file
	//if (!std::filesystem::exists(fileName)) {
	//	return std::vector<Password>();
	//}

	//std::vector<Password> passwords;
	//std::ifstream istream(fileName);

	//int n;
	//istream >> n;

	//for (int i = 0; i < n; i++) {
	//	std::string website;
	//	std::string username;
	//	std::string password;

	//	istream >> website >> username >> password;
	//	passwords.push_back(Password{ website, username, password });
	//}

	//return passwords;

	//save to mongoDB

	const std::string server = "tcp://127.0.0.1:3306";
	const std::string username = "root";
	const std::string password = "";

	std::vector<Password> passwords;

	try {
		sql::Driver* driver = get_driver_instance();
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		con = driver->connect(server, username, password);
		con->setSchema("password_manager");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM pwd_manager");

		while(res->next()) {
			std::string website = res->getString(1).c_str();
			std::string username = res->getString(2).c_str();
			std::string password = res->getString(3).c_str();

			passwords.push_back(Password{ website, username, password });
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		// save to file?
	}
	
	return passwords;
}
