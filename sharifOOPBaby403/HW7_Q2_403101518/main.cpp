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
bool isNumber(cs s) {
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
    vector<Vertex *> vertices;

public:
    Graph(int GRAPH_ID) {
        No = GRAPH_ID;
    }

    ~Graph() {
        for (auto *ptr : vertices) {
            delete ptr;
            ptr = nullptr;
        }
        vertices.clear();
    }

    int getNo() const {
        return No;
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
        if (!isNumber(graphID))
            throw ErrorHappend();

        int GRAPH_ID = stoi(graphID);
        if (!(GRAPH_ID < 100 && GRAPH_ID > 9))
            throw ErrorHappend();

        auto *newGraph = new Graph(GRAPH_ID);
        graphs.push_back(newGraph);
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
                    string weight =
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