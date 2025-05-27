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
    unordered_map<string, vector<string>> schedule; // 1. Day  2. Patient names

public:
    Doctor(cs _name, cs _specialty, int _maxNPatient, const vector<string> &_workingDays) :
    name(_name), specialty(_specialty), workingDays(_workingDays) {
        if (maxNPatient < 0) {
            throw NegativeMaxNPatientException();
        }

        for (const auto &day:workingDays) {
            if (!isValidDay(day)) {
                throw WeekdayExistException();
            }
        }
    };

    string getSpecialty() const {return specialty;}
    string getName() const {return name;}

    static bool isValidDay(cs day) {
        vector<string> validDays = {"saturday", "sunday", "monday", "tuesday", "wednesday"};
        return find(validDays.begin(), validDays.end(), day) != validDays.end();
    }

    void setMaxNPatient(int maxNPatient) {
        if (maxNPatient < 0)
            throw NegativeMaxNPatientException();

        for (auto &dayAppointment : schedule) {
            if (dayAppointment.second.size() > maxNPatient) {
                dayAppointment.second.resize(maxNPatient);
            }
        }

        this->maxNPatient = maxNPatient;
    }

    void setWorkingDays(const vector<string> &days) {
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
            schedule.erase(day);
        }

        workingDays = days;
    }

    bool hasCapacity(cs day) const {
        auto it = schedule.find(day);
        if (it == schedule.end() && (find(workingDays.begin(), workingDays.end(), day) != workingDays.end())) {
            return true;
        }
        else if (find(workingDays.begin(), workingDays.end(), day) == workingDays.end())
            return false;
        return it->second.size() < maxNPatient;
    }

    void addAppointment(cs patientName, cs day) {
        schedule[day].push_back(patientName);
    }

    void removeAppointment(cs patientName) {
        for (auto &pair : schedule) {
            auto it = find(pair.second.begin(), pair.second.end(), patientName);
            pair.second.erase(it);
            return;
        }
    }
};

class HospitalSystem {
private:
    // map<string, Doctor> doctors;
    vector<Doctor> doctorsOrder;
    map<string, pair<string, string>> patients; // name -> (doctor name, day)

public:
    // Add doctor
    void addDoctor(cs name, cs specialty, int maxNPatient, const vector<string> &workingDays) {
        if (doctors.find(name) != doctors.end())
            throw DoctorExistException(); 

        // doctors.emplace(name, Doctor(name, specialty, maxNPatient, workingDays));
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

        doctorsOrder[index].setMaxNPatient(maxP);
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

        doctorsOrder[index].setWorkingDays(newWorkingDays);
    }

    // Add patient
    string addPatient(const string& patientName, const string& specialty) {
        vector<Doctor*> matchingDoctors;
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
                    patients[patientName] = make_pair(doctor->getName(), day);
                    return day;
                }
            }
        }
        
        throw BusyDoctorsInDay();
    }

    // Delete patient
    string deletePatient(cs patientName) {
        auto it = patients.find(patientName);
        if (it == patients.end())
            throw PatientNameException();

        string docName = it->second.first;
        string day = it->second.second;

        int index = -1;
        for (int i = 0;i < doctorsOrder.size();i++) {
            if (doctorsOrder[i].getName() == docName) {
                index = i;
                break;
            }
        }

        doctorsOrder[index].removeAppointment();
        return day;
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
            for (const string & name:patientOrder) {
                if (patients.at(name).getDay() == day) {
                    cout << "patient" << ++i << " " << name << " : doctor " << patients.at(name).getDoctorName() << endl;
                }
            }
        }
    }

    // exit
    else if (cp[0] == "exit")
        return false;

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