#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class Rental {
protected:
    int ID;

public:
    Rental(int id) : ID(id) {}

    int getID() const {
        return ID;
    }
};

class CarRental : public Rental {
private:
    int dailyRate;
    int days;

public:
    CarRental(int id, int dailyRate, int days) : Rental(id) , dailyRate(dailyRate), days(days) {}

    int claculateCost() {
        int cost = days * dailyRate;
        if (days > 5) {
            cost = (cost*9)/10;
        }
        return cost;
    }
};

class BikeRental : public Rental {
private:
    int hourlyRate;
    int hours;

public:
    BikeRental(int id, int hr, int h) : Rental(id), hourlyRate(hr), hours(h) {}

    int claculateCost() {
        int cost = hours * hourlyRate;
        return cost;
    }
};

class ProcessCommand {
private:
    vector<CarRental> cars;
    vector<BikeRental> bikes;

public:
    ProcessCommand() {}

    bool addCar(int id, int dailyRate, int days) {
        for (auto car : cars) {
            if (car.getID() == id) {
                return false;
            }
        }

        for (auto bike : bikes) {
            if (bike.getID() == id) {
                return false;
            }
        }

        CarRental newCar(id, dailyRate, days);
        cars.push_back(newCar);
        return true;
    }

    bool addBike(int id, int hourlyRate, int hours) {
        for (auto bike : bikes) {
            if (bike.getID() == id) {
                return false;
            }
        }

        for (auto car : cars) {
            if (car.getID() == id) {
                return false;
            }
        }

        BikeRental newBike(id, hourlyRate, hours);
        bikes.push_back(newBike);
        return true;
    }

    bool printID(int id, int &cost) {
        for (int i = 0;i < cars.size();i++) {
            if (cars[i].getID() == id) {
                cost = cars[i].claculateCost();
                return true;
            }
        }

        for (int i = 0;i < bikes.size();i++) {
            if (bikes[i].getID() == id) {
                cost = bikes[i].claculateCost();
                return true;
            }
        }

        return false;
    }

    int calculateTotal() {
        int sumOfCost = 0;
        for (int i = 0;i < cars.size();i++) {
            sumOfCost += cars[i].claculateCost();
        }
        for (int i = 0;i < bikes.size();i++) {
            sumOfCost += bikes[i].claculateCost();
        }
        return sumOfCost;
    }

    bool deleteID(int id) {
        for (auto it = cars.begin();it != cars.end();it++) {
            if (it->getID() == id) {
                cars.erase(it);
                return true;
            }
        }

        for (auto it = bikes.begin();it != bikes.end();it++) {
            if (it->getID() == id) {
                bikes.erase(it);
                return true;
            }
        }

        return false;
    }
};

int main() {

    string line, word;
    vector<string> cp;
    ProcessCommand process;

    while(true) {
        getline(cin,line);
        stringstream ss(line);

        while (ss >> word) {
            cp.push_back(word);
        }

        if (cp[0] == "add" && cp[1] == "car" && cp.size() == 5) {
            int id = stoi(cp[2]);
            int dailyRate = stoi(cp[3]);
            int days = stoi(cp[4]);
            if (process.addCar(id, dailyRate, days))
                cout << "Rental " << id << " added!" << endl;
            else
                cout << "ID already exists." << endl;
        }

        else if (cp[0] == "add" && cp[1] == "bike" && cp.size() == 5) {
            int id = stoi(cp[2]);
            int hourlyRate = stoi(cp[3]);
            int hours = stoi(cp[4]);
            if (process.addBike(id, hourlyRate, hours))
                cout << "Rental " << id << " added!" << endl;
            else
                cout << "ID already exists." << endl;
        }

        else if (cp[0] == "print" && cp.size() == 2) {
            int id = stoi(cp[1]);
            int cost = 0;
            bool flag = process.printID(id, cost);
            if (flag)
                cout << "Rental " << id << ": " << cost << endl;
            else
                cout << "Rental not found." << endl;
        }

        else if (cp[0] == "total" && cp.size() == 1) {
            cout << "Total: " << process.calculateTotal() << endl;
        }

        else if (cp[0] == "delete" && cp.size() == 2) {
            int id = stoi(cp[1]);
            if (process.deleteID(id))
                cout << "Rental " << id << " deleted." << endl;
            else
                cout << "Rental not found." << endl;
        }

        else if (cp[0] == "end")
            break;

        cp.clear();
    }

    return 0;
}
