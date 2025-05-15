#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Food {
protected:
    int basePrice;
    string name;
    int step;

public:
    Food (int bp, cs n, int s) : basePrice(bp), name(n), step(s){}

    int getStep() {
        return step;
    }
};

class Drink:public Food {
private:
    int volume;

public:
    Drink (int basePrice, cs name, int volume) : Food(basePrice,name,10), volume(volume) {}
};

class Dessert:public Food {
private:
    int calories;

public:
    Dessert (int basePrice, cs name, int calories) : Food(basePrice,name,50), calories(calories) {}
};

class Main:public Food {
private:
    int weight;

public:
    Main (int basePrice, cs name, int weight) : Food(basePrice,name,20), weight(weight) {}
};

// Controller
class Menu {
private:
    unordered_map<string, Drink> drinks;
    unordered_map<string, Dessert> desserts;
    unordered_map<string, Main> mains;
    static int totalPrice;

public:
    // Static functions for static variables
    static int getTotalPrice();
    static void changeTotalPrice(int price, bool sum);

    // Add drink
    int addDrink(int price, cs name, int volume) {
        if (drinks.find(name) != drinks.end()) {
            return 1;
        }
        Drink drink(price,name,volume);
        drinks.emplace(name,drink);
        price += volume/drink.getStep();
        Menu::changeTotalPrice(price,true);
        return 2;
    }

    // Add dessert
    int addDessert(int price, cs name, int calories) {
        if (desserts.find(name) != desserts.end()) {
            return 1;
        }
        Dessert dessert(price,name,calories);
        desserts.emplace(name,dessert);
        price += calories/dessert.getStep();
        Menu::changeTotalPrice(price,true);
        return 2;
    }

    int addMain(int price, cs name, int weight) {
        if (mains.find(name) != mains.end()) {
            return 1;
        }
        Main main(price,name,weight);
        mains.emplace(name,main);
        price += weight/main.getStep();
        Menu::changeTotalPrice(price,true);
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
                int price = stod(ussr[3]);
                int volume = stod(ussr[4]);
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
                int price = stod(ussr[3]);
                int calories = stod(ussr[4]);
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
                int price = stod(ussr[3]);
                int weight = stod(ussr[4]);
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
                cout << "Total: " << Menu::getTotalPrice() << endl;

            // End
            else if (ussr[0] == "end")
                return;

            ussr.clear();
        }
    }
};

int Menu::totalPrice = 0;

int Menu::getTotalPrice() {
    return totalPrice;
}

void Menu::changeTotalPrice(int price,bool sum) {
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