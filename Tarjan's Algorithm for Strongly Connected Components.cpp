#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<int>* adj;  // Adjacency list
    int* disc;  // Discovery times of visited vertices
    int* low;   // Earliest visited vertex reachable from the subtree
    bool* inStack;  // Whether the vertex is in the stack
    stack<int> st;  // Stack for SCC vertices
    int time;  // Global time counter

    void SCCUtil(int u);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void SCC();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
    disc = new int[V];
    low = new int[V];
    inStack = new bool[V];
    fill(disc, disc + V, -1);
    fill(low, low + V, -1);
    fill(inStack, inStack + V, false);
    time = 0;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);  // Directed edge v -> w
}

void Graph::SCCUtil(int u) {
    disc[u] = low[u] = ++time;
    st.push(u);
    inStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            SCCUtil(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        cout << "SCC: ";
        while (st.top() != u) {
            int v = st.top();
            cout << v << " ";
            inStack[v] = false;
            st.pop();
        }
        cout << st.top() << endl;
        inStack[u] = false;
        st.pop();
    }
}

void Graph::SCC() {
    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            SCCUtil(i);
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Strongly Connected Components are:\n";
    g.SCC();

    return 0;
}
