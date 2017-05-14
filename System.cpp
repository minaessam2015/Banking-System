#include "System.h"


 static std::queue<Client>waiting;
 static int next;


System::System()
{
	next = 0;
}


System::~System()
{
}

void System::remove() {
	waiting.pop();
}
Client System::getNext() {
	Client c=waiting.front();
	remove();
	return c;
}
void System::add(Client c){
	
	next++;
	c.setTurn(next);
	waiting.push(c);
//	std::cout << "client   " << c.getTurn() << "\n";
	
}
void System::printAll() {
	std::queue<Client> q = waiting;
	while(!q.empty()) {
		std::cout <<"Turn  "<< q.front().getTurn()<<"\n";
		q.pop();
	}
}
int System::getCurrent() {
	int i = next;
	return --i;
}
bool System::empty() {
	return waiting.empty();
}