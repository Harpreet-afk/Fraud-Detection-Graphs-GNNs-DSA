import torch
import pandas as pd

def load_data():
    # Load edges
    edges = []
    with open("../data/edges.txt", "r") as f:   # ✅ FIXED
        for line in f:
            u, v = map(int, line.split())
            edges.append([u, v])

    edge_index = torch.tensor(edges, dtype=torch.long).t().contiguous()

    # Load features
    df_features = pd.read_csv("../data/features.csv")   # ✅ FIXED
    features = df_features.iloc[:, 1:].values
    features = (features - features.mean(axis=0)) / features.std(axis=0)  # ✅ normalize
    x = torch.tensor(features, dtype=torch.float)

    # Load labels
    df_labels = pd.read_csv("../data/labels.csv")   # ✅ FIXED
    y = torch.tensor(df_labels["label"].values, dtype=torch.float)

    return x, edge_index, y