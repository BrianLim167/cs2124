/*
  Brian Lim
  rec03.cpp
  Bank account simulator
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct Account_struct;
class Account;
vector<Account_struct> get_accounts1(ifstream& ifs);
vector<Account_struct> get_accounts2(ifstream& ifs);
vector<Account> get_accounts3(ifstream& ifs);
vector<Account> get_accounts4(ifstream& ifs);
vector<Account> run(ifstream& ifs);
void do_account(vector<Account>& bank, string name, unsigned int number);
void do_deposit(vector<Account>& bank, unsigned int number, double amount);
void do_withdrawal(vector<Account>& bank, unsigned int number, double amount);
size_t find_account(unsigned int number, const vector<Account>& bank);
void display_accounts(const vector<Account_struct>& bank);
void display_account(const Account_struct& account);

struct Account_struct {
  string name;
  unsigned int number;
};

class Account {
  class Transaction;
public:
  Account(string new_name, unsigned int new_number) :
    name(new_name), number(new_number) {
    balance = 0;
  }

  string get_name() const {
    return name;
  }

  unsigned int get_number() const {
    return number;
  }

  float get_balance() const {
    return balance;
  }

  void deposit(double amount) {
    history.emplace_back(true, amount);
    balance += amount;
  }

  void withdrawal(double amount) {
    if (amount > balance) {
      cout << "Not enough money left in balance to withdraw $" << amount << "!"
	   << endl;
      return;
    }
    history.emplace_back(false, amount);
    balance -= amount;
  }

  friend ostream& operator<<(ostream& os, const Account& account);
private:
  string name;
  unsigned int number;
  vector<Transaction> history;
  float balance;
  

  class Transaction {
  public:
    Transaction(bool new_is_deposit, double new_amount) :
      is_deposit(new_is_deposit), amount(new_amount) {}

    bool get_is_deposit() const {
      return is_deposit;
    }

    double get_amount() const {
      return amount;
    }
    
    friend ostream& operator<<(ostream& os, const Transaction& transaction) {
      if (transaction.is_deposit) {
	os << " deposit:";
      } else {
	os << " withdraw:";
      }
      os << transaction.amount;
    }
  private:
    bool is_deposit;
    double amount;
  };

};
ostream& operator<<(ostream& os, const Account& account) {
  //os << account.get_name() << " : " << account.get_number();
  os << account.name << " (" << account.number << ") : balance = "
     << account.balance << " {";
  for (size_t i = 0; i < account.history.size(); i++) {
    os << account.history[i];
  }
  os << " }";
  return os;
}

int main() {

  string INPUT_FILE = "bank.txt";

  //1a
  cout << "PART 1A" << endl;
  ifstream ifs(INPUT_FILE.c_str());
  if (!ifs) {
    cerr << "failed to open " << INPUT_FILE << endl;
    exit(1);
  }

  vector<Account_struct> bank1 = get_accounts1(ifs);
  display_accounts(bank1);
  ifs.close();
  cout << "_____________________" << endl;

  //1b
  cout << "PART 1B" << endl;
  bank1.clear();
  ifs.open(INPUT_FILE.c_str());
  if (!ifs) {
    cerr << "failed to open " << INPUT_FILE << endl;
    exit(1);
  }

  bank1 = get_accounts2(ifs);
  display_accounts(bank1);
  ifs.close();
  cout << "_____________________" << endl;

  //2d
  cout << "PART 2D" << endl;
  ifs.open(INPUT_FILE.c_str());
  if (!ifs) {
    cerr << "failed to open " << INPUT_FILE << endl;
    exit(1);
  }

  vector<Account> bank2 = get_accounts3(ifs);
  for (size_t i = 0; i < bank2.size(); i++) {
    cout << bank2[i] << endl;
  }
  ifs.close();
  cout << "_____________________" << endl;

  //2e
  cout << "PART 2E" << endl;
  bank2.clear();
  ifs.open(INPUT_FILE.c_str());
  if (!ifs) {
    cerr << "failed to open " << INPUT_FILE << endl;
    exit(1);
  }

  bank2 = get_accounts4(ifs);
  for (size_t i = 0; i < bank2.size(); i++) {
    cout << bank2[i] << endl;
  }
  ifs.close();
  cout << "_____________________" << endl;

  //3
  cout << "PART 3" << endl;
  bank2.clear();
  ifs.open(INPUT_FILE.c_str());
  if (!ifs) {
    cerr << "failed to open " << INPUT_FILE << endl;
    exit(1);
  }

  bank2 = run(ifs);
  for (size_t i = 0; i < bank2.size(); i++) {
    cout << bank2[i] << endl;
  }
  ifs.close();
  cout << "_____________________" << endl;
  
}

//displays all accounts in bank
void display_accounts(const vector<Account_struct>& bank) {
  
  for (size_t i = 0; i < bank.size(); i++) {
    display_account(bank[i]);
  }
  
}

//displays an account
void display_account(const Account_struct& account) {
  cout << account.name << " : " << account.number << endl;
}

//read in file contents to a list of its lines account structs
vector<Account_struct> get_accounts1(ifstream& ifs) {

  vector<Account_struct> buf;

  string token;
  while(ifs >> token) {
    if (token == "Account") {
      //tokenize the line to read its contents into a new account
      string name;
      unsigned int number;
      ifs >> name >> number;
      Account_struct new_account;
      new_account.name = name;
      new_account.number = number;
      buf.push_back(new_account);
    }
  }

  return buf;

}
//read in file contents to a list of its lines account structs
vector<Account_struct> get_accounts2(ifstream& ifs) {

  vector<Account_struct> buf;

  string token;
  while (ifs >> token) {
    //tokenize the line to read its contents into a new account
    if (token == "Account") {
      string name;
      unsigned int number;
      ifs >> name >> number;
      Account_struct new_account{name,number};
      buf.push_back(new_account);
    }
  }

  return buf;

}
//read in file contents to a list of its lines account structs
vector<Account> get_accounts3(ifstream& ifs) {

  vector<Account> buf;

  string token;
  while (ifs >> token) {
    //tokenize the line to read its contents into a new account
    if (token == "Account") {
      string name;
      unsigned int number;
      ifs >> name >> number;
      buf.push_back(Account(name, number));
    }
  }

  return buf;

}
//read in file contents to a list of its lines account structs
vector<Account> get_accounts4(ifstream& ifs) {

  vector<Account> buf;

  string token;
  while (ifs >> token) {
    //tokenize the line to read its contents into a new account
    if (token == "Account") {
      string name;
      unsigned int number;
      ifs >> name >> number;
      buf.emplace_back(name, number);
    }
  }

  return buf;

}

//handle any commands from the given file
vector<Account> run(ifstream& ifs) {

  vector<Account> bank;

  string token;
  while (ifs >> token) {
    if (token == "Account") {
      string name;
      unsigned int number;
      ifs >> name >> number;
      do_account(bank, name, number);
    } else if (token == "Deposit") {
      unsigned int number;
      double amount;
      ifs >> number >> amount;
      do_deposit(bank, number, amount);
    } else if (token == "Withdraw") {
      unsigned int number;
      double amount;
      ifs >> number >> amount;
      do_withdrawal(bank, number, amount);
    }
  }

  return bank;
  
}
  
    

//do the account user command
void do_account(vector<Account>& bank, string name, unsigned int number) {
  bank.emplace_back(name, number);
}

//do the deposit user command
void do_deposit(vector<Account>& bank, unsigned int number, double amount) {
  size_t i = find_account(number, bank);
  bank[i].deposit(amount);
}

//do the withdrawal user command
void do_withdrawal(vector<Account>& bank, unsigned int number, double amount) {
  size_t i = find_account(number, bank);
  bank[i].withdrawal(amount);
}

//find the index of the given account number
size_t find_account(unsigned int number, const vector<Account>& bank) {
  size_t i;
  for (i = 0; i < bank.size(); i++) {
    if (bank[i].get_number() == number) {
      return i;
    }
  }
  return i;
}
