import numpy as np
import matplotlib.pyplot as plt

# Parameters
c = 1.0         # river velocity
mu = 0.1        # pollutant decay rate
mu1 = 0.2       # oxygen re-absorption rate
gamma_source = 5.0   # source strength
s_max = 10.0    # maximum oxygen saturation
x_max = 100.0   # river length
N = 1000        # number of points
dx = x_max / N  # step size

# Discretized space
x = np.linspace(0, x_max, N+1)

# --- Analytic solutions ---
p_analytic = gamma_source * np.exp(-mu * x / c)
coeff = (mu * gamma_source) / (mu1 - mu)
s_analytic = s_max - coeff * (np.exp(-mu * x / c) - np.exp(-mu1 * x / c))

# --- Numerical solutions (Euler Method) ---
p_numerical = np.zeros(N+1)
s_numerical = np.zeros(N+1)

# Boundary conditions
p_numerical[0] = gamma_source
s_numerical[0] = s_max

for i in range(N):
    dp_dx = -(mu / c) * p_numerical[i]
    p_numerical[i+1] = p_numerical[i] + dp_dx * dx
    
    ds_dx = ( -mu * p_numerical[i] + mu1 * (s_max - s_numerical[i]) ) / c
    s_numerical[i+1] = s_numerical[i] + ds_dx * dx

# --- Calculate Errors ---
error_p = np.abs(p_analytic - p_numerical)
error_s = np.abs(s_analytic - s_numerical)

# --- Plot Concentrations ---
plt.figure(figsize=(12, 6))
plt.plot(x, p_analytic, 'r-', label='Pollutant (Analytic)', linewidth=2)
plt.plot(x, p_numerical, 'r--', label='Pollutant (Numerical)', linewidth=1)
plt.plot(x, s_analytic, 'b-', label='Oxygen (Analytic)', linewidth=2)
plt.plot(x, s_numerical, 'b--', label='Oxygen (Numerical)', linewidth=1)
plt.xlabel('Distance downstream x [m]')
plt.ylabel('Concentration')
plt.title('Concentrations: Analytic vs Numerical')
plt.legend()
plt.grid(True)
plt.show()

# --- Plot Errors ---
plt.figure(figsize=(12, 5))

plt.plot(x, error_p, 'r-', label='Pollutant Concentration Error')
plt.plot(x, error_s, 'b-', label='Oxygen Concentration Error')
plt.xlabel('Distance downstream x [m]')
plt.ylabel('Absolute Error')
plt.title('Error between Analytic and Numerical Solutions')
plt.legend()
plt.grid(True)
plt.show()
