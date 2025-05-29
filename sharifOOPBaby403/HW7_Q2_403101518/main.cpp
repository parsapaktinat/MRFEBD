#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class ErrorHappend : public exception {
public:
    const char* what() const noexcept override {
        return "INVALID COMMAND";
    }
};

// Helper function to see is the ID is number or not
bool isRealNumber(cs str) {
    if (str.empty()) {
        return false;
    }

    size_t i = 0;
    while (i < str.size() && isspace(str[i])) {
        ++i;
    }

    if (i < str.size() && (str[i] == '+' || str[i] == '-')) {
        ++i;
    }

    bool hasDigit = false;
    bool hasDecimal = false;

    while (i < str.size() && isdigit(str[i])) {
        hasDigit = true;
        ++i;
    }

    if (i < str.size() && str[i] == '.') {
        hasDecimal = true;
        ++i;
    }

    while (i < str.size() && isdigit(str[i])) {
        hasDigit = true;
        ++i;
    }

    while (i < str.size() && isspace(str[i])) {
        ++i;
    }

    return hasDigit && i == str.size();
}

class Vertex{
private:
    int VERTEX_ID;
    double weight;

public:
    Vertex(int _VERTEX_ID, double _weight) : VERTEX_ID(_VERTEX_ID), weight(_weight) {}

    int getNumberOfVertex() const {
        return VERTEX_ID;
    }

    void setNumberOfVertex(int VERTEX_ID) {
        Vertex::VERTEX_ID = VERTEX_ID;
    }

    double getWeight() const {
        return weight;
    }

    void setWeight(double weight) {
        Vertex::weight = weight;
    }
};

class Graph{
private:
    int GRAPH_ID;
    vector<Vertex *> vertices;

public:
    Graph(int GRAPH_ID) {
        this->GRAPH_ID = GRAPH_ID;
    }

    ~Graph() {
        for (auto *ptr : vertices) {
            delete ptr;
            ptr = nullptr;
        }
        vertices.clear();
    }

    int getNo() const {
        return GRAPH_ID;
    }

    void addVertexGraphClass(const int VERTEX_ID, const double weight) {
        auto *newVertex = new Vertex(VERTEX_ID, weight);
        vertices.push_back(newVertex);
    }
};

class GraphManagement{
private:
    vector<Graph *> graphs;

public:
    ~GraphManagement() {
        for (auto *ptr : graphs) {
            delete ptr;
            ptr = nullptr;
        }
        graphs.clear();
    }

    // Add graph
    void addGraph(cs graphID) {
        if (!isRealNumber(graphID))
            throw ErrorHappend();

        int GRAPH_ID = stoi(graphID);
        if (!(GRAPH_ID < 100 && GRAPH_ID > 9))
            throw ErrorHappend();

        auto *newGraph = new Graph(GRAPH_ID);
        graphs.push_back(newGraph);
    }

    // Add vertex
    void addVertex(cs graphID, cs vertexID, cs _weight) {
        if (!isRealNumber(graphID) || !isRealNumber(vertexID) || !isRealNumber(_weight))
            throw ErrorHappend();

        if (vertexID.size() != 8)
            throw ErrorHappend();

        int GRAPH_ID = stoi(graphID);
        int VERTEX_ID = stoi(vertexID);
        double weight = stod(_weight);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = -1;
        for (int i = 0;i < graphs.size();i++) {
            if (graphs[i]->getNo() == GRAPH_ID) {
                index = i;
                break;
            }
        }

        graphs[index]->addVertexGraphClass(VERTEX_ID, weight);
    }

    bool isThereThisGraph(const int graphID) const {
        for (auto * graph : graphs) {
            if (graph->getNo() == graphID)
                return true;
        }
        return false;
    }
};

class View{
private:
    GraphManagement graphManagement;
    int numberOfCommands;
    int counter;

public:
    View() {counter = 0;}

    void run() {
        string line, command;
        vector<string> cp;

        cin >> numberOfCommands;
        cin.ignore();

        while (true) {
            getline(cin, line);
            stringstream ss(line);
            while (ss >> command) {
                cp.push_back(command);
            }

            try {
                // New graph
                if (cp[0] == "NEW_GRAPH" && cp.size() == 2) {
                    string graphID = cp[1];
                    graphManagement.addGraph(graphID);
                    counter++;
                }

                // Add vertex
                else if (cp[0] == "ADD_VERTEX") {
                    string graphID = cp[1];
                    string vertexID = cp[2];
                    string weight = cp[3];
                    graphManagement.addVertex(graphID, vertexID, weight);
                    counter++;
                }

                // Invalid command
                else
                    throw ErrorHappend();

                // Exiting the program
                if (counter >= numberOfCommands)
                    break;
            }
            catch (const exception &e) {
                cout << e.what() << endl;
            }
        }
    }
};

int main() {
    View view;
    view.run();
    return 0;
}