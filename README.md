# River-Pollution-Simulation
## 1. **Differential Equations for Pollution in Rivers**

There are two main variables:
- \( $p(x,t)$ \) = pollutant concentration
- \( $s(x,t)$ \) = dissolved oxygen concentration

The behavior is modeled by these **coupled PDEs**:

### Pollutant Transport

$\frac{\partial p}{\partial t} + c \frac{\partial p}{\partial x} = -\mu p$

- \( $c$ \) = constant downstream river velocity
- \( $\mu$ \) = decay rate of pollutant due to bacteria
- Initial condition: river clean before \( $t=0$ \): \( $p(x,0) = 0$ \)
- Boundary condition at the source \( $x=0$ \): \( $p(0,t) = \gamma U(t)$ \)
  - where \( $\gamma$ \) is the dumping rate and \( $U(t)$ \) is the unit step function.

### Dissolved Oxygen Transport

$\frac{\partial s}{\partial t} + c \frac{\partial s}{\partial x} = -\mu p + \mu_1 (s_m - s)$

- \( $\mu_1$ \) = re-oxygenation rate from atmosphere
- \( $s_m$ \) = maximum oxygen saturation concentration
- Initial condition: river is fully oxygenated upstream: \( $s(0,t) = s_m$ \)

---

## 2. **Simplifications for Simulation**

We can assume a steady-state after a long time (so \($\partial p/\partial t = 0$\), \($\partial s/\partial t = 0$\)), leading to:

### Steady-State ODEs
Pollutant:

$c \frac{dp}{dx} = -\mu p
\quad\Rightarrow\quad
\frac{dp}{dx} = -\frac{\mu}{c} p
\quad\Rightarrow\quad
p(x) = \gamma e^{-\frac{\mu}{c}x}$


Dissolved Oxygen:

$c \frac{ds}{dx} = -\mu p + \mu_1 (s_m - s)$

Substituting \( $p(x)$ \) from above:

$c \frac{ds}{dx} + \mu_1 s = \mu_1 s_m - \mu \gamma e^{-\frac{\mu}{c}x}$


This is a **linear ODE** for \( $s(x)$ \).


### **Solve for Pollutant Concentration \( $p(x)$ \)**

Recall the steady-state pollutant equation: $c \frac{dp}{dx} = -\mu p$

#### Step-by-step:

- Rearrange: $\frac{dp}{dx} = -\frac{\mu}{c} p$

This is a **first-order linear ODE**.

- Separate variables: $\frac{dp}{p} = -\frac{\mu}{c} dx$


- Integrate both sides: $\int \frac{dp}{p} = -\frac{\mu}{c} \int dx \implies \ln |p| = -\frac{\mu}{c}x + C_1$

- Exponentiate: $p(x) = A e^{-\frac{\mu}{c}x}$ where \( $A = e^{C_1}$ \) is a constant.

- Apply boundary condition:  
At \( $x = 0$ \), the source strength is \( $p(0) = \gamma$ \).
Thus:

$p(0) = A = \gamma$


Final pollutant solution:

$\boxed{p(x) = \gamma e^{-\frac{\mu}{c}x}}$

---

# 2. ✅ Solve for Oxygen Concentration \( $s(x)$ \)

Now the oxygen steady-state equation is:

$c \frac{ds}{dx} = -\mu p + \mu_1 (s_m - s)$


Substitute \( $p(x) = \gamma e^{-\frac{\mu}{c}x}$ \):

$c \frac{ds}{dx} = -\mu \gamma e^{-\frac{\mu}{c}x} + \mu_1 (s_m - s)$


Rearrange:

$\frac{ds}{dx} + \frac{\mu_1}{c} s = \frac{\mu_1 s_m}{c} - \frac{\mu \gamma}{c} e^{-\frac{\mu}{c}x}$


### Step-by-step:

This is a **linear first-order ODE** of the form:

$\frac{ds}{dx} + P(x) s = Q(x)$

where:
- \( $P(x) = \frac{\mu_1}{c}$ \) (constant)
- \( $Q(x) = \frac{\mu_1 s_m}{c} - \frac{\mu \gamma}{c} e^{-\frac{\mu}{c}x}$ \)

#### Use Integrating Factor (IF):
The integrating factor is:

$\text{IF}(x) = e^{\int P(x) dx} = e^{\frac{\mu_1}{c} x}$


Multiply the ODE by the integrating factor:

$e^{\frac{\mu_1}{c}x} \frac{ds}{dx} + \frac{\mu_1}{c} e^{\frac{\mu_1}{c}x} s = e^{\frac{\mu_1}{c}x} \left( \frac{\mu_1 s_m}{c} - \frac{\mu \gamma}{c} e^{-\frac{\mu}{c}x} \right)$


Left-hand side becomes:

$\frac{d}{dx} \left( e^{\frac{\mu_1}{c}x} s \right)$


Thus:

$\frac{d}{dx} \left( e^{\frac{\mu_1}{c}x} s \right) = e^{\frac{\mu_1}{c}x} \frac{\mu_1 s_m}{c} - \frac{\mu \gamma}{c} e^{\left( \frac{\mu_1 - \mu}{c} \right)x}$


Now integrate both sides:

First term:

$\int e^{\frac{\mu_1}{c}x} \frac{\mu_1 s_m}{c} dx = \frac{\mu_1 s_m}{c} \times \frac{c}{\mu_1} e^{\frac{\mu_1}{c}x} = s_m e^{\frac{\mu_1}{c}x}$


Second term:

$\int \frac{\mu \gamma}{c} e^{\left( \frac{\mu_1 - \mu}{c} \right)x} dx = \frac{\mu \gamma}{c} \times \frac{c}{\mu_1 - \mu} e^{\left( \frac{\mu_1 - \mu}{c} \right)x} = \frac{\mu \gamma}{\mu_1 - \mu} e^{\left( \frac{\mu_1 - \mu}{c} \right)x}$


Thus:


$e^{\frac{\mu_1}{c}x} s(x) = s_m e^{\frac{\mu_1}{c}x} - \frac{\mu \gamma}{\mu_1 - \mu} e^{\left( \frac{\mu_1 - \mu}{c} \right)x} + C$


where \( $C$ \) is a constant of integration.

---

### Solve for \( $s(x)$ \):
Divide by \( e$^{\frac{\mu_1}{c}x}$ \):

$s(x) = s_m - \frac{\mu \gamma}{\mu_1 - \mu} e^{-\frac{\mu}{c}x} + C e^{-\frac{\mu_1}{c}x}$


---

### Find Constant \( $C$ \)

Use boundary condition:
- At \( $x = 0$ \), \( $s(0) = s_m$ \).

Substitute:

$s(0) = s_m - \frac{\mu \gamma}{\mu_1 - \mu} + C = s_m$


Thus:

$C = \frac{\mu \gamma}{\mu_1 - \mu}$

---

### Final Steady-State Solution for \( $s(x)$ \)

Thus:


$\boxed{
s(x) = s_m - \frac{\mu \gamma}{\mu_1 - \mu} \left( e^{-\frac{\mu}{c}x} - e^{-\frac{\mu_1}{c}x} \right)
}$

---

### **Summary of Final Solutions:**

- Pollutant concentration:

$\boxed{p(x) = \gamma e^{-\frac{\mu}{c}x}}$


- Dissolved oxygen concentration:

$\boxed{s(x) = s_m - \frac{\mu \gamma}{\mu_1 - \mu} \left( e^{-\frac{\mu}{c}x} - e^{-\frac{\mu_1}{c}x} \right)}$


---

**These are the exact analytic solutions for the steady-state pollutant and oxygen concentrations in the river.**  

**They match what we would also expect from the C++ simulation if we used very small \($\Delta x$\).**

---

## 3. **Plan for C++ Simulation**
- Discretize the river into small segments: \( $\Delta x$ \).
- March forward in space (Euler method or Runge-Kutta 4).
- Simulate \( $p(x)$ \) and \( $s(x)$ \) along the river length.

---

## 4. **Quick Sketch of C++ Simulation**
It will:
- Solve for \( $p(x)$ \) analytically
- Solve for \( $s(x)$ \) numerically using Forward Euler
