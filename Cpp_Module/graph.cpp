#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void Graph::addEdge(int u, int v, double amount, int time) {
    adj[u].push_back({v, amount, time});
    adj[v]; // ensure node exists
}

void Graph::loadFromCSV(const string &edgesPath) {
    ifstream file(edgesPath);
    if (!file.is_open()) {
        cerr << "[ERROR] Could not open " << edgesPath << endl;
        return;
    }

    string line;
    // Skip header line
    getline(file, line);

    int edgeCount = 0;
    while (getline(file, line)) {
        // Remove carriage return if present (Windows line endings)
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        stringstream ss(line);
        string srcStr, dstStr;

        getline(ss, srcStr, ',');
        getline(ss, dstStr, ',');

        int src = stoi(srcStr);
        int dst = stoi(dstStr);

        // For structural features we only need connectivity (amount=0, time=0)
        addEdge(src, dst, 0.0, 0);
        edgeCount++;
    }

    file.close();
    cout << "[OK] Loaded graph from " << edgesPath
         << ": " << adj.size() << " nodes, " << edgeCount << " edges" << endl;
}