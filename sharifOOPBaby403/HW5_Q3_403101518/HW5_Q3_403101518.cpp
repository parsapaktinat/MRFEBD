#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class Customer;
class BankAccount;
class ProcessCommands;
Customer* findCustomerByAccountNumber(cs accountNumber);

class Customer {
private:
    string name;
    string nationalID;
    string accountNumber;
    double balance = 0;

public:
    Customer(string name, string nationalID, string accountNumber, double balance) : name(name), nationalID(nationalID), accountNumber(accountNumber), balance(balance) {};

    static vector<Customer> customerList;

    string getName() const {return name;}
    string getNationalID() const {return nationalID;}
    string getAccountNumber() const {return accountNumber;}
    double getbalance() const {return balance;}

    double deposit(double money) {
        balance += money;
        return balance;
    }

    bool withdraw(double amount) {
        if (balance - amount < 0)
            return false;
        balance -= amount;
        return true;
    }

    void applyInterest(double rate) {
        double interest = balance * rate/100.0;
        balance += interest;
    }

    void applyTax(double rate) {
        double tax = balance * rate/100.0;
        balance -= tax;
    }
};

class BankAccount {
public:
    static double annualInterestRate;
    static double taxRate;

    static void applyIntesterRateToAll();
    static void applyTaxToAll();
};

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
                double balance = stod(cp[4]);
                bool flag = false;

                for (auto customer : Customer::customerList) {
                    if (customer.getName() == name) {
                        cout << "Error! this name is already registered." << endl;
                        flag = true;
                        break;
                    }
                    if (customer.getNationalID() == nationalID) {
                        cout << "Error! this national_ID is already registered." << endl;
                        flag = true;
                        break;
                    }
                    if (customer.getAccountNumber() == accountNumber) {
                        cout << "Error! this accountNumber is already registered." << endl;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    Customer::customerList.emplace_back(name,nationalID,accountNumber,balance);
                    cout << "Customer " << name << " added. Account: " << accountNumber << endl;
                }
            }

            // Deposit money
            else if (cp[0] == "deposit" && cp.size() == 3) {
                cout << fixed << setprecision(2);
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                double balance = 0.0;

                Customer* customer = findCustomerByAccountNumber(accountNumber);
                balance = customer->deposit(amount);
                cout << "Deposit successful. New balance: " << balance << endl;
            }

            // Withdraw money
            else if (cp[0] == "withdraw" && cp.size() == 3) {
                cout << fixed << setprecision(2);
                string accountNumber = cp[1];
                double amount = stod(cp[2]);
                double balance = 0.0;

                Customer* customer = findCustomerByAccountNumber(accountNumber);

                if (!customer->withdraw(amount)) {
                    cout << "Error! Insufficient funds" << endl;
                    cp.clear();
                    continue;
                }

                balance = customer->getbalance();
                cout << "Withdrawal successful. New balance: " << balance << endl;
            }

            // Balance
            else if (cp[0] == "balance" && cp.size() == 2) {
                cout << fixed << setprecision(2);
                Customer* customer = findCustomerByAccountNumber(cp[1]);
                cout << "Account " << cp[1] << " balance: " << customer->getbalance() << endl;
            }

            // Show all customers
            else if (cp[0] == "show_all") {
                cout << fixed << setprecision(2);
                for (auto customer : Customer::customerList) {
                    cout << customer.getName() << " " << customer.getNationalID() << " " << customer.getAccountNumber() << " " << customer.getbalance() << endl;
                }
            }

            // Set interest
            else if (cp[0] == "set_interest") {
                cout << fixed << setprecision(2);
                double interestRate = stod(cp[1]);
                BankAccount::annualInterestRate = interestRate;
                cout << "Interest rate set to " << interestRate << "%" << endl;
            }

            // Set tax
            else if (cp[0] == "set_tax") {
                cout << fixed << setprecision(2);
                double taxRate = stod(cp[1]);
                BankAccount::taxRate = taxRate;
                cout << "Tax rate set to " << taxRate << "%" << endl;
            }

            // Apply interest
            else if (cp[0] == "apply_interest") {
                cout << "Interest applied." << endl;
                BankAccount::applyIntesterRateToAll();
            }

            // Apply tax
            else if (cp[0] == "apply_tax") {
                cout << "Tax applied." << endl;
                BankAccount::applyTaxToAll();
            }

            // Exit
            else if (cp[0] == "exit") {
                cout << "Goodbye!" << endl;
                return;
            }

            // Invalid command
            else
                cout << "invalid command!" << endl;

            cp.clear();
        }
    }
};

vector<Customer> Customer::customerList;
double BankAccount::taxRate = 0.0;
double BankAccount::annualInterestRate = 0.0;

int main() {
    ProcessCommands processCommands;
    processCommands.run();
    return 0;
}

Customer* findCustomerByAccountNumber(cs accountNumber) {
    for (auto &customer : Customer::customerList) {
        if (customer.getAccountNumber() == accountNumber) {
            return &customer;
        }
    }
    return NULL;
}

void BankAccount::applyIntesterRateToAll() {
    cout << fixed << setprecision(2);
    for (Customer &customer:Customer::customerList) {
        double oldBalance = customer.getbalance();
        customer.applyInterest(BankAccount::annualInterestRate);
        double newBalance = customer.getbalance();

        cout << customer.getName() << ": " << oldBalance << " => " << newBalance << endl;
    }
}

void BankAccount::applyTaxToAll() {
    cout << fixed << setprecision(2);
    for (Customer &customer:Customer::customerList) {
        double oldBalance = customer.getbalance();
        customer.applyTax(BankAccount::taxRate);
        double newBalance = customer.getbalance();

        cout << customer.getName() << ": " << oldBalance << " => " << newBalance << endl;
    }
}
