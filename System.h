#pragma once
#include<string>
#include<queue>
#include<iostream>
#include"Client.h"

class System
{
public:
	 System();
	~System();
	 void add(Client c);
	Client getNext();
	void remove();
	void printAll();
	int getCurrent();
	bool empty();
};

