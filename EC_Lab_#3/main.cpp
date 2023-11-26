#include <iostream>
#include <string>
using namespace std;

//prototypes
class SavingsAccount;
class CurrentAccount;

//Account class
//base class for SavingsAccount class and CurrentAccount class
class Account {
public:
  string accountNumber = "";
  string accountHolder = "";
  double balance = 0;

  void displayDetails() {
    cout << "(ID: " << accountNumber << ")" << endl;
    cout << "Holder: " << accountHolder << endl;
    cout << "Balance: $" << balance << endl;
  };

  void deposit(int amount) { balance += amount; };

  void withdraw(int amount) {
    if (balance - amount > 0) {
      balance -= amount;
    } else {
      cout << "You can not withdraw that amount." << endl;
    };
  };
};

//SavingsAccount class
//child class of Account
class SavingsAccount : public Account {
public:
  int interestRate = 0;
  int minimumBalance = 1200;
  SavingsAccount(string id, string name, double bal, int rate) {
    accountNumber = id;
    accountHolder = name;
    balance = bal;
    interestRate = rate;
  };

  void withdraw(int amount) {
    if (balance - amount < minimumBalance) {
      cout << "You can not withdraw that amount." << endl;
    } else {
      balance -= amount;
    };
  };

  void displayDetails() {
    cout << "Account Details for Savings Account";
    Account::displayDetails();
    cout << "Interest Rate: " << interestRate << "%" << endl;
  };

  friend ostream & operator << (ostream &out, const SavingsAccount &account);
  friend SavingsAccount operator+(SavingsAccount &sa, CurrentAccount &ca);
};

// CurrentAccount class
// child class of Account
class CurrentAccount : public Account {
public:
  int overdraftLimit = 0;

  CurrentAccount(string id, string name, double bal, int limit) {
    accountNumber = id;
    accountHolder = name;
    balance = bal;
    overdraftLimit = limit;
  };

  void withdraw(int amount) {
    if (amount < overdraftLimit + balance) {
      balance -= amount;
    } else {
      cout << "You can not withdraw that amount." << endl;
    };
  };

  void displayDetails() {
    cout << "Account Details for Current Account";
    Account::displayDetails();
    cout << "Overdraft Limit: %" << overdraftLimit << endl;
  };

  friend ostream & operator << (ostream &out, const CurrentAccount &account);
  friend CurrentAccount operator+(CurrentAccount &ca, SavingsAccount &sa);
};

//overloading << operator
ostream & operator << (ostream &out, const SavingsAccount &account){
  out << "Account Details for Savings Account (ID: " << account.accountNumber << ")" << endl;
  out << "Holder: " << account.accountHolder << endl;
  out << "Balance: $" << account.balance << endl;
  out << "Interest Rate: " << account.interestRate << "%" << endl;
  return out;
};
ostream & operator << (ostream &out, const CurrentAccount &account){
  out << "Account Details for Current Account (ID: " << account.accountNumber << ")" << endl;
  out << "Holder: " << account.accountHolder << endl;
  out << "Balance: $" << account.balance << endl;
  out << "Overdraft Limit: $" << account.overdraftLimit << endl;
  return out;
};

//overloading + operator
CurrentAccount operator+(CurrentAccount &ca, SavingsAccount &sa){
  int temp = sa.balance - sa.minimumBalance;
  int bal = ca.balance + temp;
  sa.balance = sa.minimumBalance;
  return CurrentAccount(ca.accountNumber, ca.accountHolder, bal, ca.overdraftLimit);
};
SavingsAccount operator+(SavingsAccount &sa, CurrentAccount &ca){
  int bal = sa.balance + ca.balance;
  ca.balance = 0;
  return SavingsAccount(sa.accountNumber, sa.accountHolder, bal, sa.interestRate);
};

// main
int main() {
  // make SavingsAccount object and CurrentAccount object
  SavingsAccount savings("S123", "John Doe", 1000, 20);
  CurrentAccount current("C456", "Jane Doe", 2000, 500);

  //print savings and current by function
  savings.displayDetails();
  cout << endl;
  current.displayDetails();
  cout << endl << endl;

  //despoit and withdraw
  savings.deposit(500);
  current.withdraw(1000);
  
  //print savings and current by overloading << operator
  cout << "Account Details after deposit and withdrawal:" << endl;
  cout << savings << endl;
  cout << current << endl << endl;

  // Transfer 300 from savings to current
  //using overloading + operator
  current = current + savings;

  //print savings and current after transfer
  cout << "Account Details after transfer:" << endl;
  savings.displayDetails();
  cout << endl;
  current.displayDetails();
  cout << endl << endl;

  //transfer 500 from current to savings
  //using overloading + operator
  savings = savings + current;

  //print savings and current after transfer
  cout << "Account Details after transfer:" << endl;
  savings.displayDetails();
  cout << endl;
  current.displayDetails();
  cout << endl << endl;

  return 0;
};