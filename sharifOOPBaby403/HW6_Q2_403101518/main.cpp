#include <bits/stdc++.h>
using namespace std;

#define cs const string &

// Model
class Node{
private:
    int Number;
    double voltage;
    static int counter;
    bool isGround;

public:
    Node() {
        Number = ++counter;
        isGround = false;
        voltage = 0;
    }

    double getVoltage() const {return voltage;}
    int getNumber() const {return Number;}
    void setNumberNode(int n) {Number = n;}
    bool getGround() const {return isGround;}
    void setGround() {
        isGround = true;
    }
};

int Node::counter = 0;

class Component{
protected:
    string name;
    Node Node1;
    Node Node2;

public:
    Component(cs name, Node* node1, Node* node2) : name(name), Node1(node1), Node2(node2) {}

    Node getNode(int n) const {
        Node result;
        if (n == 1)
            result = Node1;
        else if (n == 2)
            result = Node2;
        return result;
    }

    virtual double getVoltage() const = 0;
    virtual double getCurrent() const = 0;
};

class Resistor:public Component{
private:
    double value;
public:
    Resistor(cs name, Node* Node1, Node Node2*,double value) : Component(name, Node1, Node2), value(value) {}

    double getVoltage() const {}
    double getCurrent() const {}
};

class VoltageSource:public Component{
private:
    double voltage;
public:
    VoltageSource(Node* node1, Node* node2 , double voltage) : Component("VIN", node1, node2), voltage(voltage) {}

    double getVoltage() const {return voltage;}
    double getCurrent() const {}
};

// Control
class Circuit{
private:
    unordered_map<int, Component*> components;
    vector<Component*> resistors;
    vector<Component*> voltageSources;
    unordered_map<string, Node*> nodes;
    unordered_map<string, int> nodeIndexes;

public:
    // Add node
    void addNode(cs name) {
        Node* newNode = new Node();
        nodes.emplace(name,newNode);
        nodeIndexes.emplace(name,newNode->getNumber());
    }

    // Add resistor
    void addResistor(double resVal, cs resName, cs node1Name, cs node2Name) {
        Component* newResistor = new Resistor(resName, nodes.at(node1Name), nodes.at(node2Name),resVal);
        components.emplace(1,newResistor);
        resistors.emplace_back(newResistor);
    }

    // Add voltage source
    void addVoltageSource(double voltage, cs node1, cs node2) {
        Component* newVoltageSource = new VoltageSource(nodes.at(node1),nodes.at(node2),voltage);
        components.emplace(2,newVoltageSource);
        voltageSources.emplace_back(newVoltageSource);
    }

    // Add ground
    void addGround(cs nodeName) {
        int counter = 0;
        nodes.at(nodeName)->setGround();
        for (auto &node:nodes) {
            if (!node.second->getGround()) {
                node.second->setNumberNode(counter++);
            }
        }
    }

    // Analyse circuit
    vector<double> currentVoltages() const {
        int n = nodes.size() - 1;
        int m = 1;
        vector<vector<double>> A(n+m,vector<double>(n+m,0.0));
        for (auto component:components) {
            if (component.first == 1) {
                Node tempNode1 = component.second->getNode(1);
                Node tempNode2 = component.second->getNode(2);

            }
        }
    }

    // Destructor
    ~Circuit() {
        for (auto component:components)
            delete component.second;
        for (auto res:resistors)
            delete res;
        for (auto vol:voltageSources)
            delete vol;
        for (auto node:nodes) {
            delete node.second;
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
        regex addGroundPattern(R"(add ground (\S+)\s*)");

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
                spice.addVoltageSource(voltageSource,node1Name,node2Name);
            }

            // Add ground
            else if (regex_match(cmd, matches, addGroundPattern)) {
                string node = matches[1];
                spice.addGround(node);
            }

            //


            // End
            else if (cmd == "end")
                return;
        } 
    }
};

int main() {
    
    return 0;
}
