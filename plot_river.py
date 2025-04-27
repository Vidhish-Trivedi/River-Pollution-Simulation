import pandas as pd
import matplotlib.pyplot as plt

# Read the simulation data
data = pd.read_csv('river_simulation.csv')

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

# Show the plot
plt.show()
