#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// Constants
const double c = 1.0;            // River velocity (e.g., meters per second)
const double mu = 0.1;           // Pollutant decay rate
const double mu1 = 0.2;          // Re-oxygenation rate
const double gamma_source = 5.0; // Pollutant source strength at x=0
const double s_max = 10.0;       // Maximum dissolved oxygen concentration
const double x_max = 100.0;      // Length of river to simulate (meters)
const int N = 1000;              // Number of spatial steps
const double dx = x_max / N;     // Spatial step size

// Function to compute pollutant concentration at x
double pollutant_concentration(double x)
{
    return gamma_source * exp(-mu * x / c);
}

int main()
{
    // Discretized domain
    vector<double> x(N + 1);
    vector<double> p(N + 1); // pollutant concentration
    vector<double> s(N + 1); // oxygen concentration

    // Initialize x and p
    for (int i = 0; i <= N; ++i)
    {
        x[i] = i * dx;
        p[i] = pollutant_concentration(x[i]);
    }

    // Initialize oxygen concentration
    s[0] = s_max; // boundary condition at x = 0

    // Forward Euler method to solve for s(x)
    for (int i = 0; i < N; ++i)
    {
        double ds_dx = (-mu * p[i] + mu1 * (s_max - s[i])) / c;
        s[i + 1] = s[i] + ds_dx * dx;
    }

    // Output results to a CSV file
    ofstream outfile("river_simulation.csv");
    outfile << "x,pollutant_concentration,oxygen_concentration\n";
    for (int i = 0; i <= N; ++i)
    {
        outfile << x[i] << "," << p[i] << "," << s[i] << "\n";
    }
    outfile.close();

    cout << "Simulation complete. Results saved to 'river_simulation.csv'.\n";
    return 0;
}
