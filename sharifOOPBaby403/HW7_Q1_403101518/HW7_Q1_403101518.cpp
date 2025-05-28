#include <bits/stdc++.h>
using namespace std;

#define cs const string &

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

class InvalidCommandException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: invalid command";
    }
};

// ------------- your code goes here ----------------
class Doctor {
private:
    string name;
    string specialty;
    int maxNPatient;
    vector<string> workingDays;
    unordered_map<string, vector<string>> schedule; // 1. Day  2. Patient names

public:
    Doctor(cs _name, cs _specialty, int _maxNPatient, const vector<string> &_workingDays) :
    name(_name), specialty(_specialty) {
        if (_maxNPatient < 0) {
            throw NegativeMaxNPatientException();
        }

        for (const auto &day:_workingDays) {
            if (!isValidDay(day)) {
                throw WeekdayExistException();
            }
        }

        maxNPatient = _maxNPatient;
        workingDays = _workingDays;
        for (auto &day:workingDays) {
            if (schedule.count(day) == 0) {
                schedule.insert({day, {}});
            }
        }
    };

    string getSpecialty() const {return specialty;}
    string getName() const {return name;}

    static bool isValidDay(cs day) {
        vector<string> validDays = {"saturday", "sunday", "monday", "tuesday", "wednesday"};
        return find(validDays.begin(), validDays.end(), day) != validDays.end();
    }

    void setMaxNPatient(int _maxNPatient, vector<string> & deletedPatients) {
        if (_maxNPatient < 0)
            throw NegativeMaxNPatientException();

        for (auto &dayAppointment : schedule) {
            if (dayAppointment.second.size() > _maxNPatient) {
                for (int i = _maxNPatient;i < dayAppointment.second.size();i++) {
                    deletedPatients.push_back(dayAppointment.second[i]);
                }
                dayAppointment.second.resize(_maxNPatient);
            }
        }

        maxNPatient = _maxNPatient;
    }

    void setWorkingDays(const vector<string> &days, vector<string> & deletedPatients) {
        for (cs day : days) {
            if (!isValidDay(day)) {
                throw WeekdayExistException();
            }
        }

        vector<string> oldDays;
        for (const string &day:workingDays) {
            if (find(days.begin(), days.end(), day) == days.end()) {
                oldDays.push_back(day);
            }
        }

        for (const string &day:oldDays) {
            for (string & name : schedule[day])
                deletedPatients.push_back(name);
            schedule.erase(day);
        }

        workingDays = days;

        for (auto &day:workingDays) {
            if (schedule.count(day) == 0) {
                schedule.insert({day, {}});
            }
        }
    }

    bool hasCapacity(cs day) const {
        if (find(workingDays.begin(), workingDays.end(), day) != workingDays.end()) {
            if (schedule.find(day) != schedule.end()) {
                return schedule.at(day).size() < maxNPatient;
            }
        }
        return false;
    }

    void addAppointment(cs patientName, cs day) {
        schedule[day].push_back(patientName);
    }

    void removeAppointment(cs patientName) {
        for (auto &pair : schedule) {
            auto it = find(pair.second.begin(), pair.second.end(), patientName);
            pair.second.erase(it);
        }
    }
};

class Patient{
private:
    string name;
    string docName;
    string day;

public:
    Patient(cs _name, cs _doctorName, cs _day) : name(_name), docName(_doctorName), day(_day) {}

    string getDay() const {return day;}
    string getDoctorName() const {return docName;}
    string getName() const {return name;}
};

class HospitalSystem {
private:
    vector<Doctor> doctorsOrder;
    vector<Patient> patientsOrder;

public:
    // Add doctor
    void addDoctor(cs name, cs specialty, int maxNPatient, const vector<string> &workingDays) {
        int index = -1;
        for (int i = 0;i < doctorsOrder.size();i++) {
            if (doctorsOrder[i].getName() == name) {
                index = i;
                break;
            }
        }

        if (index >= 0)
            throw DoctorExistException();

        doctorsOrder.push_back(Doctor(name, specialty, maxNPatient, workingDays));
    }

    // Change max number of patients
    void changeDoctorMaxPatient(cs name, int maxP) {
        int index = -1;
        for (int i = 0;i < doctorsOrder.size();i++) {
            if (doctorsOrder[i].getName() == name) {
                index = i;
                break;
            }
        }

        if (index < 0)
            throw DoctorDontExistException();

        vector<string> deletedPatients;
        doctorsOrder[index].setMaxNPatient(maxP, deletedPatients);

        for (auto it = patientsOrder.begin(); it != patientsOrder.end();) {
            if (find(deletedPatients.begin(), deletedPatients.end(), it->getName()) != deletedPatients.end()) {
                it = patientsOrder.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // change working days
    void changeWorkingDays(cs name, const vector<string> & newWorkingDays) {
        int index = -1;
        for (int i = 0;i < doctorsOrder.size();i++) {
            if (doctorsOrder[i].getName() == name) {
                index = i;
                break;
            }
        }

        if (index < 0)
            throw DoctorDontExistException();

        vector<string> deletedPatients;
        doctorsOrder[index].setWorkingDays(newWorkingDays,deletedPatients);

        for (auto it = patientsOrder.begin(); it != patientsOrder.end();) {
            if (find(deletedPatients.begin(), deletedPatients.end(), it->getName()) != deletedPatients.end()) {
                it = patientsOrder.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Add patient
    string addPatient(cs patientName, cs specialty, string& docName) {
        vector<Doctor *> matchingDoctors;
        for (auto& doctor : doctorsOrder) {
            if (doctor.getSpecialty() == specialty) {
                matchingDoctors.push_back(&doctor);
            }
        }

        if (matchingDoctors.empty()) {
            throw DoctorsSpecialtyExist();
        }

        vector<string> daysOrder = {"saturday", "sunday", "monday", "tuesday", "wednesday"};

        for (auto day : daysOrder) {
            for (auto doctor : matchingDoctors) {
                if (doctor->hasCapacity(day)) {
                    doctor->addAppointment(patientName, day);
                    docName = doctor->getName();
                    Patient newPatient(patientName, docName,day);
                    patientsOrder.emplace_back(newPatient);
                    return day;
                }
            }
        }

        throw BusyDoctorsInDay();
    }

    // Delete patient
    string deletePatient(cs patientName, string &docName) {
        int index = -1;
        for (int i = 0;i < patientsOrder.size();i++) {
            if (patientsOrder[i].getName() == patientName) {
                index = i;
                break;
            }
        }

        if (index < 0)
            throw PatientNameException();

        docName = patientsOrder[index].getDoctorName();
        string day = patientsOrder[index].getDay();

        int ind = -1;
        for (int i = 0;i < doctorsOrder.size();i++) {
            if (doctorsOrder[i].getName() == docName) {
                ind = i;
                break;
            }
        }

        doctorsOrder[index].removeAppointment(patientName);
    
        for (auto it = patientsOrder.begin(); it != patientsOrder.end();it++) {
            if (it->getName() == patientName) {
                patientsOrder.erase(it);
                break;
            }
        }
        
        return day;
    }

    // Get patient list
    void getPatinetListOnDay(vector<string> & patName, vector<string> & docName, cs day) {
        for (auto & patient : patientsOrder) {
            if (patient.getDay() == day) {
                patName.push_back(patient.getName());
                docName.push_back(patient.getDoctorName());
            }
        }
    }
};

HospitalSystem hs;

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

        hs.addDoctor(name, specialty, maxNPatients, workingDays);

        cout << "doctor " << name << " added with specialty " << specialty << " with " << maxNPatients << " patients" << endl;
    }

    // Change the number of patients of the doctor
    else if (cp[0] == "change" && cp[1] == "the" && cp[2] == "number") {
        string name = cp[7];
        int numberOfPatients = stoi(cp[9]);

        hs.changeDoctorMaxPatient(name, numberOfPatients);

        cout << "number of patients changed" << endl;
    }

    // Change the working days
    else if (cp[0] == "change" && cp[1] == "the" && cp[2] == "working") {
        string name = cp[6];
        vector<string> workingDays;
        for (int i = 8 ;i < cp.size();i++) {
            workingDays.push_back(cp[i]);
        }

        hs.changeWorkingDays(name, workingDays);

        cout << "working days changed" << endl;
    }

    // Add patients
    else if (cp[0] == "add" && cp[1] == "patient" && cp.size() == 4) {
        string name = cp[2];
        string specialty = cp[3];

        string docName;
        string day = hs.addPatient(name, specialty, docName);

        cout << "appointment set on day " << day << " doctor " << docName << endl;
    }

    // Delete patient
    else if (cp[0] == "delete" && cp[1] == "patient" && cp.size() == 3) {
        string name = cp[2];

        string docName;
        string day = hs.deletePatient(name, docName);

        cout << "appointment deleted on day " << day << " doctor " << docName << endl;
    }

    // Patients list
    else if (cp[0] == "patients" && cp[1] == "list") {
        vector<string> patName,docName;
        for (string day : {"saturday","sunday","monday","tuesday","wednesday"}) {
            cout << day << ":\n";
            hs.getPatinetListOnDay(patName, docName, day);
            if (patName.empty()) {
                patName.clear();
                docName.clear();
                continue;
            }
            else {
                for (int i = 0;i < patName.size();i++)
                    cout << "patient" << i+1 << " " << patName[i] << " : doctor " << docName[i] << endl;

                patName.clear();
                docName.clear();
            }
        }
    }

    // exit
    else if (cp[0] == "exit")
        return false;

    // Invalid command
    else
        throw InvalidCommandException();

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