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

// -----------------Model-----------------
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

class Edge{
private:
    int START_VERTEX_ID;
    int END_VERTEX_ID;
    double WEIGHT;

public:
    Edge(int svi, int evi, double w) : START_VERTEX_ID(svi), END_VERTEX_ID(evi), WEIGHT(w) {}

    int getEndVertexId() const {
        return END_VERTEX_ID;
    }

    int getStartVertexId() const {
        return START_VERTEX_ID;
    }

    double getWeight() const {
        return WEIGHT;
    }

    void setWeight(double weight) {
        WEIGHT = weight;
    }

    bool connectsVertices(int v1, int v2) const {
        return (START_VERTEX_ID == v1 && END_VERTEX_ID == v2) ||
               (START_VERTEX_ID == v2 && END_VERTEX_ID == v1);
    }
};

class Graph{
private:
    int GRAPH_ID;
    map<int, Vertex> vertices;
    vector<Edge> edges;

public:
    Graph(int GRAPH_ID) {
        this->GRAPH_ID = GRAPH_ID;
    }

    ~Graph() {
        vertices.clear();
    }

    int getNo() const {
        return GRAPH_ID;
    }

    void addVertexGraphClass(const int VERTEX_ID, const double weight) {
        Vertex newVertex(VERTEX_ID, weight);
        vertices.insert({VERTEX_ID, newVertex});
    }

    void addEdgeGraphClass(const int START_VERTEX_ID, const int END_VERTEX_ID, const double WEIGHT) {
        if (vertices.count(START_VERTEX_ID) == 1 && vertices.count(END_VERTEX_ID) == 1) {
            Edge newEdge(START_VERTEX_ID, END_VERTEX_ID, WEIGHT);
            edges.push_back(newEdge);
        }
    }

    void deleteVertexGraphClass(const int VERTEX_ID) {
        vertices.erase(VERTEX_ID);

        for (auto it = edges.begin();it != edges.end();) {
            if (it->connectsVertices(VERTEX_ID, it->getStartVertexId()) || it->connectsVertices(VERTEX_ID, it->getEndVertexId()))
                it = edges.erase(it);
            else
                it++;
        }
    }

    void deleteEdgeGraphClass(const int START_VERTEX_ID, const int END_VERTEX_ID) {
        for (auto it = edges.begin();it != edges.end();) {
            if (it->connectsVertices(START_VERTEX_ID,END_VERTEX_ID))
                it = edges.erase(it);
            else
                it++;
        }
    }

    void changeVertexWeight(const int vertexID, const double newWeight) {
        auto it = vertices.find(vertexID);
        if (it != vertices.end())
            it->second.setWeight(newWeight);
    }

    void changeEdgeWeight(const int START_VERTEX_ID, const int END_VERTEX_ID, const double WEIGHT) {
        for (auto it = edges.begin();it != edges.end();) {
            if (it->connectsVertices(START_VERTEX_ID,END_VERTEX_ID)) {
                it->setWeight(WEIGHT);
            }
        }
    }
};

// -----------------Controller-----------------
class GraphManagement{
private:
    vector<Graph> graphs;

public:
    ~GraphManagement() {
        graphs.clear();
    }

    // Add graph
    void addGraph(cs graphID) {
        checkInvalidCommands(graphID);

        int GRAPH_ID = stoi(graphID);
        if (!(GRAPH_ID < 100 && GRAPH_ID > 9))
            throw ErrorHappend();

        Graph newGraph(GRAPH_ID);
        graphs.push_back(newGraph);
    }

    // Add vertex
    void addVertex(cs graphID, cs vertexID, cs _weight) {
        checkInvalidCommands(graphID,vertexID,"",_weight);

        int GRAPH_ID = stoi(graphID);
        int VERTEX_ID = stoi(vertexID);
        double weight = stod(_weight);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].addVertexGraphClass(VERTEX_ID, weight);
    }

    // Add edge
    void addEdge(cs graphID, cs startVertexID, cs endVertexID, cs _weight) {
        checkInvalidCommands(graphID,startVertexID,endVertexID,_weight);

        int GRAPH_ID = stoi(graphID);
        int START_VERTEX_ID = stoi(startVertexID);
        int END_VERTEX_ID = stoi(endVertexID);
        double WEIGHT = stod(_weight);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].addEdgeGraphClass(START_VERTEX_ID, END_VERTEX_ID, WEIGHT);
    }

    // Delete vertex
    void delVertex(cs graphID, cs vertexID) {
        checkInvalidCommands(graphID,vertexID);

        int GRAPH_ID = stoi(graphID);
        int VERTEX_ID = stoi(vertexID);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].deleteVertexGraphClass(VERTEX_ID);
    }

    // Delete edge
    void delEdge(cs graphID, cs startVertexID, cs endVertexID) {
        checkInvalidCommands(graphID,startVertexID,endVertexID);

        int GRAPH_ID = stoi(graphID);
        int START_VERTEX_ID = stoi(startVertexID);
        int END_VERTEX_ID = stoi(endVertexID);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].deleteEdgeGraphClass(START_VERTEX_ID, END_VERTEX_ID);
    }

    // Edit vertex
    void editVertex(cs graphID, cs vertexID, cs weight) {
        checkInvalidCommands(graphID, vertexID,"", weight);

        int GRAPH_ID = stoi(graphID);
        int VERTEX_ID = stoi(vertexID);
        int WEIGHT = stod(weight);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].changeVertexWeight(VERTEX_ID,WEIGHT);
    }

    // Edit edge
    void editEdge(cs graphID, cs startVertexID, cs endVertexID, cs weight) {
        checkInvalidCommands(graphID, startVertexID,endVertexID, weight);

        int GRAPH_ID = stoi(graphID);
        int START_VERTEX_ID = stoi(startVertexID);
        int END_VERTEX_ID = stoi(endVertexID);
        int WEIGHT = stod(weight);
        if (!isThereThisGraph(GRAPH_ID))
            throw ErrorHappend();

        int index = getGraphsIndex(GRAPH_ID);
        graphs[index].changeEdgeWeight(START_VERTEX_ID,END_VERTEX_ID,WEIGHT);
    }

    bool isThereThisGraph(const int graphID) const {
        for (const Graph &graph : graphs) {
            if (graph.getNo() == graphID)
                return true;
        }
        return false;
    }

    int getGraphsIndex(const int GRAPH_ID) {
        int index = -1;
        for (int i = 0;i < graphs.size();i++) {
            if (graphs[i].getNo() == GRAPH_ID) {
                index = i;
                break;
            }
        }
        return index;
    }

    void checkInvalidCommands(cs GRAPH_ID = "", cs vertex1ID = "", cs vertex2ID = "", cs weight = "") {
        if (!GRAPH_ID.empty())
            if (!isRealNumber(GRAPH_ID))
                throw ErrorHappend();
        if (!vertex1ID.empty()) {
            if (!isRealNumber(vertex1ID))
                throw ErrorHappend();
            if (vertex1ID.size() != 8)
                throw ErrorHappend();
        }
        if (!vertex2ID.empty()) {
            if (!isRealNumber(vertex2ID))
                throw ErrorHappend();
            if (vertex1ID.size() != 8)
                throw ErrorHappend();
        }
        if (!weight.empty())
            if (!isRealNumber(weight))
                throw ErrorHappend();
    }
};

// -----------------View-----------------
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
                else if (cp[0] == "ADD_VERTEX" && cp.size() == 4) {
                    string graphID = cp[1];
                    string vertexID = cp[2];
                    string weight = cp[3];
                    graphManagement.addVertex(graphID, vertexID, weight);
                    counter++;
                }

                // Add edge
                else if (cp[0] == "ADD_EDGE" && cp.size() == 5) {
                    string graphID = cp[1];
                    string startVertexID = cp[2];
                    string endVertexID = cp[3];
                    string weight = cp[4];
                    graphManagement.addEdge(graphID,startVertexID,endVertexID,weight);
                    counter++;
                }

                // Delete vertex
                else if (cp[0] == "DEL_VERTEX" && cp.size() == 3) {
                    string graphID = cp[1];
                    string vertexID = cp[2];
                    graphManagement.delVertex(graphID, vertexID);
                    counter++;
                }

                // Delete edge
                else if (cp[0] == "DEL_EDGE" && cp.size() == 4) {
                    string graphID = cp[1];
                    string startVertexID = cp[2];
                    string endVertexID = cp[3];
                    graphManagement.delEdge(graphID, startVertexID, endVertexID);
                    counter++;
                }

                // Edit vertex
                else if (cp[0] == "EDIT_VERTEX" && cp.size() == 4) {
                    string graphID = cp[1];
                    string vertexID = cp[2];
                    string weight = cp[3];
                    graphManagement.editVertex(graphID, vertexID, weight);
                    counter++;
                }

                // Edit edge
                else if (cp[0] == "EDIT_EDGE" && cp.size() == 5) {
                    string graphID = cp[1];
                    string startVertexID = cp[2];
                    string endVertexID = cp[3];
                    string weight = cp[4];
                    graphManagement.editEdge(graphID, startVertexID, endVertexID, weight);
                    counter++;
                }

                // Invalid command
                else
                    throw ErrorHappend();

                // Exiting the program
                if (counter >= numberOfCommands)
                    break;

                cp.clear();
            }
            catch (const exception &e) {
                cout << e.what() << endl;
                cp.clear();
            }
        }
    }
};

int main() {
    View view;
    view.run();
    return 0;
}