#include "databaseUtils.h"
#include"sqlite3.h"



sqlite3 *db;
char *zErrMsg = 0;
int status;
char * sql;
std::map<std::string, std::string>:: iterator logins;
/*char * userName = "userName";
char * password = "password"; 
char * name = "clientName";
char * age = "age";
char * address = "address";
char * balance = "balance";*/
databaseUtils::databaseUtils()
{
	create_database();
}


databaseUtils::~databaseUtils()
{
	close_database();
}
int databaseUtils::open_database(char* s) {
	status = sqlite3_open(s, &db);
	if (status) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	return status;
}

 int databaseUtils::printAll(void *dataToBePrinted, int numOfColums, char **columValue, char **columnName) {
	printf("printAll \n");
	int i;
	for (i = 0; i<numOfColums; i++) {
		printf("%s = %s\n", columnName[i], columValue[i] ? columValue[i] : "NULL");
	}
	printf("\n");
	return 0;
}
 int databaseUtils::getID(void *id, int numOfColums, char **columValue, char **columnName) {
	 printf("getID \n");
	
	*((int*)id) = atoi(columValue[0]);
	std::cout << "ID from getID " << *((int*)id)<<"\n";
	 return 0;
 }


 void databaseUtils::close_database() {
	 sqlite3_close(db);
 }
 void databaseUtils::create_accTable() {
	 sql = "CREATE TABLE IF NOT EXISTS account ("\
		 "ID integer primary key autoincrement , userName text not null , password text not null , clientName text not null " \
		 ", age integer not null , address text not null , balance real not null default 0.0  );";
	 open_database("account.db");
	 sqlite3_exec(db, sql, printAll, "creating account database", &zErrMsg);
	 
 }
 void  databaseUtils::create_loanTable() {
	 sql = "CREATE TABLE IF NOT EXISTS loan ( loanID integer primary key autoincrement , amount real not null, \
		 date timestamp default current_timestamp , "\
		 " ID  integer not null , FOREIGN KEY(ID) REFERENCES account (ID) );";
	 open_database("loan.db");
	 sqlite3_exec(db, sql, printAll, "creating loan database", &zErrMsg);

 }
 void  databaseUtils::create_depositeTable() {
	 sql= "CREATE TABLE IF NOT EXISTS deposite ( depositeID integer primary key autoincrement ,"\
		 "date timestamp default current_timestamp , "\
		 " amount real not null , ID  integer not null , FOREIGN KEY(ID) REFERENCES account (ID) );";
	 open_database("deposite.db");
	 sqlite3_exec(db, sql, printAll, "creating deposite database", &zErrMsg);
 }
 void  databaseUtils::create_withdrawTable() {
	 sql = "CREATE TABLE IF NOT EXISTS withdraw ( withdrawID integer primary key autoincrement ,amount real not null, "\
		 "date timestamp default current_timestamp , "\
		 "  ID  integer not null , FOREIGN KEY(ID) REFERENCES account (ID) );";
	 open_database("withdraw.db");
	 sqlite3_exec(db, sql, printAll, "creating withdraw database", &zErrMsg);
 }

 void  databaseUtils::create_database() {
	 create_accTable();
	 create_depositeTable();
	 create_loanTable();
	 create_withdrawTable();
	 
 }

 void databaseUtils::check_operation(int status) {
	 if (status != SQLITE_OK) {
		 fprintf(stderr, "SQL error: %s\n", zErrMsg);
		 sqlite3_free(zErrMsg);
	 }
	 else {
		 fprintf(stdout, "Operation done successfully\n");
	 }
 }

 void databaseUtils::insert_intoAcc(std::string userName, std::string password,
	 std::string name, std::string age, std::string address, std::string balance) {
	 
	 
	 std::string s = "INSERT INTO account( userName , password , clientName , age , address , balance )  VALUES( \""
		 + userName + "\" , \"" + password + "\" , \"" + name + "\" , " + age + " , \"" + address + "\" , " + balance + " );";

	 std::cout << s << "\n";
	 char* statement = new char[s.length() + 1];
	 strcpy(statement, s.c_str());
	 open_database("account.db");

	 status=sqlite3_exec(db, statement, printAll, "Account Table ", &zErrMsg);
	 check_operation(status);
	 //print_database();
	 delete[] statement;
 }

 void databaseUtils::insert_intoLoan(std::string amount,std::string id) {
	 open_database("loan.db");
	 //loanID primary key autoincrement , date timestamp default current_timestamp , "\
		 " ID  integer not null , FOREIGN KEY(ID) REFERENCES account (ID) );"
	 std::string s = "INSERT INTO loan( amount , ID )  VALUES( " + amount + " , " + id +" );";
	 char* statement = new char[s.length() + 1];
	 strcpy(statement, s.c_str());
	 sqlite3_exec(db, statement, printAll, 0, &zErrMsg);
	 delete[] statement;
 }

 void databaseUtils::insert_intoDeposite(std::string amount, std::string id) {
	 open_database("deposite.db");
	 //loanID primary key autoincrement , date timestamp default current_timestamp , "\
	 		 " ID  integer not null , FOREIGN KEY(ID) REFERENCES account (ID) );"
	 std::string s = "INSERT INTO deposite ( amount , ID )  Values ( " + amount + " , " + id + " );";
	 char* statement = new char[s.length() + 1];
	 strcpy(statement, s.c_str());
	 sqlite3_exec(db, statement, printAll, 0, &zErrMsg);
	 update_balance(atof(amount.c_str()), id);
	 delete[] statement;

 }
 void databaseUtils::insert_intoWithdraw(std::string amount, std::string id) {

	 open_database("account.db");
	 std::string m = "SELECT balance FROM account WHERE ID = " + id + " ;";
	 char* statment = new char[m.length() + 1];
	 strcpy(statment, m.c_str());
	 double * balance = new double;
	 *balance = 0.0;
	 sqlite3_exec(db, statment, get_balance, (void *)balance, &zErrMsg);
	 sqlite3_exec(db, statment, get_balance, (void *)balance, &zErrMsg);
	 if (*balance < atof(amount.c_str())) {
		 std::cout << "No enough money in the account \n current balance  " << *balance << "\n";
		 delete balance;
		 return;
	 }
	 delete balance;
	 open_database("withdraw.db");
	 std::string s = "INSERT INTO withdraw ( amount , ID )  Values ( " + amount + " , " + id + " );";

	 char* statement = new char[s.length() + 1];
	 strcpy(statement, s.c_str());
	 sqlite3_exec(db, statement, printAll, 0, &zErrMsg);
	 update_balance((atof(amount.c_str())*-1), id);
	 delete[] statement;
 }



 int databaseUtils::get_clientID(std::string name) {
	 std::cout << "get_clientID \n";
	// sqlite3_open("account.db", &db);
	 std::string s = "SELECT * FROM account WHERE userName =\"" + name + "\" ;";

	 printf("%s \n", s.c_str());
	 int* id=new int;
	 *id = 0;
	 open_database("account.db");
	 int status=sqlite3_exec(db, s.c_str(), getID,(void *) id, &zErrMsg);
	 check_operation(status);
	 std::cout << *id << "\n";
	 return *id;
 }
 /*Printing different tables */
 void  databaseUtils::print_database() {
	 sql = "SELECT * FROM account  ;";
	 open_database("account.db");
	 status = sqlite3_exec(db, sql, printAll, "Account Table", &zErrMsg);
	 check_operation(status);
	 printf("print_database \n");
 }

 void databaseUtils::print_loans() {
	 // open_database("loan.db");
	 sqlite3_open("loan.db", &db);
	 sql = "SELECT * FROM loan ;";

	 int status = sqlite3_exec(db, sql, printAll, "Loan ", &zErrMsg);
	 check_operation(status);

 }
 void databaseUtils::print_loans_for(std::string id) {

	 open_database("loan.db");
	 std::string s = "SELECT * FROM loan WHERE ID = " + id + " ; ";
	 strcpy(sql, s.c_str());

	 int status = sqlite3_exec(db, sql, printAll, "Loan ", &zErrMsg);
	 check_operation(status);
 }

 void databaseUtils::print_deposites_for(std::string id) {
	
	 open_database("deposite.db");
	 std::string s = "SELECT * FROM deposite WHERE ID = " + id + " ; ";
	 char* statment = new char[s.length() + 1];
	 strcpy(statment, s.c_str());

	 int status = sqlite3_exec(db, statment, printAll, "Loan ", &zErrMsg);
	 check_operation(status);
	 delete[] statment;
 }

 void databaseUtils::print_withdraws_for(std::string id) {

	 open_database("withdraw.db");
	 std::string s = "SELECT * FROM withdraw WHERE ID = " + id + " ; ";


	 int status = sqlite3_exec(db, s.c_str(), printAll, "withdraw ", &zErrMsg);
	 check_operation(status);

 }

 void databaseUtils::print_withdraws() {
	 open_database("withdraw.db");
	 std::string s = "SELECT * FROM withdraw  ; ";
	 int status = sqlite3_exec(db, s.c_str(), printAll, "withdraw ", &zErrMsg);
	 check_operation(status);

 }

 void databaseUtils::print_deposites() {
	 open_database("deposite.db");
	 std::string s = "SELECT * FROM deposite  ; ";
	 int status = sqlite3_exec(db, s.c_str(), printAll, "deposite ", &zErrMsg);
	 check_operation(status);
 }
 void databaseUtils::update_balance(double amount,std::string id) {
	 open_database("account.db");
	 std::string m = "SELECT balance FROM account WHERE ID = " + id + " ;";
	 char* statment = new char[m.length() + 1];
	 strcpy(statment, m.c_str());
	 double * balance=new double;
	 *balance = 0.0;
	 sqlite3_exec(db, statment, get_balance, (void *)balance, &zErrMsg);
	 printf("balance after account %f \n", *balance);

	 double total = amount + *balance;
	 //printf("balance after adding %f \n", total);
	 m = std::to_string(total);
	 std::string s = "UPDATE account SET balance = " + m + " WHERE ID = " + id + " ;";
	 std::cout << s << "\n";
	 sqlite3_exec(db, s.c_str(), printAll, "Update Balance ", &zErrMsg);
	 balance = nullptr;
	 delete balance;
	 delete[]statment;
 }

 int databaseUtils::get_balance(void *balance, int numOfColums, char **columValue, char **columnName) {
	 *((double*)balance) = atof(columValue[0]);
	 return 0;
 }

 void databaseUtils::get_logins(std::map<std::string, std::string> * m) {
	 open_database("account.db");
	 std::string s = "SELECT userName , password FROM account ;";


	 sqlite3_stmt *statement;


 if (sqlite3_prepare_v2(db, s.c_str(), -1, &statement, 0) == SQLITE_OK)

	 {

	 int cols = sqlite3_column_count(statement);
		 

	 int result = 0;

	 while (true)

	 {
		 result = sqlite3_step(statement);

		 if (result == SQLITE_ROW)
		 {
		    std::string s[2];

		       for (int col = 0; col < cols; col++) {
			 s[col] = (char*)sqlite3_column_text(statement, col);
			       
			 }
			 (*m).insert(std::pair<std::string, std::string>(s[0], s[1]));
		 }

		 else
		 {
			 break;
		 }
           }

	 sqlite3_finalize(statement);
	 }

	 std::string error = sqlite3_errmsg(db);

	 if (error != "not an error") std::cout << s << " " << error << "\n";

 }
