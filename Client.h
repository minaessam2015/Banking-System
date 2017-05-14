#pragma once
#include<iostream>
#include<string>


class Client
{
private:
	int id;
	std::string clientName="";
	std::string clientPassword="";
	double balance=0.0;
	int req;
	int turn=0;
	
public:
	Client();
	Client(int req);
	Client(std::string name, std::string password,int req);

	~Client();
	int getTurn();
	void setTurn(int i);
	int getReq();
	std::string getName();
	void setReq(int i);
	void setName(std::string s);


};

