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

class ProcessCommands {
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
                bool flag = false;

                for (auto customer : Customer::customerList) {
                    if (customer.getName() == name) {
                        cout << "Error! this name is already registered." << endl;
                        flag = true;
                        break;
                    }
                    else if (customer.getNationalID() == nationalID) {
                        cout << "Error! this national_ID is already registered." << endl;
                        flag = true;
                        break;
                    }
                    else if (customer.getAccountNumber() == accountNumber) {
                        cout << "Error! this accountNumber is already registered." << endl;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    Customer newCustomer(name,nationalID,accountNumber,initialBalance);
                    Customer::customerList.push_back(newCustomer);
                    cout << "Customer " << name << " added. Account: " << accountNumber << endl;
                }
            }

            // Deposit money
            if (cp[0] == "deposit" && cp.size() == 3) {
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                double balance = 0.0;

                Customer* customer = findCustomerByAccountNumber(accountNumber);
                balance = customer->deposit(amount);
                cout << "Deposit successful. New balance: " << balance << endl;
            }

            // Withdraw money
            if (cp[0] == "withdraw" && cp.size() == 3) {
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                double balance = 0.0;

                Customer* customer = findCustomerByAccountNumber(accountNumber);

                if (!customer->withdraw(amount)) {
                    cout << "Error! Insufficient funds" << endl;
                    continue;
                }

                balance = customer->getInitialBalance();
                cout << "Withdrawal successful. New balance: " << balance << endl;
            }

            // Balance
            if (cp[0] == "balance" && cp.size() == 2) {
                Customer* customer = findCustomerByAccountNumber(cp[1]);
                cout << "Account " << cp[1] << " balance: " << customer->getAccountNumber() << endl;
            }

            // Show all customers
            if (cp[0] == "show_all") {
                for (auto customer : Customer::customerList) {
                    cout << customer.getName() << " " << customer.getNationalID() << " " << customer.getAccountNumber() << " " << customer.getInitialBalance() << endl;
                }
            }

            //

        }
    }
};

int main() {

    return 0;
}