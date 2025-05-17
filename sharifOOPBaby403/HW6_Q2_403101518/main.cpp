#include <bits/stdc++.h>
using namespace std;

// Model
class Node{
private:
    int Number;

public:
    double getVoltage() const {

    }
};

class Component{
protected:
    string name;
    Node Node1;
    Node Node2;

public:
    virtual double getVoltage() const = 0;

    virtual double getCurrent() const = 0;
};

class Resistor:public Component{
public:
    double getVoltage() const {

    }

    double getCurrent() const {

    }
};

class VoltageSource:public Component{
public:
    double getVoltage() const {

    }

    double getCurrent() const {

    }
};

// Control
class ProcessCommand{
private:
    vector<Component *> components;

public:
    
};

// View
class View{
public:
    void run() {
        regex addNodePattern(R"(add\s+node (\S+)\s*)");

        smatch matches;
        string cmd;

        while (true) {
            getline(cin, cmd);

            if(regex_match(cmd,matches,addNodePattern)){
                string nodeName=matches[1];

            }


        } 
    }
};

int main()
{
    
    return 0;
}
