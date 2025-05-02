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

    double deposit(double money) {
        initialBalance += money;
        return initialBalance;
    }

    bool withdraw(double amount) {
        if (initialBalance - amount < 0)
            return false;
        initialBalance -= amount;
        return true;
    }

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

vector<Customer> Customer::customerList;
double BankAccount::taxRate = 0.0;
double BankAccount::annualInterestRate = 0.0;

Customer* findCustomerByAccountNumber(cs accountNumber) {
    for (auto customer : Customer::customerList) {
        if (customer.getAccountNumber() == accountNumber) {
            return &customer;
        }
    }
    return NULL;
}

class Control {
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
    int depositMoney(cs accountNumebr, double money, double &balance) {
        Customer* customer = findCustomerByAccountNumber(accountNumebr);
        if (customer) {
            balance = customer->deposit(money);
            return 1;
        }
    }

    // Withdraw money
    int withdrawMoney(cs accountNumber, double amount, double &balance) {
        Customer* customer = findCustomerByAccountNumber(accountNumber);
        if (!customer->withdraw(amount))
            return 1;
        balance = customer->getInitialBalance();
        return 2;
    }
};

class View {
private:
    Control controller;
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
                double initialBalance = stod(cp[4]);
                int status = controller.addCustomer(name, nationalID, accountNumber, initialBalance);
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
                double balance = 0.0;
                int status = controller.depositMoney(accountNumber,amount,balance);
                if (status == 1) {
                    cout << "Deposit successful. New balance: " << balance << endl;
                }
            }

            // Withdraw money
            if (cp[0] == "withdraw" && cp.size() == 3) {
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                double balance = 0.0;
                int status = controller.withdrawMoney(accountNumber,amount,balance);
                switch (status) {
                    case 1:
                        cout << "Error! Insufficient funds " << endl;
                        break;
                    case 2:
                        cout << "Withdrawal successful. New balance: " << balance << endl;
                        break;
                }
            }

        }
    }
};

int main() {

    return 0;
}