## Fraud Detection in Transaction Graphs using GNNs and Graph Heuristics

A hybrid fraud detection system that combines Graph Neural Networks (GNNs) with classical graph algorithms and heuristic scoring to identify suspicious behavior in large-scale transaction networks. The project models financial transactions as a graph where accounts are represented as nodes and transactions as edges.

## Overview

This project integrates:
Graph-based feature engineering (C++)
Heuristic fraud scoring
Graph Attention Networks (GATv2Conv)
Hybrid prediction fusion
Large-scale transaction graph processing

The system captures both:
interpretable rule-based fraud patterns
learned relational patterns using Graph Neural Networks

## System Architecture
Raw Transaction Data
        ↓
Graph Construction (C++)
        ↓
Feature Engineering
(Degree, Clustering, PageRank, Frequency)
        ↓
Heuristic Fraud Scoring
        ↓
CSV Export
(edges.csv, features.csv, labels.csv)
        ↓
GATv2Conv-based GNN (PyTorch Geometric)
        ↓
Fusion Layer
(Heuristic + GNN Prediction)
        ↓
Final Fraud Classification
        ↓
Explainability Output

## Project Structure
Fraud-Detection-Graphs-GNNs-DSA/
│
├── data/
│   ├── edges.csv
│   ├── features.csv
│   ├── labels.csv
│   └── final_predictions.csv
│
├── CPP_Module/
│   ├── graph.hpp
│   ├── graph.cpp
│   ├── features.hpp
│   ├── features.cpp
│   ├── pagerank.hpp
│   ├── pagerank.cpp
│   ├── heuristics.hpp
│   ├── heuristics.cpp
│   ├── export.cpp
│   └── main.cpp
│
├── Python_Module/
│   ├── model.py
│   ├── train.py
│   ├── load_data.py
│   ├── evaluate.py
│   └── fusion.py
│
└── README.md

## Features Extracted
The system computes structural and transactional graph features for every account:
Feature	Description
Degree	Number of connected transactions
Clustering Coefficient	Measures local transaction density
PageRank	Importance/influence of node
Transaction Frequency	Number of transactions performed
Total Amount	Total transferred amount
Heuristic Score	Weighted fraud suspicion score

## GNN Architecture

The project uses Graph Attention Networks v2 (GATv2Conv) from PyTorch Geometric.
Model Highlights
Attention-based message passing
Learns relational fraud patterns
Handles graph-structured financial data
Optimized for imbalanced fraud datasets

## Evaluation Metrics

The system is evaluated using:
Precision
Recall
F1-score

Special focus is given to Recall, since missing fraudulent accounts is costly in fraud detection systems.

## Tech Stack
Languages
C++
Python
Libraries & Frameworks
PyTorch
PyTorch Geometric
Pandas
NumPy
scikit-learn

## Dataset Format
edges.csv
src,dst
230425980,5530458
232022460,232438397
labels.csv
node,label
230425980,0
232438397,1
0 → Non-Fraud
1 → Fraud
features.csv
node,degree,clustering,pagerank,txn_freq,total_amount,heuristic
230425980,12,0.43,0.0021,12,45000,0.67

## Running the Project
Step 1: Compile C++ Module
g++ -std=c++17 main.cpp graph.cpp features.cpp pagerank.cpp heuristics.cpp export.cpp -o run

Run:
./run

This generates:
features.csv
heuristic scores
Step 2: Train GNN
cd Python_Module
python train.py

## Results

The hybrid pipeline combines:
heuristic scoring
graph neural network inference
to improve fraud detection performance and capture suspicious transaction behavior effectively.
