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

    double getVoltage() const {return voltage;}
};

int Node::counter = 0;

class Component{
protected:
    string name;
    Node Node1;
    Node Node2;

public:
    Component(cs name, Node node1, Node node2) : name(name), Node1(node1), Node2(node2) {}

    virtual double getVoltage() const = 0;

    virtual double getCurrent() const = 0;
};

class Resistor:public Component{
private:
    double value;
public:
    Resistor(cs name, Node Node1, Node Node2,double value) : Component(name, Node1, Node2), value(value) {}

    double getVoltage() const {}

    double getCurrent() const {}
};

class VoltageSource:public Component{
private:
    double voltage;
public:
    VoltageSource(Node node1, Node node2 , double voltage) : Component("V1", node1, node2), voltage(voltage) {}

    double getVoltage() const {return voltage;}

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
        nodes.emplace(name,newNode);
    }

    // Add resistor
    void addResistor(double resVal, cs resName, cs node1Name, cs node2Name) {
        Component* newResistor = new Resistor(resName, nodes.at(node1Name), nodes.at(node2Name),resVal);
        components.emplace_back(newResistor);
    }

    // Add voltage source
    void addVoltageSource(double voltage, cs node1, cs node2) {
        Component* newVoltageSource = new VoltageSource(nodes.at(node1),nodes.at(node2),voltage);
        components.emplace_back(newVoltageSource);
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
        regex addVoltageSourcePattern(R"(add voltage source (\S+)\s*)");

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
                double resVal = stod(matches[1]);
                string resName = matches[2];
                string node1Name = matches[3];
                string node2Name = matches[4];
                spice.addResistor(resVal, resName, node1Name, node2Name);
            }

            // Add voltage source
            else if (regex_match(cmd, matches, addVoltageSourcePattern)) {
                double voltageSource = stod(matches[1]);
                string node1Name = matches[2];
                string node2Name = matches[3];
                spice.
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
