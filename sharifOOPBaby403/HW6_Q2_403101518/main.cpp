#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Node{
private:
    int Number;
    double voltage;
    static int counter;

public:
    Node() {
        Number = ++counter;
        voltage = 0;
    }

    double getVoltage() const {

    }
};

int Node::counter = 0;

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
class Circuit{
private:
    vector<Component *> components;
    unordered_map<string, Node> nodes;

public:
    // Add node
    void addNode(cs name) {
        Node newNode;
        nodes.emplace(newNode);
    }

    // Add resistor
    void addResistor(cs resVal, cs resName, cs node1Name, cs node2Name) {
        
    }

    // Destructor
    ~Circuit() {
        for (auto component:components) {
            delete component;
        }
    }
};

// View
class View{
private:
    Circuit spice;
public:
    void run() {
        regex addNodePattern(R"(add node (\S+)\s*)");
        regex addResistorPattern(R"(add resistor (\S+)\s*)");

        smatch matches;
        string cmd;

        while (true) {
            getline(cin, cmd);

            // Add node
            if (regex_match(cmd, matches, addNodePattern)) {
                string nodeName = matches[1];
                spice.addNode(nodeName);
            }

            // Add resistor
            else if (regex_match(cmd, matches, addResistorPattern)) {
                string resVal = matches[1];
                string resName = matches[2];
                string node1Name = matches[3];
                string node2Name = matches[4];

            }


            // End
            else if (cmd == "end")
                return;
        } 
    }
};

int main() {
    
    return 0;
}
