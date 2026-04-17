#include "features.hpp"
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>

// Degree
double computeDegree(Graph &g, int node) {
    return g.adj[node].size();
}

// Clustering Coefficient
double clusteringCoeff(Graph &g, int node) {
    auto &neighbors = g.adj[node];
    int k = neighbors.size();
    if (k < 2) return 0;

    unordered_set<int> neighborSet;
    for (auto &e : neighbors) neighborSet.insert(e.to);

    int links = 0;
    for (auto &e : neighbors) {
        for (auto &x : g.adj[e.to]) {
            if (neighborSet.count(x.to)) links++;
        }
    }
    return (double)links / (k * (k - 1));
}

unordered_map<int, Features> computeFeatures(Graph &g) {
    unordered_map<int, Features> fmap;

    int count = 0;
    int total = g.adj.size();

    for (auto &[node, _] : g.adj) {
        Features f = {};  // zero-initialize all fields
        f.degree = computeDegree(g, node);
        f.clustering = clusteringCoeff(g, node);
        f.pagerank = 0; // filled later by computePageRank

        fmap[node] = f;

        count++;
        if (count % 10000 == 0 || count == total)
            cout << "\r[..] Computing structural features: "
                 << count << "/" << total << " nodes" << flush;
    }
    cout << endl;
    cout << "[OK] Computed degree + clustering for " << total << " nodes" << endl;

    return fmap;
}

// Load transactional features from raw_features.csv
// CSV format: node,tx_count,total_amount,avg_amount,max_amount,std_amount,tx_frequency
void loadRawFeatures(const string &path, unordered_map<int, Features> &fmap) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[WARNING] Could not open " << path
             << " — transactional features will be zero" << endl;
        return;
    }

    string line;
    // Skip header
    getline(file, line);

    int loaded = 0;
    int skipped = 0;
    while (getline(file, line)) {
        // Remove carriage return if present
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        try {
            stringstream ss(line);
            string token;

            // Parse: node,tx_count,total_amount,avg_amount,max_amount,std_amount,tx_frequency
            getline(ss, token, ','); int node = stoi(token);
            getline(ss, token, ','); double tx_count = stod(token);
            getline(ss, token, ','); double total_amount = stod(token);
            getline(ss, token, ','); double avg_amount = stod(token);
            getline(ss, token, ','); double max_amount = stod(token);
            getline(ss, token, ','); double std_amount = stod(token);
            getline(ss, token, ','); double tx_frequency = stod(token);

            // Merge into existing feature map (structural features already set)
            if (fmap.count(node)) {
                fmap[node].tx_count = tx_count;
                fmap[node].total_amount = total_amount;
                fmap[node].avg_amount = avg_amount;
                fmap[node].max_amount = max_amount;
                fmap[node].std_amount = std_amount;
                fmap[node].tx_frequency = tx_frequency;
                loaded++;
            }
        } catch (const exception &e) {
            skipped++;
            if (skipped <= 3)
                cerr << "[WARNING] Skipping malformed line: " << line << endl;
        }
    }

    if (skipped > 0)
        cerr << "[WARNING] Skipped " << skipped
             << " malformed lines (ensure raw_features.csv has numeric node IDs)" << endl;

    file.close();
    cout << "[OK] Loaded transactional features for " << loaded << " nodes from " << path << endl;
}