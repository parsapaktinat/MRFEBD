#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// ------------- Exception example ------------------
class NameException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: error output";
    }
};

// ------------- your code goes here ----------------
class Patient{
private:
    string name;
    string doctorName;
    string day;

public:
    Patient() {}

    
};

class Doctor {
private:
    string name;
    string specialty;
    int numberOfPatients;
    vector<string> workingDays;

public:
    Doctor(cs _name, cs _specialty, int _numberOfPatients, const vector<string> &_workingDays) : name(_name), specialty(_specialty), numberOfPatients(_numberOfPatients), workingDays(_workingDays) {};

    string getName() const {return name;}
    string getSpecialty() const {return specialty;}
    int getNumberOfPatients() const {return numberOfPatients;}
    vector<string> getWorkingDays() const {return workingDays;}
};

class HospitalController {
private:
    vector<Doctor> doctors;
};

bool inputHandler(string line, HospitalController &c) {
    string word;
    vector<string> cp;
    stringstream ss(line);
    while (ss >> word) {
        cp.push_back(word);
    }

    // Add doctor
    if (cp[0] == "add" && cp[1] == "doctor" && cp.size() >= 6) {
        string name = cp[2];
        string specialty = cp[3];
        int numberOfPatients = stoi(cp[4]);
        vector<string> workingDays;
        for (int i = 5;i < cp.size();i++) {
            workingDays.push_back(cp[i]);
        }
    }

}

// ------ do not change main() function ------
int main() {
    HospitalController hc;
    string line;
    bool cond = true;
    while (cond) {
        getline(cin, line);
        try {
            cond = inputHandler(line, hc);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}