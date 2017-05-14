#include"sqlite3.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include"databaseUtils.h"
#include"Client.h"
#include"System.h"
#include"Clerk.h"
#include<map>

using namespace std;


int main() {
	databaseUtils database=databaseUtils();
	/*database.insert_intoAcc("MinaESSAM", "1234", "MINA ESSAM", "22", "MATARYA", "10000");
	database.insert_intoAcc("MinaFADY", "1234", "MINA FADY", "22", "MATARYA", "10000");
	database.insert_intoAcc("MinaSOBHY", "1234", "MINA SOBHY", "22", "MATARYA", "10000");
	database.insert_intoAcc("MinaFRANSA", "1234", "MINA FRANSA", "22", "MATARYA", "10000");
	database.print_database();
	int id=database.get_clientID("MINA SOBHY");
	cout << "id is " << id << "\n";
	string s = to_string(id);
	database.insert_intoLoan("1000", s);
	database.print_loans();
	//sqlite3 * db; sqlite3_open("loan.db", &db);
	//sqlite3_exec(db, ".tables", NULL, 0,0);
	database.insert_intoDeposite("1000", "2");
	database.print_deposites_for("2");
	database.print_database();
	database.insert_intoWithdraw("2000", "3");
	database.insert_intoWithdraw("12000", "1");
	database.print_database();
	database.print_deposites();
	database.print_withdraws();
	database.close_database();*/
	System sys = System();
	Client clients[5] = { Client(2),Client(2),Client(3)  };
		for (int i = 0; i < 5; ++i) {
	sys.add(clients[i]);

	}

		map<string, string> logins;
		//databaseUtils database = databaseUtils();
		database.get_logins(&logins);

		map<string, string>::iterator i;
		for (i = logins.begin(); i != logins.end(); i++) {
			cout << i->first << "  = " << i->second << "\n";
		}
		database.print_database();
		Clerk clerk = Clerk(sys, database, &logins);
		database.print_database();
	/*database.print_database();
	database.print_loans();
	database.print_withdraws();
	database.print_withdraws();*/
	return 0;
}


