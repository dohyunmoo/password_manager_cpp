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

void SavePassword(const std::vector<Password>& passwords, const std::string& fileName);
std::vector<Password> LoadPassword(const std::string& fileName);
