#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Food {
protected:
    double basePrice;
    string name;
    double step;

public:
    Food (double bp, cs n, double s) : basePrice(bp), name(n), step(s){}
};

class Drink:public Food {
private:
    double volume;

public:
    Drink (double basePrice, cs name, double volume) : Food(basePrice,name,10), volume(volume) {}
};

class Dessert:public Food {
private:
    double calories;

public:
    Dessert (double basePrice, cs name, double calories) : Food(basePrice,name,50), calories(calories) {}
};

class Main:public Food {
private:
    double weight;

public:
    Main (double basePrice, cs name, double weight) : Food(basePrice,name,50), weight(weight) {}
};

// Controller
class Menu {
private:
    unordered_map<string, Drink> drinks;
    unordered_map<string, Dessert> desserts;
    unordered_map<string, Main> mains;
    static double totalPrice;

public:
    // Static functions for static variables
    static double getTotalPrice();
    static void changeTotalPrice(double price, bool sum);

    // Add drink
    int addDrink(double price, cs name, double volume) {
        if (drinks.find(name) != drinks.end()) {
            return 1;
        }
        Drink drink(price,name,volume);
        drinks.emplace(name,drink);
        changeTotalPrice(price,true);
        return 2;
    }

    // Add dessert
    int addDessert(double price, cs name, double calories) {
        if (desserts.find(name) != desserts.end()) {
            return 1;
        }
        Dessert dessert(price,name,calories);
        desserts.emplace(name,dessert);
        changeTotalPrice(price,true);
        return 2;
    }

    int addMain(double price, cs name, double weight) {
        if (mains.find(name) != mains.end()) {
            return 1;
        }
        Main main(price,name,weight);
        mains.emplace(name,main);
        changeTotalPrice(price,true);
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

            // Add drinks
            if (ussr[0] == "add" && ussr[1] == "drink" && ussr.size() == 5) {
                string name = ussr[2];
                double price = stod(ussr[3]);
                double volume = stod(ussr[4]);
                int status = menu.addDrink(price,name,volume);
                switch (status) {
                    case 1:
                        cout << "Item already exists." << endl;
                        break;
                    case 2:
                        cout << name << " added!" << endl;
                        break;
                }
            }

            // Add dessert
            else if (ussr[0] == "add" && ussr[1] == "dessert" && ussr.size() == 5) {
                string name = ussr[2];
                double price = stod(ussr[3]);
                double calories = stod(ussr[4]);
                int status = menu.addDessert(price,name,calories);
                switch (status) {
                    case 1:
                        cout << "Item already exists." << endl;
                        break;
                    case 2:
                        cout << name << " added!" << endl;
                        break;
                }
            }

            // Add main
            else if (ussr[0] == "add" && ussr[1] == "main" && ussr.size() == 5) {
                string name = ussr[2];
                double price = stod(ussr[3]);
                double weight = stod(ussr[4]);
                int status = menu.addMain(price,name,weight);
                switch (status) {
                    case 1:
                        cout << "Item already exists." << endl;
                    break;
                    case 2:
                        cout << name << " added!" << endl;
                    break;
                }
            }

            // Sum
            else if (ussr[0] == "sum")
                cout << "Total: " << Menu::getTotalPrice << endl;

            // End
            else if (ussr[0] == "end")
                return;

            ussr.clear();
        }
    }
};

double Menu::totalPrice = 0;

double Menu::getTotalPrice() {
    return totalPrice;
}

void Menu::changeTotalPrice(double price,bool sum) {
    if (sum) 
        totalPrice += price;
    else 
        totalPrice -= price;
}

int main() {
    ProcessCommands process;
    process.run();
    return 0;
}