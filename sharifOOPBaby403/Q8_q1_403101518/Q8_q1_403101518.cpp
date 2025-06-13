#include <bits/stdc++.h>
using namespace std;

class NumParametersException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid input format at line ";
    }
};

class TypeException : public exception {
public:
    const char* what() const noexcept override {
        return "Unknown service type at line ";
    }
};

class InvalidCustomerIDException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid consumption amount at line ";
    }
};

class WrongProirityException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid priority value at line ";
    }
};

class InvaldAmountException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid consumption amount at line ";
    }
};

class ServiceRequest {
protected:
    int customerID;
    int proirity;
    int amount;

public:
    ServiceRequest(int ci, int p, int a) : customerID(ci), proirity(p), amount(a) {}

    virtual int getFine() const = 0;
    virtual string getDescription() const = 0;
    virtual string getType() const = 0;

    int getAmount() const { return amount; }
    int getCustomerID() const { return customerID; }

    virtual void process(map<int, int> & customers) = 0;

    virtual ~ServiceRequest() {}
};

class WaterService : public ServiceRequest {
public:
    WaterService(int ci, int p, int a) : ServiceRequest(ci, p, a) {}

    int getFine() const override {
        int remaining = amount - 3000;
        return (remaining > 0) ? (remaining/500) * 100 : 0;
    }

    string getDescription() const override {
        string description;
        if (amount % 200 >= 50)
            description = to_string(amount/200 + 1) + " barrels ";
        else
            description = to_string(amount/200) + " barrels ";
        return description;
    }

    string getType() const override {
        return "WATER";
    }

    void process(map<int, int> & customers) override {
        cout << "Request for " << this->getType() << ": " << this->getDescription() << "(Customer " << this->getCustomerID() << ")";
        if (this->getFine() > 0) {
            cout << " | Fine: " << this->getFine();
            if (customers.find(this->getCustomerID()) != customers.end())
                customers.at(this->getCustomerID()) += this->getFine();
            else
                customers.insert({this->getCustomerID(), this->getFine()});
        }
        cout << endl;
    }
};

class ElectricityService : public ServiceRequest {
public:
    ElectricityService(int ci, int p, int a) : ServiceRequest(ci, p, a) {}

    int getFine() const override {
        int remaining = amount - 6000;
        return (remaining > 0) ? (remaining/1000) * 200 : 0;
    }

    string getDescription() const override {
        string description;
        if (amount % 30 >= 15)
            description = to_string(amount/30 + 1) + " kW/day ";
        else
            description = to_string(amount/30) + " kW/day ";
        return description;
    }

    string getType() const override {
        return "ELECTRICITY";
    }

    void process(map<int, int> & customers) override {
        cout << "Request for " << this->getType() << ": " << this->getDescription() << "(Customer " << this->getCustomerID() << ")";
        if (this->getFine() > 0) {
            cout << " | Fine: " << this->getFine();
            if (customers.find(this->getCustomerID()) != customers.end())
                customers.at(this->getCustomerID()) += this->getFine();
            else
                customers.insert({this->getCustomerID(), this->getFine()});
        }
        cout << endl;
    }
};

bool isPureNumber(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<string> cp;
    vector<string> commands;
    vector<ServiceRequest *> requests;
    map<int, int> customers; // ID, fine

    string word, commandLine;
    getline(cin, commandLine);
    stringstream ss(commandLine);

    int maxWaterCapacity, maxElectricityCapacity;
    ss >> maxWaterCapacity >> maxElectricityCapacity;


    while (true) {
        getline(cin, commandLine);
        if (commandLine == "END")
            break;
        commands.push_back(commandLine);
    }

    int i = 1;

    for (const auto & commad : commands) {
        stringstream ssd(commad);
        while (ssd >> word) {
            cp.push_back(word);
        }

        try {
            if (cp.size() != 4) {
                throw NumParametersException();
            }

            else if (cp[0] != "WATER" && cp[0] != "ELECTRICITY") {
                throw TypeException();
            }

            else if (!isPureNumber(cp[1]))
                throw InvalidCustomerIDException();
            else if (isPureNumber(cp[1]) && stoi(cp[1]) <= 0)
                throw InvalidCustomerIDException();

            else if (!isPureNumber(cp[2]))
                throw WrongProirityException();
            else if (stoi(cp[2]) < 1 || stoi(cp[2]) > 5)
                throw WrongProirityException();

            else if (!isPureNumber(cp[3]))
                throw InvaldAmountException();
            else if (stoi(cp[3]) < 0) {
                throw InvaldAmountException();
            }

            else {
                i++;
                string serviceType = cp[0];
                int customerID = stoi(cp[1]);
                int proirity = stoi(cp[2]);
                int amount = stoi(cp[3]);

                ServiceRequest *sq = nullptr;

                if (serviceType == "WATER")
                    sq = new WaterService(customerID, proirity, amount);
                else if (serviceType == "ELECTRICITY")
                    sq = new ElectricityService(customerID, proirity, amount);


                requests.push_back(sq);
                sq->process(customers);
                cp.clear();
            }
        }
        catch (const exception& e) {
            cout << e.what() << i++ << endl;
            cp.clear();
        }
    }

    int totalWaterUsed = 0, totalElectricityUsed = 0;
    for (auto request : requests) {
        if (request->getType() == "WATER") {
            totalWaterUsed += request->getAmount();
        }

        else if (request->getType() == "ELECTRICITY") {
            totalElectricityUsed += request->getAmount();
        }
    }

    cout << "Summary:" << endl;
    cout << "Total Water Used: " << totalWaterUsed << " / " << maxWaterCapacity << endl;
    cout << "Total Electricity Used: " << totalElectricityUsed << " / " << maxElectricityCapacity << endl;

    if (totalWaterUsed > maxWaterCapacity)
        cout << "Water Overload Detected – Consider Water Outage" << endl;
    else
        cout << "No Water overload." << endl;
    if (totalElectricityUsed > maxElectricityCapacity)
        cout << "Electricity Overload Detected – Consider Rolling Blackouts" << endl;
    else
        cout << "No Electricity overload." << endl;

    if (!customers.empty()) {
        cout << "Fined Customers:" << endl;
        for (const auto & customer : customers) {
            cout << "Customer " << customer.first << ": " << customer.second << endl;
        }
    }

    for (auto request : requests) {
        delete request;
    }

    return 0;
}
