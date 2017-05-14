#pragma once
#include"Client.h"
#include"System.h"
#include"databaseUtils.h"
#include<map>

class Clerk
{
private:
	System sys;
	Client currentClient;
	databaseUtils database;
	std::map<std::string, std::string> * logins;

	const int loanCode = 1, depositeCode = 2, withdrawCode = 3, createCode = 4;
public:
	Clerk(System s,databaseUtils database, std::map<std::string, std::string> * map);
	~Clerk();
	void deposit(std::string s);
	void withdraw(std::string i);
	void getLoan(std::string i);
	void creatAcc( std::string userName, std::string password, std::string name, std::string age
		,std::string address, std::string balance);
	void checkReq();
	void startServing();
};

