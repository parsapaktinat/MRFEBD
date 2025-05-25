#include <bits/stdc++.h>
using namespace std;

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

    string getDay() const {
        return day;
    }

    string getDoctorName() const {
        return doctorName;
    }

    string getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    void setDay(const string &day) {
        this->day = day;
    }

    void setDoctorName(const string &doctorName) {
        this->doctorName = doctorName;
    }
};

class Doctor {
private:
    string name;
    string specialty;
    int maxNPatient;
    vector<string> workingDays;
    unordered_map<string, vector<string>> schedule;

public:
    Doctor(string _name, string _specialty, int _maxNPatient, const vector<string> &_workingDays) :
    name(_name), specialty(_specialty) {

    };

    void setWorkingDays(const vector<string> &days) {

    }

    string getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    string getSpecialty() const {
        return specialty;
    }

    void setSpecialty(const string &specialty) {
        this->specialty = specialty;
    }
};

class HospitalController {
private:
    static vector<string> validDays;
    static map<string, Doctor> doctors;
    static vector<string> doctorOrder;
    static map<string, Patient> patients;
};

vector<string> HospitalController::validDays;
map<string, Doctor> HospitalController::doctors;
vector<string> HospitalController::doctorOrder;
map<string, Patient> HospitalController::patients;

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