#ifndef FEATURES_HPP
#define FEATURES_HPP

#include "graph.hpp"
#include <unordered_map>
#include <string>

struct Features {
    // Structural features (computed by C++ from graph)
    double degree;
    double clustering;
    double pagerank;

    // Transactional features (loaded from raw_features.csv)
    double tx_count;
    double total_amount;
    double avg_amount;
    double max_amount;
    double std_amount;
    double tx_frequency;

    // Heuristic score (for baseline comparison, NOT fed to GNN)
    double heuristic_score;
};

// Compute structural features (degree, clustering) for all nodes
unordered_map<int, Features> computeFeatures(Graph &g);

// Load transactional features from raw_features.csv and merge into feature map
void loadRawFeatures(const string &path, unordered_map<int, Features> &fmap);

#endif