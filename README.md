# River-Pollution-Simulation
## 1. **Differential Equations for Pollution in Rivers**

There are two main variables:
- \( $p(x,t)$ \) = pollutant concentration
- \( $s(x,t)$ \) = dissolved oxygen concentration

The behavior is modeled by these **coupled PDEs**:

### Pollutant Transport
\[
$\frac{\partial p}{\partial t} + c \frac{\partial p}{\partial x} = -\mu p$
\]
- \( $c$ \) = constant downstream river velocity
- \( $\mu$ \) = decay rate of pollutant due to bacteria
- Initial condition: river clean before \( $t=0$ \): \( $p(x,0) = 0$ \)
- Boundary condition at the source \( $x=0$ \): \( $p(0,t) = \gamma U(t)$ \)
  - where \( $\gamma$ \) is the dumping rate and \( $U(t)$ \) is the unit step function.

### Dissolved Oxygen Transport
\[
$\frac{\partial s}{\partial t} + c \frac{\partial s}{\partial x} = -\mu p + \mu_1 (s_m - s)$
\]
- \( $\mu_1$ \) = re-oxygenation rate from atmosphere
- \( $s_m$ \) = maximum oxygen saturation concentration
- Initial condition: river is fully oxygenated upstream: \( $s(0,t) = s_m$ \)

---

## 2. **Simplifications for Simulation**

We can assume a steady-state after a long time (so \($\partial p/\partial t = 0$\), \($\partial s/\partial t = 0$\)), leading to:

### Steady-State ODEs
Pollutant:
\[
$c \frac{dp}{dx} = -\mu p
\quad\Rightarrow\quad
\frac{dp}{dx} = -\frac{\mu}{c} p
\quad\Rightarrow\quad
p(x) = \gamma e^{-\frac{\mu}{c}x}$
\]

Dissolved Oxygen:
\[
$c \frac{ds}{dx} = -\mu p + \mu_1 (s_m - s)$
\]
Substituting \( $p(x)$ \) from above:
\[
$c \frac{ds}{dx} + \mu_1 s = \mu_1 s_m - \mu \gamma e^{-\frac{\mu}{c}x}$
\]

This is a **linear ODE** for \( $s(x)$ \).

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
