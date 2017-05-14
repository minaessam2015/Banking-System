#include "Clerk.h"



Clerk::Clerk(System s,databaseUtils db, std::map<std::string, std::string> * map)
{
	sys = s;
	database = db;
	logins = map;
	currentClient = Client();
	startServing();
}


Clerk::~Clerk()
{
}

void Clerk::checkReq() {
	bool withoutAccount = false;
	int oldReq;

	int req = currentClient.getReq();
	if (currentClient.getName().empty() &&req!=createCode ) {
		withoutAccount = true;
		std::cout << "Without Account \n";
	}
	if (withoutAccount) {
		oldReq = req;
		req = createCode;
		currentClient.setReq(req);
		checkReq();
		req = oldReq;
	}

	if (req == createCode) {
		//std::string userName, std::string password, std::string name, std::string age
		//, std::string address, std::string balance
		std::string userName, password, name, age, address, balance;
		std::cout << "Enter userName , password , Name , age , address , balance \n";
		std::cin>>userName;
		std::cin >> password;
		std::cin.ignore();
		std::getline(std::cin, name);
		std::cin >> age;
		std::cin.ignore();
		std::getline(std::cin, address);
		std::cin >> balance;
		
		//std::cin >> userName >> password >> name >> age >> address >> balance;
		creatAcc(userName, password, name, age, address, balance);
	}
	else if(req==depositeCode)
	{
		std::cout << "Enter the amount to deposite \n";
		std::string s;
		std::cin >> s;
		deposit(s);
	}
	else if (req == withdrawCode) {
		std::cout << "Enter the amount to withdraw \n";
		std::string s;
		std::cin >> s;
		withdraw(s);
	}
	else if (req == loanCode) {
		std::cout << "Enter the amount for loan \n";
		std::string s;
		std::cin >> s;
		getLoan(s);
	}
}

void Clerk::deposit(std::string s) {
	std::string str = std::to_string(database.get_clientID(currentClient.getName()));
	std::cout << str << "\n";
	database.insert_intoDeposite(s, str);

}
void Clerk::withdraw(std::string s) {
	database.insert_intoWithdraw(s, std::to_string(database.get_clientID(currentClient.getName())));
}
void Clerk::creatAcc(std::string userName, std::string password, std::string name, std::string age
	, std::string address, std::string balance) {

	while (true)
	{
		if ((*logins).count(userName)) {
			std::cout << "This user name is already taken ,try something else \n";
			std::cin >> userName;
		}
		else
		{
			break;
		}
	}
	database.insert_intoAcc(userName, password, name, age, address, balance);
	currentClient.setName(userName);
	(*logins).insert(std::pair<std::string, std::string>(userName,password));
}
void Clerk::getLoan(std::string i) {
	database.insert_intoLoan(i, std::to_string(database.get_clientID(currentClient.getName())));
}
void Clerk::startServing() {
	while (!sys.empty())
	{
		currentClient = sys.getNext();
		checkReq();

	}
}