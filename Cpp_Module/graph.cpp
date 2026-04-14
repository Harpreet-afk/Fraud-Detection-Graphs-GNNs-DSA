#include "graph.h"

Graph::Graph(int nodes) {
    n = nodes;
    adj.resize(n);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}