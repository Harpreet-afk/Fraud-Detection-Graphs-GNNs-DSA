#include "graph.hpp"
#include "features.hpp"
#include "pagerank.hpp"
#include "heuristics.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "============================================" << endl;
    cout << "  Fraud Detection - C++ Feature Engine" << endl;
    cout << "============================================" << endl;

    // Step 1: Load graph from edges.csv
    cout << "\n--- Building graph ---" << endl;
    Graph g;
    g.loadFromCSV("../data/edges.csv");

    // Step 2: Compute structural features (degree, clustering)
    cout << "\n--- Computing structural features ---" << endl;
    auto fmap = computeFeatures(g);

    // Step 3: Compute PageRank
    cout << "\n--- Computing PageRank ---" << endl;
    auto pr = computePageRank(g);
    for (auto &[node, val] : pr)
        fmap[node].pagerank = val;
    cout << "[OK] Computed PageRank for " << pr.size() << " nodes" << endl;

    // Step 4: Load transactional features from raw_features.csv
    cout << "\n--- Loading transactional features ---" << endl;
    loadRawFeatures("../data/raw_features.csv", fmap);

    // Step 5: Compute heuristic scores (for baseline comparison)
    cout << "\n--- Computing heuristic scores ---" << endl;
    computeHeuristicScores(fmap);
    cout << "[OK] Computed heuristic scores" << endl;

    // Step 6: Export
    cout << "\n--- Exporting ---" << endl;
    exportCSV(fmap);          // features.csv for GNN input
    exportHeuristic(fmap);    // heuristic_scores.csv for baseline evaluation

    cout << "\n============================================" << endl;
    cout << "  Done! Files written to ../data/" << endl;
    cout << "  Next step: run the GNN pipeline (train.py)" << endl;
    cout << "============================================" << endl;

    return 0;
}