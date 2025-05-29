#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class ErrorHappend : public exception {
public:
    const char* what() const noexcept override {
        return "INVALID COMMAND";
    }
};

bool is_number(const string &s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

class Vertex{
private:
    int numberOfVertex;
    double weight;

public:
    Vertex(int _numberOfVertex, double _weight) : numberOfVertex(_numberOfVertex), weight(_weight) {}

    int getNumberOfVertex() const {
        return numberOfVertex;
    }

    void setNumberOfVertex(int numberOfVertex) {
        Vertex::numberOfVertex = numberOfVertex;
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
    int No;
    vector<Vertex> vertices;

public:
    Graph(int GRAPH_ID) {
        No = GRAPH_ID;
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
    void addGraph() {

    }
};

class View{
private:
    GraphManagement graphManagement;

public:
    void run() {
        string line, command;
        vector<string> cp;

        while (true) {
            stringstream ss(line);
            while (ss >> command) {
                cp.push_back(command);
            }

            try {
                // New graph
                if (cp[0] == "NEW_GRAPH" && cp.size() == 2) {
                    string graphID = cp[1];

                }

                // Helper function to see is the ID is number or not

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