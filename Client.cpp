#include "Client.h"


/*private:
	int id;
	std::string clientName;
	std::string clientPassword;
	double balance;
	int req;*/
Client::Client(){}
Client::Client(int req) 
{
	this->req = req;
}

Client::Client(std::string name, std::string password,int req) {

	this->req = req;
	this->clientName = name;
	this->clientPassword = password;
}
Client::~Client()
{
}

int Client::getTurn() {
	
	return this->turn;
}
void Client::setTurn(int i) {
	
	this->turn = i;
	
 }

int Client::getReq() {
	return this->req;
}
std::string Client::getName() {
	return this->clientName;
}
void Client::setReq(int i) {
	this->req = i;
}
void Client::setName(std::string s) {
	this->clientName = s;
}