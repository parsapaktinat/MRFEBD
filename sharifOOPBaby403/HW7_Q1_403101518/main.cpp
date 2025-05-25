#include <bits/stdc++.h>
using namespace std;

// ------------- Exception example ------------------
class DoctorExistException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: doctor added twice";
    }
};

class WeekdayExistException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: invalid weekday";
    }
};

class NegativeMaxNPatientException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: number of patients can not be negative";
    }
};

// ------------- your code goes here ----------------
class Doctor;

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

class HospitalController {
public:
    static vector<string> validDays;
    static map<string, Doctor> doctors;
    static vector<string> doctorOrder;
    static map<string, Patient> patients;
};

vector<string> HospitalController::validDays;
map<string, Doctor> HospitalController::doctors;
vector<string> HospitalController::doctorOrder;
map<string, Patient> HospitalController::patients;

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
        setWorkingDays(_workingDays);
        setMaxNPatient(_maxNPatient);
    };

    void setWorkingDays(const vector<string> &days) {
        for (const string& x:days) {
            if (find(HospitalController::validDays.begin(),HospitalController::validDays.end(),x) == HospitalController::validDays.end())
                throw WeekdayExistException();
        }
        workingDays = vector<string>(days.begin(),days.end());
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

    int getMaxNPatient() const {
        return maxNPatient;
    }

    void setMaxNPatient(int maxNPatient) {
        if (maxNPatient < 0)
            throw NegativeMaxNPatientException();
        this->maxNPatient = maxNPatient;
    }
};

bool inputHandler(string line) {
    string word;
    vector<string> cp;
    stringstream ss(line);
    while (ss >> word) {
        cp.push_back(word);
    }

    // Add doctor
    if (cp[0] == "add" && cp[1] == "doctor" && cp.size() >= 6) {
        string name = cp[2];
        if (HospitalController::doctors.count(name))
            throw DoctorExistException();

        string specialty = cp[3];
        int maxNPatients = stoi(cp[4]);
        vector<string> workingDays;
        for (int i = 5;i < cp.size();i++) {
            workingDays.push_back(cp[i]);
        }
        Doctor newDoctor(name,specialty,maxNPatients,workingDays);
        HospitalController::doctors.emplace(name, newDoctor);
        HospitalController::doctorOrder.push_back(name);
        cout << "doctor " << name << " added with specialty " << specialty << " with " << maxNPatients << " patients" << endl;
    }

}

// ------ do not change main() function ------
int main() {
    string line;
    bool cond = true;
    while (cond) {
        getline(cin, line);
        try {
            cond = inputHandler(line);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}