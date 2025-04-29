#include <bits/stdc++.h>
using namespace std;

bool heater = false;
bool television = false;
bool air_conditioner = false;
bool refrigerator = false;

bool setupMode = true;

class Device {
private:
    string name;
    bool on;

public:
    Device(string Name) : name(Name), on(false) {}

    string getName() { return name; }
    bool isOn() { return on; }

    void button() {
        this->on = !this->on;
        cout << this->name << " turns " << (this->on ? "on":"off") << endl;
    }

    void wrongButton() {
        cout << this->name << " was " << (this->on ? "on":"off") << endl;
    }
};

class Client {
private:
    string IP;
    int spamCount;
    string spamOnWhatDevice;

public:
    vector<string> accessPointsName;

    Client(string ip) : IP(ip), spamCount(0) {}

    string getIP() { return IP; }
    int getSpams() { return spamCount; }
    void spam() { spamCount++; }
    void notSpamAnymore() {
        spamOnWhatDevice = "";
        spamCount = 0;
    }
    string getWhatDeviceIsSpammed() { return spamOnWhatDevice; }
    void tellMeWhatDeviceIsSpamming(string s) { spamOnWhatDevice = s; }
};

class AccessPoint {
private:
    string name;
    string password;
    unordered_map<string, Device> devices;
    vector<string> bannedIPs;
    int maxLimitation;
    int nOfConnecttions;
    vector<string> IPsPerTime;

public:
    unordered_map<string, Client> clients;

    AccessPoint(const string& Name, const string& Password, const vector<string>& deviceNames ) : name(Name),
    password(Password), maxLimitation(1000), nOfConnecttions(0) {
        string binaryCodeOfDevice;
        for (string device:deviceNames) {
            switch (device[0]) {
                case 'h':
                    binaryCodeOfDevice = "00";
                    heater = true;
                    break;
                case 't':
                    binaryCodeOfDevice = "01";
                    television = true;
                    break;
                case 'a':
                    binaryCodeOfDevice = "10";
                    air_conditioner = true;
                    break;
                case 'r':
                    binaryCodeOfDevice = "11";
                    refrigerator = true;
                    break;
            }
            devices.emplace(binaryCodeOfDevice,Device(device));
        }
    }

    string getName() { return name; }
    string getPass() { return password; }
    int getMaxLimit() { return maxLimitation; }
    int nConnect() { return nOfConnecttions; }
    void setMaxLimit(int newMaxLimit) { maxLimitation = newMaxLimit; }

    void connectClient(const string& ip) {
        if (nOfConnecttions >= maxLimitation || searchBannedIPs(ip)) {
            cout << "can not connect because of limitations" << endl;
            return;
        }
        Client cl(ip);
        clients.emplace(ip,cl);
        cl.accessPointsName.push_back(name);
        IPsPerTime.push_back(ip);
        nOfConnecttions++;
        cout << "client connected successfully" << endl;
    }

    void getClients() {
        int counter = 1;
        if (clients.empty()) {
            cout << "no client connected yet" << endl;
            return;
        }
        for (int i = 0;i < IPsPerTime.size();i++) {
            cout << "client" << to_string(counter) << " " << IPsPerTime[i] << endl;
            counter++;
        }
    }

    void makeBannedIP(const string& ip) {
        bannedIPs.push_back(ip);
    }

    bool findIP(const string& ip, Client *cl) {
        if (clients.find(ip) != clients.end()) {
            cl = &clients.at(ip);
            return true;
        }
        return false;
    }

    void deleteClient(const string& ip) {
        clients.erase(ip);
        IPsPerTime.erase(find(IPsPerTime.begin(),IPsPerTime.end(),ip));
        nOfConnecttions--;
    }

    void processDeviceCommand(Client& cl, const string& binaryCode) {
        string deviceCode = binaryCode.substr(0, 2);
        string action = binaryCode.substr(2);

        if (devices.find(deviceCode) == devices.end()) {
            cout << "no such device found" << endl;
            return;
        }
        Device *device = &devices.at(deviceCode);
        if (action == "1") {
            if (device->isOn())
                device->wrongButton();
            else
                device->button();
        }
        else if (action == "0") {
            if (!device->isOn())
                device->wrongButton();
            else
                device->button();
        }
        if (cl.getWhatDeviceIsSpammed().empty()) {
            cl.tellMeWhatDeviceIsSpamming(deviceCode);
            if (cl.getSpams() == 0)
                cl.spam();
        }
        else if (cl.getWhatDeviceIsSpammed() != deviceCode) {
            cl.notSpamAnymore();
            cl.spam();
            cl.tellMeWhatDeviceIsSpamming(deviceCode);
        }
        else if (cl.getWhatDeviceIsSpammed() == deviceCode) {
            cl.spam();
        }
    }

    bool searchBannedIPs(const string& ip) {
        if(find(bannedIPs.begin(),bannedIPs.end(),ip) != bannedIPs.end())
            return true;
        return false;
    }
};

class ESP32Controller {
private:
    unordered_map<string, AccessPoint> accessPoints;

public:
    void makeAccessPoint(const string& name, const string& pass, const vector<string>& devices) {
        if (accessPoints.find(name) != accessPoints.end()) {
            cout << "this name already used" << endl;
            return;
        }
        if (pass.size() < 8 && !pass.empty()) {
            cout << "invalid password" << endl;
            return;
        }

        accessPoints.emplace(name, AccessPoint(name,pass,devices));
        cout << "access point created successfully" << endl;
    }

    void setMaxLimitation(const string& name, int n) {
        if (accessPoints.find(name) == accessPoints.end()) {
            cout << "invalid access point name" << endl;
            return;
        }
        if (n < 0) {
            cout << "number of clients can not be negative" << endl;
            return;
        }

        AccessPoint *accessPoint = &accessPoints.at(name);
        accessPoint->setMaxLimit(n);
        cout << "limitation set" << endl;
    }

    void setBannedIP(const string& name,const string& ip) {
        if (wrongAccessPointName(name)) {
            cout << "invalid access point name" << endl;
            return;
        }

        AccessPoint *acp = &accessPoints.at(name);
        acp->makeBannedIP(ip);
        cout << "limitation set" << endl;
    }

    bool wrongIP(const string& ip) {
        string ip1 = ip.substr(0,10);
        string ip2 = ip.substr(10);
        int number = 0;
        for (auto num:ip2) {
            number += (num - '0');
            number *= 10;
        }
        number /= 10;
        if (ip1 == "192.168.1." && number <= 255 && number >= 0)
            return false;
        return true;
    }

    bool wrongAccessPointName(const string& accessPointName) {
        if (accessPoints.find(accessPointName) != accessPoints.end())
            return false;
        return true;
    }

    bool wrongPassword(const string& password, const string& accessPointName) {
        bool ok = true;
        if (accessPoints.at(accessPointName).getPass().empty())
            ok = false;
        else if (accessPoints.at(accessPointName).getPass() == password)
            ok = false;
        return ok;
    }

    void processCommand(const vector<string>& cp) {  // cp -> command parts
        if (cp[0] == "create" && cp[1] == "Access" && cp[2] == "point") {
            if (!setupMode) {
                cout << "invalid command" << endl;
                return;
            }
            vector<string> d;
            string name = cp[3];
            string pass;
            if (cp[4] == "heater" || cp[4] == "television" || cp[4] == "air_conditioner" || cp[4] == "refrigerator") {
                pass = "";
                for (int i = 4; i < cp.size();i++) {
                    d.push_back(cp[i]);
                }
            }
            else {
                pass = cp[4];
                for (int i = 5; i < cp.size();i++) {
                    d.push_back(cp[i]);
                }
            }

            makeAccessPoint(name,pass,d);
        }

        else if (cp[0] == "access" && cp[1] == "point" && cp[3] == "max" && cp[4] == "client") {
            if (!setupMode) {
                cout << "invalid command" << endl;
                return;
            }
            string acpName = cp[2];
            int nClients = stoi(cp[5]);
            setMaxLimitation(acpName,nClients);
        }

        else if (cp[0] == "limit" && cp[1] == "client" && cp[3] == "from" && cp[4] == "access") {
            if (!setupMode) {
                cout << "invalid command" << endl;
                return;
            }
            string clientIp = cp[2];
            string acpName = cp[6];
            setBannedIP(acpName,clientIp);
        }

        else if (television && air_conditioner && heater && refrigerator) {
            setupMode = false;

            if (cp[0] == "connect" && cp[1] == "client") {
                const string& ip = cp[2];
                const string& accessPointName = cp[3];
                string password;
                if (cp.size() == 4)
                    password = "";
                else
                    password = cp[4];
                if (wrongIP(ip))
                    cout << "invalid IP" << endl;
                else if (wrongAccessPointName(accessPointName))
                    cout << "invalid access point name" << endl;
                else if (wrongPassword(password,accessPointName))
                    cout << "wrong password" << endl;
                else
                    accessPoints.at(accessPointName).connectClient(ip);
            }

            else if (cp[0] == "access" && cp[1] == "point" && cp[3] == "clients" && cp[4] == "list") {
                const string& accessPonitName = cp[2];
                if (wrongAccessPointName(accessPonitName))
                    cout << "invalid access point name" << endl;
                else {
                    AccessPoint *accPoi = &accessPoints.at(accessPonitName);
                    accPoi->getClients();
                }
            }

            else if (cp[0] == "delete" && cp[1] == "client" && cp[3] == "from" && cp[4] == "access" && cp[5] == "point") {
                const string& ip = cp[2];
                const string& accessPointName = cp[6];
                Client* clientFounded;
                if (wrongAccessPointName(accessPointName))
                    cout << "invalid access point name" << endl;
                else {
                    AccessPoint *accessPoint = &accessPoints.at(accessPointName);
                    if (!accessPoint->findIP(ip,clientFounded))
                        cout << "this IP does not exist in the access point " << accessPointName << endl;
                    else {
                        accessPoint->deleteClient(ip);
                        cout << "client deleted" << endl;
                    }
                }
            }

            else if (cp[0] == "disconnect" && cp[1] == "client" && cp[3] == "from" && cp[4] == "access" && cp[5] == "point") {
                const string& ip = cp[2];
                const string& accessPointName = cp[6];
                Client* clientFounded;
                if (wrongAccessPointName(accessPointName))
                    cout << "this access point does not exist" << endl;
                else {
                    AccessPoint *accessPoint = &accessPoints.at(accessPointName);
                    if (!accessPoint->findIP(ip,clientFounded))
                        cout << "no such client exist in this access point" << endl;
                    else {
                        accessPoint->deleteClient(ip);
                        cout << "client disconnected" << endl;
                    }
                }
            }

            else if (cp[0] == "read" && cp[1] == "from" && cp[2] == "client") {
                const string& ip = cp[3];
                string binaryCode;
                cin >> binaryCode;

                bool flag = false;

                for (auto &acp:accessPoints) {
                    AccessPoint &hmmmmm = acp.second;
                    if (hmmmmm.clients.find(ip) != hmmmmm.clients.end()) {
                        flag = true;
                        Client& cl = hmmmmm.clients.at(ip);
                        if (cl.getSpams() >= 4) {
                            cout << "client " << ip << " banned due to spam" << endl;
                            hmmmmm.makeBannedIP(ip);
                            hmmmmm.deleteClient(ip);
                            cin.ignore();
                            return;
                        }
                        hmmmmm.processDeviceCommand(cl,binaryCode);
                        cin.ignore();
                        return;
                    }

                    if (hmmmmm.searchBannedIPs(ip))
                        flag = false;
                }

                if (!flag)
                    cout << "invalid IP" << endl;

                cin.ignore();
            }

            else
                cout << "invalid command" << endl;
        }

        else {
            cout << "invalid command" << endl;
            setupMode = true;
        }
    }
};

int main() {
    ESP32Controller esp32;

    string command,word;
    vector<string> cp;

    while (getline(cin,command)) {
        stringstream ss(command);
        while (ss >> word) {
            if (word == "exit")
                return 0;
            cp.push_back(word);
        }
        esp32.processCommand(cp);
        cp.clear();
    }
    return 0;
}