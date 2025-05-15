#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Food {
protected:
    double basePrice;
    double step;
    string name;


public:
    Food (double bp, double s, cs n) : basePrice(bp), step(s), name(n) {}

};

class Drink:public Food {
private:
    double volume;

public:
    Drink (double basePrice, cs name, double volume) : Food(basePrice,10,name), volume(volume)  {}


};

class Dessert:public Food {

};

class Main:public Food {

};

// Controller
class Menu {
private:
    unordered_map<string, Drink> drinks;
    unordered_map<string, Dessert> desserts;
    unordered_map<string, Main> mains;

public:
    // Add drink
    int addDrink(cs name, double price, double volume) {
        if (drinks.find(name) != drinks.end()) {
            return 1;
        }
        Drink drink(price,name,volume);
        drinks.emplace(name,drink);
        return 2;
    }


};

// View
class ProcessCommands {
private:
    Menu menu;
public:
    void run() {
        string command, word;
        vector<string> ussr;

        while (true) {
            getline(cin, command);
            stringstream ss(command);

            while (ss >> word)
                ussr.push_back(word);

            if (ussr[0] == "add" && ussr[1] == "drink") {
                string name = ussr[2];
                double price = stod(ussr[3]);
                double volume = stod(ussr[4]);
                int status = menu.addDrink(name,price,volume);
                switch (status) {
                    case 1:
                        cout << "Item already exists." << endl;
                        break;
                    case 2:
                        cout << name << " added!" << endl;
                        break;
                }
            }

            else if (ussr[0] == "end")
                return;

            ussr.clear();
        }
    }
};

int main() {
    ProcessCommands process;
    process.run();
    return 0;
}