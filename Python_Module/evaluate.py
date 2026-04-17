from sklearn.metrics import precision_score, recall_score, f1_score
import torch
import pandas as pd
import os

def evaluate(model, data):
    model.eval()
    with torch.no_grad():
        logits = model(data.x, data.edge_index)
        preds = torch.sigmoid(logits) > 0.5

    # Only evaluate on LABELED test nodes
    mask = data.test_mask

    y_true = data.y[mask].cpu().numpy()
    y_pred = preds[mask].cpu().numpy()

    precision = precision_score(y_true, y_pred, zero_division=0)
    recall = recall_score(y_true, y_pred, zero_division=0)
    f1 = f1_score(y_true, y_pred, zero_division=0)

    print("\n=== GNN Model Performance ===")
    print("Precision:", precision)
    print("Recall:", recall)  # MOST IMPORTANT
    print("F1-score:", f1)

    # --- Heuristic Baseline Comparison ---
    heuristic_path = os.path.join(os.path.dirname(__file__), "..", "data", "heuristic_scores.csv")
    if os.path.exists(heuristic_path):
        print("\n=== Heuristic Baseline Performance ===")
        heur_df = pd.read_csv(heuristic_path)

        # Get labels for test nodes
        test_indices = mask.nonzero(as_tuple=True)[0].cpu().numpy()
        heur_scores = heur_df.set_index("node")["heuristic_score"]

        # Try multiple thresholds and pick the best F1
        best_f1 = 0
        best_threshold = 0.5
        for threshold in [0.3, 0.4, 0.5, 0.6, 0.7, 0.8]:
            h_preds = []
            h_true = []
            for idx in test_indices:
                if idx in heur_scores.index:
                    h_preds.append(1 if heur_scores[idx] >= threshold else 0)
                    h_true.append(int(data.y[idx].item()))

            if len(h_preds) > 0:
                curr_f1 = f1_score(h_true, h_preds, zero_division=0)
                if curr_f1 > best_f1:
                    best_f1 = curr_f1
                    best_threshold = threshold

        # Report best heuristic threshold
        h_preds = []
        h_true = []
        for idx in test_indices:
            if idx in heur_scores.index:
                h_preds.append(1 if heur_scores[idx] >= best_threshold else 0)
                h_true.append(int(data.y[idx].item()))

        h_precision = precision_score(h_true, h_preds, zero_division=0)
        h_recall = recall_score(h_true, h_preds, zero_division=0)
        h_f1 = f1_score(h_true, h_preds, zero_division=0)

        print(f"Best threshold: {best_threshold}")
        print(f"Precision: {h_precision}")
        print(f"Recall: {h_recall}")
        print(f"F1-score: {h_f1}")

        print("\n=== Comparison ===")
        print(f"GNN F1:       {f1:.4f}")
        print(f"Heuristic F1: {h_f1:.4f}")
        if f1 > h_f1:
            print(">>> GNN outperforms heuristic baseline <<<")
        else:
            print(">>> Heuristic baseline matches or exceeds GNN <<<")
    else:
        print("\n[!] No heuristic_scores.csv found — skipping baseline comparison")
        print("    Run the C++ module first to generate heuristic scores")