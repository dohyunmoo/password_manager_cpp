#pragma once
#include <string>
#include <vector>

class Password
{
public:
	std::string website;
	std::string username;
	std::string password;
	bool isHidden = true;
};

void savePassword(const std::vector<Password>& passwords, const std::string& fileName);
std::vector<Password> loadPassword(const std::string& fileName);
