#include <iostream>
#include "graph.h"
#include "heuristics.h"
using namespace std;

int main() {
    int n = 6;
    Graph g(n);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(1,5);

    vector<int> labels = {0,1,0,1,0,0};

    Heuristics h(g, labels);

    cout << "Heuristic Fraud Scores:\n";

    for(int i=0;i<n;i++){
        double score = h.riskScore(i);
        cout << "Node " << i << " Score: " << score;

        if(score > 2.0) cout << " -> FRAUD\n";
        else cout << " -> NORMAL\n";
    }
}