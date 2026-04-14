#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "graph.h"
#include <vector>
using namespace std;

class Heuristics {
public:
    Graph &g;
    vector<int> fraud;

    Heuristics(Graph &graph, vector<int> &labels);

    int degree(int node);
    int suspiciousNeighbors(int node);
    double transactionVelocity(int node);
    double riskScore(int node);
};
#endif