#include "Password.h"
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>
#include <algorithm>

void savePassword(const std::vector<Password>& passwords, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << passwords.size();

	for (const Password& pwd : passwords) {
		std::string website = pwd.website;
		std::string username = pwd.username;
		std::string password = pwd.password;

		ostream << '\n' << website << ' ' << username << ' ' << password;
	}
}

std::vector<Password> loadPassword(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<Password>();
	}

	std::vector<Password> passwords;
	std::ifstream istream(fileName);

	int n;
	istream >> n;

	for (int i = 0; i < n; i++) {
		std::string website;
		std::string username;
		std::string password;

		istream >> website >> username >> password;
		passwords.push_back(Password{ website, username, password });
	}

	return passwords;
}
