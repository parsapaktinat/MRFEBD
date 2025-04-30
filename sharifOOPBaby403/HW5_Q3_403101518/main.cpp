#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class BankAccount {
private:
    static double annualInterestRate;
    static double taxRate;

    static void applyIntesterRateToAll() {

    }

    static void applyTaxToAll() {

    }

    string name;
    string nationalID;
    string accountNumber;
    string initialBalance;
public:
    BankAccount(cs name,cs nationalID, cs accountNumber, cs initialBalance) : name(name), nationalID(nationalID),
    accountNumber(accountNumber), initialBalance(initialBalance) {}

    string getName() const {return name;}
    void setName(cs name) {this->name = name;}
    string getNatioalID() const {return nationalID;}
    void setNationalID(cs name) {this->nationalID = nationalID;}
    string getName() const {return name;}
    void setName(cs name) {this->name = name;}
    string getName() const {return name;}
    void setName(cs name) {this->name = name;}

};

class Customer {
private:
    static vector<BankAccount> customerList;
public:
    int addCustomer(cs name, cs nationalID, cs accountNumber, cs initialBalance) {
        for (auto customer : customerList) {
            if (customer.)
        }

    }
};

class View {
private:
    Customer customer;
public:
    void run() {
        string command,word;
        vector<string> cp;

        while (true) {
            getline(cin, command);
            stringstream ss(command);

            while (ss >> word)
                cp.push_back(word);

            // Add a new customer
            if (cp[0] == "add_customer" && cp.size() == 5) {
                string name = cp[1];
                string nationalID = cp[2];
                string accountNumber = cp[3];
                string initialBalance = cp[4];


            }
        }
    }
};

int main() {

    return 0;
}