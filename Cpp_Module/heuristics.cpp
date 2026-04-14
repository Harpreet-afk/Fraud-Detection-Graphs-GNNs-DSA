#include "heuristics.h"

Heuristics::Heuristics(Graph &graph, vector<int> &labels)
    : g(graph), fraud(labels) {}

int Heuristics::degree(int node) {
    return g.adj[node].size();
}

int Heuristics::suspiciousNeighbors(int node) {
    int count = 0;
    for (int nb : g.adj[node]) {
        if (fraud[nb] == 1) count++;
    }
    return count;
}

double Heuristics::transactionVelocity(int node) {
    // simple assumption: more connections = higher velocity
    return g.adj[node].size() * 0.5;
}

double Heuristics::riskScore(int node) {
    double score = 0;
    score += 0.4 * degree(node);
    score += 0.4 * suspiciousNeighbors(node);
    score += 0.2 * transactionVelocity(node);
    return score;
}