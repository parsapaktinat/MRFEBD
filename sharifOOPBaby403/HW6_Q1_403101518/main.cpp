#include <bits/stdc++.h>
using namespace std;

#define cs const string &

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

class Menu {
private:
    unordered_map<string, Drink> drinks;
    unordered_map<string, Dessert> desserts;
    unordered_map<string, Main> mains;

public:
    int addDrink(cs name, double price, double volume) {
        if ()
    }
};

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

            while (ss >> word) {
                ussr.push_back(word);
            }

            if (ussr[0] == "add" && ussr[1] == "drink") {
                string name = ussr[2];
                double price = stod(ussr[3]);
                double volume = stod(ussr[4]);

            }

            else if (ussr[0] == "end")
                return;

            ussr.clear();
        }
    }
};

int main() {

    return 0;
}