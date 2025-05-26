#include <bits/stdc++.h>
using namespace std;

// ------------- Exception example ------------------
class DoctorExistException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: doctor added twice";
    }
};

class DoctorDontExistException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: no doctor with this name exist";
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

class BusyDoctorsInDay : public exception {
public:
    const char* what() const noexcept override {
        return "Error: doctors with this specialty are busy";
    }
};

class PatientNameException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: no patient with this name exist";
    }
};

// ------------- your code goes here ----------------
class Doctor;
class Patient;
string findDoctorWithSpecialty(const string &specialty, bool &found);

vector<string> validDays = {"saturday", "sunday", "monday", "tuesday", "wednesday"};
map<string, Doctor> doctors;
vector<string> doctorOrder;
map<string, Patient> patients;
vector<string> patientOrder;

class Patient{
private:
    string name;
    string doctorName;
    string day;

public:
    Patient(const string &_name, const string & _doctorName, const string & _day) : name(_name), doctorName(_doctorName)
    , day(_day) {}

    string getDay() const {
        return day;
    }

    string getDoctorName() const {
        return doctorName;
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

        vector<string> oldDays;
        for (const string &day:workingDays) {
            if (find(days.begin(), days.end(), day) == days.end()) {
                oldDays.push_back(day);
            }
        }

        for (const string &day:oldDays) {
            for (const string &patName:schedule.at(day)) {
                patients.erase(patName);
                patientOrder.erase(remove(patientOrder.begin(), patientOrder.end(), patName), patientOrder.end());
            }
            schedule.erase(day);
        }

        workingDays = vector<string>(days.begin(),days.end());
    }

    string getSpecialty() const {
        return specialty;
    }

    void deletePatient(const string &patName, string &weekday) {
        for (auto &[day, p] : schedule) {
            if (find(p.begin(),p.end(),patName) != p.end()) {
                weekday = day;
                p.erase(remove(p.begin(), p.end(), patName), p.end());
                patients.erase(patName);
                patientOrder.erase(remove(patientOrder.begin(), patientOrder.end(), patName), patientOrder.end());
                return;
            }
        }
    }

    bool hasCapacity(string &weekday, const string &name) {
        for (auto &day:workingDays) {
            if (schedule[day].size() < maxNPatient) {
                schedule[day].push_back(name);
                weekday = day;
                return true;
            }
        }
        return false;
    }

    void setMaxNPatient(int maxNPatient) {
        if (maxNPatient < 0)
            throw NegativeMaxNPatientException();

        
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

        if (doctors.count(name) == 1)
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

        if (doctors.count(name) == 0)
            throw DoctorDontExistException();

        doctors.at(name).setMaxNPatient(numberOfPatients);

        cout << "number of patients changed" << endl;
    }

    // Change the working days
    else if (cp[0] == "change" && cp[1] == "the" && cp[2] == "working") {
        string name = cp[6];
        vector<string> workingDays;
        for (int i = 8 ;i < cp.size();i++) {
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
        string doctorName = findDoctorWithSpecialty(specialty, found);

        if (!found)
            throw DoctorsSpecialtyExist();

        string weekday;
        if (doctors.at(doctorName).hasCapacity(weekday,name)) {
            Patient newPatient(name,doctorName,weekday);
            patients.emplace(name,newPatient);
            patientOrder.push_back(name);
            cout << "appointment set on day " << weekday << " doctor " << doctorName << endl;
        }
        else
            throw BusyDoctorsInDay();
    }

    // Delete patient
    else if (cp[0] == "delete" && cp[1] == "patient" && cp.size() == 3) {
        string name = cp[2];

        if (patients.count(name) == 0)
            throw PatientNameException();

        string weekday, docName = patients.at(name).getDoctorName();
        doctors.at(docName).deletePatient(name,weekday);
        cout << "appointment deleted on day " << weekday << " doctor " << name << endl;
    }

    // Patients list
    else if (cp[0] == "patients" && cp[1] == "list") {
        for (auto day : {"saturday", "sunday", "monday", "tuesday", "wednesday"}) {
            cout << day << ":\n";
            int i = 0;
//            for () {

//            }
        }
    }

    // exit
    else if (cp[0] == "exit")
        return false;

    return true;
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

string findDoctorWithSpecialty(const string &specialty, bool &found) {
    string name1, name2;
    for (auto &[name,doctor]:doctors) {
        if (doctor.getSpecialty() == specialty) {
            if (!found) {
                name1 = name;
                found = true;
            }
            else {
                name2 = name;
                auto it1 = find(doctorOrder.begin(), doctorOrder.end(), name1);
                auto it2 = find(doctorOrder.begin(), doctorOrder.end(), name2);
                if (it2 < it1)
                    name1 = name2;
            }
        }
    }
    return name1;
}