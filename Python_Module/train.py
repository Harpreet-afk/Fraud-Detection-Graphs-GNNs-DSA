import torch
import torch.nn.functional as F
from torch_geometric.nn import SAGEConv
from load_data import load_data

# Device setup (Mac M3 support)
device = torch.device("mps" if torch.backends.mps.is_available() else "cpu")

# Load dataset
x, edge_index, y = load_data()

# Move to device
x = x.to(device)
edge_index = edge_index.to(device)
y = y.to(device)

# Define GNN Model
class GNN(torch.nn.Module):
    def __init__(self, in_channels, hidden, out_channels):
        super().__init__()
        self.conv1 = SAGEConv(in_channels, hidden)
        self.conv2 = SAGEConv(hidden, out_channels)

    def forward(self, x, edge_index):
        x = self.conv1(x, edge_index)
        x = F.relu(x)
        x = self.conv2(x, edge_index)
        return torch.sigmoid(x)

# Initialize model
model = GNN(in_channels=x.shape[1], hidden=8, out_channels=1).to(device)

optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# Training loop
for epoch in range(200):
    model.train()
    optimizer.zero_grad()

    out = model(x, edge_index).squeeze()
    loss = F.binary_cross_entropy(out, y)

    loss.backward()
    optimizer.step()

    if epoch % 10 == 0:
        print(f"Epoch {epoch}, Loss: {loss.item()}")

# Final predictions
model.eval()
pred = model(x, edge_index).squeeze()

print("\nFinal Predictions:")
for i, val in enumerate(pred):
    label = "FRAUD" if val.item() > 0.5 else "NORMAL"
    print(f"Node {i}: {val.item():.3f} -> {label}")