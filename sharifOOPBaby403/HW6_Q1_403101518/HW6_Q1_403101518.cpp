#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Food {
protected:
    int finalPrice;
    string name;
    int step;

public:
    Food (int bp, cs n, int s) : finalPrice(bp), name(n), step(s) {}

    int getStep() {
        return step;
    }

    int getfinalPrice() {
        return finalPrice;
    }
};

class Drink:public Food {
private:
    int volume;

public:
    Drink (int bPrice, cs name, int v) : Food(bPrice,name,10), volume(v) {
        finalPrice += volume/step;
    }
};

class Dessert:public Food {
private:
    int calories;

public:
    Dessert (int bPrice, cs name, int c) : Food(bPrice,name,50), calories(c) {
        finalPrice += calories/step;
    }
};

class Main:public Food {
private:
    int weight;

public:
    Main (int bPrice, cs name, int w) : Food(bPrice,name,20), weight(w) {
        finalPrice += weight/step;
    }
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
        Menu::changeTotalPrice(drink.getfinalPrice(),true);
        return 2;
    }

    // Add dessert
    int addDessert(int price, cs name, int calories) {
        if (desserts.find(name) != desserts.end()) {
            return 1;
        }
        Dessert dessert(price,name,calories);
        desserts.emplace(name,dessert);
        Menu::changeTotalPrice(dessert.getfinalPrice(),true);
        return 2;
    }

    // Add main
    int addMain(int price, cs name, int weight) {
        if (mains.find(name) != mains.end()) {
            return 1;
        }
        Main main(price,name,weight);
        mains.emplace(name,main);
        Menu::changeTotalPrice(main.getfinalPrice(),true);
        return 2;
    }

    // Print final price
    int printFinalPrice(cs name, int& price) {
        string status = findInMaps(name);
        if (status == "nothing") 
            return 1;
        else {
            if (status == "drink")
                price = drinks.at(name).getfinalPrice();
            else if (status == "dessert")
                price = desserts.at(name).getfinalPrice();
            else if (status == "main")
                price = mains.at(name).getfinalPrice();
        }
        return 2;
    }

    // Delete Food
    int deleteFood(cs name) {
        string status = findInMaps(name);
        if (status == "nothing")
            return 1;
        else {
            if (status == "drink"){
                Menu::changeTotalPrice(drinks.at(name).getfinalPrice(),false);
                drinks.erase(name);
            }
            else if (status == "dessert"){
                Menu::changeTotalPrice(desserts.at(name).getfinalPrice(),false);
                desserts.erase(name);
            }
            else if (status == "main"){
                Menu::changeTotalPrice(mains.at(name).getfinalPrice(),false);
                mains.erase(name);
            }
        }
        return 2;
    }

    // helper function
    string findInMaps(cs name) {
        string result;
        if (drinks.find(name) == drinks.end() && desserts.find(name) == desserts.end() && mains.find(name) == mains.end())
            result = "nothing";
        else if (drinks.find(name) != drinks.end())
            result = "drink";
        else if (desserts.find(name) != desserts.end())
            result = "dessert";
        else if (mains.find(name) != mains.end())
            result = "main";
        return result;
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

            // Print final price
            else if (ussr[0] == "print" && ussr.size() == 2) {
                string name = ussr[1];
                int price = 0;
                int status = menu.printFinalPrice(name,price);
                switch (status) {
                    case 1:
                        cout << "Item doesn't exist." << endl;
                        break;
                    case 2:
                        cout << name << ": " << price << endl;
                        break;
                }
            }

            // Sum
            else if (ussr[0] == "sum")
                cout << "Total: " << Menu::getTotalPrice() << endl;

            // Delete food
            else if (ussr[0] == "delete" && ussr.size() == 2) {
                string name = ussr[1];
                int status = menu.deleteFood(name);
                switch (status) {
                    case 1:
                        cout << "Item doesn't exist." << endl;
                        break;
                    case 2:
                        cout << name << " deleted." << endl;
                        break;
                }
            }

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