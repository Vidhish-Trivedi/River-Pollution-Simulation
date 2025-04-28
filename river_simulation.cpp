// Steady-State Assumption:
// After some duration, the pollution in river at a given point in space becomes independent of time.
// That is, d(rho)/dt = 0. 

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Struct to hold initial conditions
struct InitialConditions {
    int idx;             // Testcase id
    double c;            // River velocity
    double mu;           // Pollutant decay rate
    double mu1;          // Re-oxygenation rate
    double gamma_source; // Pollutant source strength at x=0
    double s_max;        // Maximum dissolved oxygen concentration
    double x_max;        // Length of river to simulate
    int N;               // Number of spatial steps
};

// Function to compute spatial step size
double compute_dx(const InitialConditions& ic) {
    return ic.x_max / ic.N;
}

// List of test cases with different initial conditions
vector<InitialConditions> test_cases = {
    {1, 1.0, 0.1, 0.2, 5.0, 10.0, 100.0, 1000}, // Test case 1
    {2, 0.8, 0.05, 0.15, 4.0, 8.0, 80.0, 800},  // Test case 2
    {3, 1.2, 0.2, 0.25, 6.0, 12.0, 120.0, 1200}, // Test case 3
    {4, 1.2, 0.2, 0.25, 6.0, 12.0, 120.0, 1200} // Test case 4
};

// Function to compute pollutant concentration at x
double pollutant_concentration(double x, double gamma_source, double mu, double c)
{
    return gamma_source * exp(-mu * x / c);
}

int main()
{
    for(InitialConditions ic: test_cases) {
        // Discretized domain
        vector<double> x(ic.N + 1);
        vector<double> p(ic.N + 1); // pollutant concentration
        vector<double> s(ic.N + 1); // oxygen concentration

        double dx = ic.x_max / ic.N;

        // Initialize x and p
        for (int i = 0; i <= ic.N; ++i)
        {
            x[i] = i * dx;
            p[i] = pollutant_concentration(x[i], ic.gamma_source, ic.mu, ic.c);
        }

        // Initialize oxygen concentration
        s[0] = ic.s_max; // boundary condition at x = 0

        // Forward Euler method to solve for s(x)
        for (int i = 0; i < ic.N; ++i)
        {
            double ds_dx = (-ic.mu * p[i] + ic.mu1 * (ic.s_max - s[i])) / ic.c;
            s[i + 1] = s[i] + ds_dx * dx;
        }

        // Output results to a CSV file
        string fname = "river_simulation" + to_string(ic.idx) + ".csv";
        ofstream outfile(fname);
        outfile << "x,pollutant_concentration,oxygen_concentration\n";
        for (int i = 0; i <= ic.N; ++i)
        {
            outfile << x[i] << "," << p[i] << "," << s[i] << "\n";
        }
        outfile.close();
        cout << "Simulation complete. Results saved to" + fname + ".\n";
    }
        return 0;
}
