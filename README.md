# C++ Option Pricing and Greeks Library

This project is a high-performance C++ library for pricing financial options and calculating their sensitivities (Greeks). It serves as a portfolio piece demonstrating skills in C++, object-oriented design, numerical methods, and quantitative finance.

## 🌟 Features

*   **Multiple Pricing Models**:
    *   **Black-Scholes**: Analytical closed-form solution for European options.
    *   **Binomial Tree**: Numerical method for both European and American options, capturing the early exercise premium.
    *   **Monte Carlo Simulation**: Flexible simulation-based method for European options, easily extendable to exotic options.
*   **Greeks Calculation**: Computes Delta, Gamma, Vega, Theta, and Rho using analytical Black-Scholes formulas.
*   **Object-Oriented Design**: Clean, modular structure using base classes (`Option`) and derived classes (`EuropeanOption`, `AmericanOption`) with separate pricer engines.
*   **Performance**: Optimized implementations, such as a space-efficient binomial tree and antithetic variate reduction for Monte Carlo.
*   **Build System**: Uses modern CMake for cross-platform compilation.

## 🏗️ Project Structure

```
/
├── include/              # Header files (.hpp) for all classes
├── src/                  # Source implementation files (.cpp)
├── tests/                # (Placeholder for unit tests)
├── CMakeLists.txt        # The build script for CMake
├── main.cpp              # An interactive command-line demo
└── README.md             # This file
```

## 🛠️ How to Build and Run

### Prerequisites

*   A C++17 compliant compiler (e.g., GCC, Clang, MSVC)
*   CMake (version 3.10 or higher)

### Build Steps

1.  **Clone the repository:**
    ```bash
    git clone 
    cd project
    ```

2.  **Configure the project with CMake:**
    This command creates a `build` directory and generates the build files (e.g., Makefiles).
    ```bash
    cmake -B build
    ```

3.  **Compile the code:**
    This command invokes the compiler to build the library and the demo executable.
    ```bash
    cmake --build build
    ```

### Running the Demo

The compiled executable will be located in the `build` directory.

```bash
./build/demo
```

The program will then prompt you to enter the parameters for the option you want to price:

```
--- C++ Option Pricing Engine ---
=================================
Enter Spot Price (e.g., 100): 100
Enter Strike Price (e.g., 105): 105
Enter Risk-Free Rate (e.g., 0.05 for 5%): 0.05
Enter Volatility (e.g., 0.20 for 20%): 0.2
Enter Maturity in years (e.g., 1.0): 1

--- Calculating Prices... ---
... (output follows) ...
```

## 🧠 Financial Theory Summary

*   **Black-Scholes Model**: Assumes the underlying asset follows a Geometric Brownian Motion with constant drift and volatility. It provides a precise, analytical formula for European options but cannot handle American-style early exercise.
*   **Binomial Tree Model**: A discrete-time model that approximates the continuous process of the asset price. Its primary advantage is the ability to correctly price American options by checking for optimal exercise at each node in the tree.
*   **Monte Carlo Simulation**: Estimates the option price by simulating thousands of random asset price paths and averaging the resulting option payoffs. While computationally intensive, it is extremely flexible and is the industry standard for pricing complex, path-dependent exotic options.
