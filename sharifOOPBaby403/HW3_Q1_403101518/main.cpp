#include <bits/stdc++.h>
using namespace std;

class Airplane {
private:
    string id;
    int status;
    int bandNumber;

public:
    Airplane(string id) : id(id), status(1), bandNumber(-1) {}

    string getID() {
        return id;
    }
    int getStatus() {
        return status;
    }
    int getBandNumber() {
        return bandNumber;
    }

    void setStatus(int newStatus) {
        status = newStatus;
    }
    void setBandNumber(int newBandNumber) {
        bandNumber = newBandNumber;
    }
};

class ControlTower {
private:
    int numberOfBands;
    unordered_map<string, Airplane> airplanes;
    vector<string> bandsStatus; // FREE or ID of the plane

public:
    ControlTower(int k) : numberOfBands(k) {
        for (int i = 0;i < k;i++) {
            bandsStatus.push_back("FREE");
        }
    }

    void addPlane(const string& id) {
        airplanes.emplace(id, Airplane(id));
    }

    void takeOff(const string& id) {
        if (airplanes.find(id) == airplanes.end()) {
            cout << "YOU ARE NOT HERE" << endl;
            return;
        }

        Airplane *plane = &airplanes.at(id);
        int status = plane->getStatus();

        if (status == 4) {
            cout << "YOU ARE NOT HERE" << endl;
        }
        else if (status == 3) {
            cout << "YOU ARE LANDING NOW" << endl;
        }
        else if (status == 2) {
            cout << "YOU ARE TAKING OFF" << endl;
        }
        else if (status == 1) {
            for (int i = 0;i < numberOfBands;i++) {
                if (bandsStatus[i] == "FREE") {
                    plane->setStatus(2);
                    plane->setBandNumber(i+1);
                    bandsStatus[i] = id;
                    return;
                }
            }
            cout << "NO FREE BAND" << endl;
        }
    }

    void landing(const string& id) {
        if (airplanes.find(id) == airplanes.end()) {
            airplanes.emplace(id, Airplane(id));
            airplanes.at(id).setStatus(4);
        }

        Airplane *plane = &airplanes.at(id);
        int status = plane->getStatus();

        if (status == 1) {
            cout << "YOU ARE HERE" << endl;
        }
        else if (status == 2) {
            cout << "YOU ARE TAKING OFF" << endl;
        }
        else if (status == 3) {
            cout << "YOU ARE LANDING NOW" << endl;
        }
        else if (status == 4) {
            for (int i = numberOfBands-1;i >= 0;i--) {
                if (bandsStatus[i] == "FREE") {
                    plane->setStatus(3);
                    plane->setBandNumber(i+1);
                    bandsStatus[i] = id;
                    return;
                }
            }
            cout << "NO FREE BAND" << endl;
        }
    }

    void planeStatus(const string& id) {
        if (airplanes.find(id) == airplanes.end()) {
            cout << "4" << endl;
            return;
        }
        int status = airplanes.at(id).getStatus();
        cout << status << endl;
    }

    void bandStatus(const int& line) {
        if (line > numberOfBands || line < 0) {
            return;
        }
        string status = bandsStatus[line-1];
        cout << status << endl;
    }
};

int main() {
    int k;
    cin >> k;

    ControlTower controlTower(k);
    string command,num;

    while (true) {
        cin >> command;
        if (command == "ADD-PLANE") {
            cin >> num;
            controlTower.addPlane(num);
        }
        else if (command == "TAKE-OFF") {
            cin >> num;
            controlTower.takeOff(num);
        }
        else if (command == "LANDING") {
            cin >> num;
            controlTower.landing(num);
        }
        else if (command == "PLANE-STATUS") {
            cin >> num;
            controlTower.planeStatus(num);
        }
        else if (command == "BAND-STATUS") {
            cin >> num;
            controlTower.bandStatus(stoi(num));
        }
        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}