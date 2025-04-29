import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

# Read the simulation data
if len(sys.argv) != 2:
    print("Usage: python plot_river.py <filename>")
    sys.exit(1)

filename = sys.argv[1]
data = pd.read_csv(filename)
filename = filename.split('/')[-1]  # Extract the filename from the path

# Plot
plt.figure(figsize=(10, 6))
plt.plot(data['x'], data['pollutant_concentration'], color='red', linewidth=2)
plt.xlabel('Distance downstream (x) [m]')
plt.ylabel('Pollutant Concentration p(x,t)')
plt.title('Pollutant Traveling Wave at t = 20 seconds')
plt.grid(True)
os.makedirs("./Plots", exist_ok=True)
plt.savefig("./Plots/" + filename.replace('.csv', '.png'), dpi=300, bbox_inches='tight')
plt.show()
