#include <bits/stdc++.h>
using namespace std;

class BankAccount {
private:
    static double annualInterestRate;
    static double taxRate;

    static void applyIntesterRateToAll() {

    }

    static void applyTaxToAll() {

    }
};

class Customer {
private:
    static vector<BankAccount> customerList;
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

        }
    }
};

int main() {

    return 0;
}