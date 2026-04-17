import torch
from gnn_model import FraudGNN
from load_data import load_data
from evaluate import evaluate

data = load_data()

model = FraudGNN(in_channels=data.num_features, hidden=32)

# Compute class weight for balanced training
train_indices = data.train_mask.nonzero(as_tuple=True)[0]
train_labels = data.y[train_indices].squeeze()

fraud_count = (train_labels == 1).sum()
legit_count = (train_labels == 0).sum()
pos_weight = legit_count / max(fraud_count, 1)

print(f"\n[Training] {legit_count} legit, {fraud_count} fraud nodes")
print(f"[Training] Using pos_weight = {pos_weight:.2f} to balance loss\n")

criterion = torch.nn.BCEWithLogitsLoss(pos_weight=pos_weight)
optimizer = torch.optim.Adam(model.parameters(), lr=0.005)

for epoch in range(300):
    model.train()
    optimizer.zero_grad()

    out = model(data.x, data.edge_index)

    # Compute loss only on training nodes
    loss = criterion(out[data.train_mask], data.y[data.train_mask])

    loss.backward()
    optimizer.step()

    if epoch % 25 == 0 or epoch == 299:
        print(f"Epoch {epoch:3d}, Loss: {loss.item():.4f}")

# --- Evaluate after training ---
print("\n" + "=" * 50)
evaluate(model, data)