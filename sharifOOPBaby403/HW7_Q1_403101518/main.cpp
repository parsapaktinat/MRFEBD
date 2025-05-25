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

class DoctorsSpecialtyExist : public exception {
public:
    const char* what() const noexcept override {
        return "Error: no doctor for this problem exist";
    }
};

// ------------- your code goes here ----------------
class Doctor;
class Patient;

vector<string> validDays;
map<string, Doctor> doctors;
vector<string> doctorOrder;
map<string, Patient> patients;

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
    unordered_map<string, vector<string>> schedule; // 1. Day - 2. Patient names

public:
    Doctor(string _name, string _specialty, int _maxNPatient, const vector<string> &_workingDays) :
    name(_name), specialty(_specialty) {
        setWorkingDays(_workingDays);
        setMaxNPatient(_maxNPatient);
    };

    void setWorkingDays(const vector<string> &days) {
        for (const string& x:days) {
            if (find(validDays.begin(),validDays.end(),x) == validDays.end())
                throw WeekdayExistException();
        }
        workingDays = vector<string>(days.begin(),days.end());
        for (auto &[day, patients]:schedule) {
            if (find(workingDays.begin(), workingDays.end(), day) == workingDays.end())
                schedule.erase(day);
        }
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

        for (auto &[day,patients]:schedule) {
            if (patients.size() > maxNPatient)
                patients.resize(maxNPatient);
        }
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
        string specialty = cp[3];
        int maxNPatients = stoi(cp[4]);
        vector<string> workingDays;
        for (int i = 5;i < cp.size();i++) {
            workingDays.push_back(cp[i]);
        }

        if (doctors.count(name))
            throw DoctorExistException();

        Doctor newDoctor(name,specialty,maxNPatients,workingDays);
        doctors.emplace(name, newDoctor);
        doctorOrder.push_back(name);

        cout << "doctor " << name << " added with specialty " << specialty << " with " << maxNPatients << " patients" << endl;
    }

    // Change the number of patients of the doctor
    else if (cp[0] == "change" && cp[1] == "the" && cp[2] == "number" && cp.size() == 10) {
        string name = cp[7];
        int numberOfPatients = stoi(cp[9]);

        if (doctors.count(name))
            throw DoctorExistException();

        doctors.at(name).setMaxNPatient(numberOfPatients);

        cout << "number of patients changed" << endl;
    }

    // Change the working days
    else if (cp[0] == "change" && cp[1] == "the" && cp[2] == "working" && cp.size() == 9) {
        string name = cp[6];
        vector<string> workingDays;
        for (int i = 7;i < cp.size();i++) {
            workingDays.push_back(cp[i]);
        }

        if (doctors.count(name) == 0)
            throw DoctorExistException();

        doctors.at(name).setWorkingDays(workingDays);

        cout << "working days changed" << endl;
    }

    // Add patients
    else if (cp[0] == "add" && cp[1] == "patient" && cp.size() == 4) {
        string name = cp[2];
        string specialty = cp[3];

        bool found = false;
        string doctorName;
        for (auto &doctor:doctors) {
            if (doctor.second.getSpecialty() == specialty) {
                doctorName = doctor.first;
                found = true;
            }
        }

        if ()
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