#include <fstream>
#include <iostream>
#include "features.hpp"

// Export features.csv for GNN input (NO heuristic score column)
// Columns match what load_data.py expects: node + 9 feature columns
void exportCSV(unordered_map<int, Features> &fmap) {
    ofstream feats("../data/features.csv");
    if (!feats.is_open()) {
        cerr << "[ERROR] Could not open ../data/features.csv for writing" << endl;
        return;
    }

    feats << "node,degree,pagerank,clustering_coeff,tx_count,total_amount,avg_amount,max_amount,std_amount,tx_frequency\n";

    // Write in sorted node order for consistency
    vector<int> nodes;
    for (auto &[node, _] : fmap) nodes.push_back(node);
    sort(nodes.begin(), nodes.end());

    for (int node : nodes) {
        auto &f = fmap[node];
        feats << node << ","
              << f.degree << ","
              << f.pagerank << ","
              << f.clustering << ","
              << f.tx_count << ","
              << f.total_amount << ","
              << f.avg_amount << ","
              << f.max_amount << ","
              << f.std_amount << ","
              << f.tx_frequency << "\n";
    }

    feats.close();
    cout << "[OK] Wrote ../data/features.csv (" << nodes.size() << " nodes, 9 feature columns)" << endl;
}

// Export heuristic scores to a separate CSV (for baseline evaluation, NOT GNN input)
void exportHeuristic(unordered_map<int, Features> &fmap) {
    ofstream heur("../data/heuristic_scores.csv");
    if (!heur.is_open()) {
        cerr << "[ERROR] Could not open ../data/heuristic_scores.csv for writing" << endl;
        return;
    }

    heur << "node,heuristic_score\n";

    vector<int> nodes;
    for (auto &[node, _] : fmap) nodes.push_back(node);
    sort(nodes.begin(), nodes.end());

    for (int node : nodes) {
        heur << node << "," << fmap[node].heuristic_score << "\n";
    }

    heur.close();
    cout << "[OK] Wrote ../data/heuristic_scores.csv (" << nodes.size() << " nodes)" << endl;
}