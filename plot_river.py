import pandas as pd
import sys
import os
import matplotlib.pyplot as plt

# Read the simulation data
if len(sys.argv) != 2:
    print("Usage: python plot_river.py <filename>")
    sys.exit(1)

filename = sys.argv[1]
data = pd.read_csv(filename)    # filename: ./Results/xyz.csv

filename = filename.split('/')[-1]  # Extract the filename from the path

# Create the plot
plt.figure(figsize=(10, 6))

# Plot pollutant concentration
plt.plot(data['x'], data['pollutant_concentration'], label='Pollutant Concentration p(x)', color='red', linewidth=2)

# Plot oxygen concentration
plt.plot(data['x'], data['oxygen_concentration'], label='Oxygen Concentration s(x)', color='blue', linewidth=2)

# Labels and title
plt.xlabel('Distance downstream (x) [m]')
plt.ylabel('Concentration')
plt.title('Pollutant and Oxygen Concentrations in River')
plt.legend()
plt.grid(True)

# Create the directory if it does not exist
os.makedirs("./Plots", exist_ok=True)
plt.savefig("./Plots/" + filename.replace('.csv', '.png'), dpi=300, bbox_inches='tight')

# Show the plot
plt.show()
