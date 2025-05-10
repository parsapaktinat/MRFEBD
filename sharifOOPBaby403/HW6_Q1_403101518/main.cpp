#include <bits/stdc++.h>
using namespace std;

class Food {
protected:
    double basePrice = 0;
    double step = 0;
    string name;

public:
    Food (double bp, double s, string n) : basePrice(bp), step(s), name(n) {}

};

class Drink:public Food {
private:
    double volume = 0;

public:
    Drink (double basePrice, double step, string name, double volume) : Food(basePrice,step,name), volume(volume)  {}
    
};

class Dessert:public Food {

};

class Main:public Food {

};

class ProcessCommands {
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