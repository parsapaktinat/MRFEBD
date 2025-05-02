#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class BankAccount;

class Customer {
private:
    string name;
    string nationalID;
    string accountNumber;
    double initialBalance = 0;

public:
    Customer(string name, string nationalID, string accountNumber, double initialBalance) : name(name), nationalID(nationalID), accountNumber(accountNumber) {};

    static vector<Customer> customerList;

    string getName() const {return name;}
    void setName(cs name) {this->name = name;}
    string getNationalID() const {return nationalID;}
    void setNationalID(cs nationalID) {this->nationalID = nationalID;}
    string getAccountNumber() const {return accountNumber;}
    void setAccountNumber(cs accountNumber) {this->accountNumber = accountNumber;}
    double getInitialBalance() const {return initialBalance;}
    void setInitialBalance(double initialBalance) {this->initialBalance = initialBalance;}

};

class BankAccount {
public:
    static double annualInterestRate;
    static double taxRate;

    static void applyIntesterRateToAll() {

    }

    static void applyTaxToAll() {

    }
};

class Control {
private:
    Customer customer;
public:
    // Add new customer
    int addCustomer(cs name, cs nationalID, cs accountNumber, double initialBalance) {
        for (auto customer : Customer::customerList) {
            if (customer.getName() == name)
                return 1;
            if (customer.getNationalID() == nationalID)
                return 2;
            if (customer.getAccountNumber() == accountNumber)
                return 3;
        }
        Customer newCustomer(name,nationalID,accountNumber,initialBalance);
        Customer::customerList.push_back(newCustomer);
        return 4;
    }

    // Deposit money
    int depositMoney(cs accountNumebr, double money) {

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
                int status = customer.addCustomer(name, nationalID, accountNumber, initialBalance);
                switch (status) {
                    case 1:
                        cout << "Error! this name is already registered." << endl;
                        break;
                    case 2:
                        cout << "Error! this national_ID is already registered." << endl;
                        break;
                    case 3:
                        cout << "Error! this accountNumber is already registered." << endl;
                        break;
                    case 4:
                        cout << "Customer " << name << " added. Account: " << accountNumber << endl;
                        break;
                }
            }

            // Deposit money
            if (cp[0] == "deposit" && cp.size() == 3) {
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                int status
            }

        }
    }
};

int main() {

    return 0;
}