#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <fstream>
#include <set>
using namespace std;

class Node {
public:
    string value;
    vector<Node*> edges;
    bool visited;
    Node* parent;

    Node(string v) {
        value = v;
        visited = false;
        parent = nullptr;
    }

    void addEdge(Node* neighbor) {
        edges.push_back(neighbor);
    }
};

class Graph {
public:
    vector<Node*> nodes;
    unordered_map<string, Node*> map;

    void addNode(string name) {
        if (!map.count(name)) {
            Node* newNode = new Node(name);
            nodes.push_back(newNode);
            map[name] = newNode;
        }
    }

    void addEdge(string a, string b) {
        Node* nodeA = map[a];
        Node* nodeB = map[b];
        nodeA->addEdge(nodeB);
        nodeB->addEdge(nodeA);
    }

    Node* getNode(string name) {
        if (map.count(name))
            return map[name];
        return nullptr;
    }

    void reset() {
        for (auto n : nodes) {
            n->visited = false;
            n->parent = nullptr;
        }
    }
};

void exportToDot(Graph& graph, vector<Node*>& path) {

    ofstream file("graph.dot");
    file << "graph G {\n";
    file << "layout=neato;\n";
    file << "overlap=false;\n";
    file << "splines=true;\n";

    set<pair<string, string>> pathEdges;

    for (int i = 0; i < path.size() - 1; i++) {
        string a = path[i]->value;
        string b = path[i + 1]->value;
        if (a < b)
            pathEdges.insert({a, b});
        else
            pathEdges.insert({b, a});
    }

    for (auto node : graph.nodes) {
        for (auto neighbor : node->edges) {
            if (node->value < neighbor->value) {

                pair<string, string> edge = {node->value, neighbor->value};

                if (pathEdges.count(edge)) {
                    file << "\"" << node->value << "\" -- \"" 
                         << neighbor->value 
                         << "\" [color=red, penwidth=3];\n";
                } else {
                    file << "\"" << node->value << "\" -- \"" 
                         << neighbor->value << "\";\n";
                }
            }
        }
    }

    file << "}\n";
    file.close();

    system("dot -Tpng graph.dot -o graph.png");
}

int main() {

    Graph graph;

    vector<pair<string, vector<string>>> data = {
        {"Cloud Security Platform",
         {"System Architect", "Backend Engineer", "DevOps Specialist",
          "Security Analyst", "Database Engineer"}},

        {"AI Recommendation Engine",
         {"Machine Learning Engineer", "Data Scientist",
          "Backend Engineer", "System Architect", "Product Manager"}},

        {"Mobile Banking Application",
         {"Android Developer", "iOS Developer",
          "Security Analyst", "Backend Engineer", "System Architect"}}
    };

    // Build Graph
    for (auto& item : data) {
        string project = item.first;
        graph.addNode(project);

        for (auto& role : item.second) {
            graph.addNode(role);
            graph.addEdge(project, role);
        }
    }

    string startRole;

    cout << "\n========= AVAILABLE ROLES =========\n";
    cout << "System Architect\n";
    cout << "Backend Engineer\n";
    cout << "DevOps Specialist\n";
    cout << "Security Analyst\n";
    cout << "Database Engineer\n";
    cout << "Machine Learning Engineer\n";
    cout << "Data Scientist\n";
    cout << "Product Manager\n";
    cout << "Android Developer\n";
    cout << "iOS Developer\n";
    cout << "====================================\n\n";

    cout << "Enter your role EXACTLY as shown above: ";
    getline(cin, startRole);

    // Remove leading spaces
    while (!startRole.empty() && startRole.front() == ' ')
        startRole.erase(startRole.begin());

    // Remove trailing spaces
    while (!startRole.empty() && startRole.back() == ' ')
        startRole.pop_back();

    Node* start = graph.getNode(startRole);
    Node* end = graph.getNode("System Architect");

    if (!start || !end) {
        cout << "\n❌ Invalid role entered.\n";
        cout << "Please enter the role exactly as displayed above.\n";
        return 0;
    }

    // BFS
    graph.reset();
    queue<Node*> q;

    start->visited = true;
    q.push(start);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current == end)
            break;

        for (auto neighbor : current->edges) {
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->parent = current;
                q.push(neighbor);
            }
        }
    }

    // Reconstruct Path
    vector<Node*> path;
    Node* temp = end;

    while (temp != nullptr) {
        path.push_back(temp);
        temp = temp->parent;
    }

    cout << "\n========== SHORTEST COLLABORATION PATH ==========\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i]->value;
        if (i != 0) cout << " --> ";
    }

    exportToDot(graph, path);

    cout << "\n\nGraph visualization saved as graph.png\n";
    cout << "=================================================\n";

    return 0;
}
