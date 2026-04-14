#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<int>> adj;

    Graph(int nodes);
    void addEdge(int u, int v);
};
#endif