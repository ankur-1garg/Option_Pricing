#include <iostream>
#include <iomanip>
#include <string>
#include <limits> 

#include "european_option.hpp"
#include "american_option.hpp"
#include "black_scholes_pricer.hpp"
#include "binomial_pricer.hpp"
#include "monte_carlo_pricer.hpp"

// Helper function to get validated user input
double get_double_input(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good() && value > 0) {
            // Clear the rest of the line in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter a positive number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::cout << "--- C++ Option Pricing Engine ---" << std::endl;
    std::cout << "=================================" << std::endl;

    // --- Get User Inputs ---
    double spot = get_double_input("Enter Spot Price (e.g., 100): ");
    double strike = get_double_input("Enter Strike Price (e.g., 105): ");
    double rate = get_double_input("Enter Risk-Free Rate (e.g., 0.05 for 5%): ");
    double vol = get_double_input("Enter Volatility (e.g., 0.20 for 20%): ");
    double maturity = get_double_input("Enter Maturity in years (e.g., 1.0): ");
    
    // Hardcoded parameters for numerical methods
    int binomial_steps = 200;
    long mc_simulations = 100000;

    std::cout << "\n--- Calculating Prices... ---" << std::endl;
    std::cout << std::fixed << std::setprecision(5);

    // --- Create Options ---
    EuropeanOption euroCall(strike, maturity, OptionType::Call);
    EuropeanOption euroPut(strike, maturity, OptionType::Put);
    AmericanOption americanPut(strike, maturity, OptionType::Put);

    // --- European Call Pricing ---
    std::cout << "\n--- European Call Option ---" << std::endl;
    BlackScholesPricer bs_pricer(euroCall, spot, rate, vol);
    std::cout << "Black-Scholes Price: " << bs_pricer.price() << std::endl;
    
    BinomialPricer tree_pricer_ec(euroCall, spot, rate, vol, binomial_steps);
    std::cout << "Binomial Tree Price: " << tree_pricer_ec.price() << " (" << binomial_steps << " steps)" << std::endl;

    MonteCarloPricer mc_pricer_ec(euroCall, spot, rate, vol, mc_simulations);
    std::cout << "Monte Carlo Price:   " << mc_pricer_ec.price() << " (" << mc_simulations << " sims)" << std::endl;

    // --- European Put Pricing ---
    std::cout << "\n--- European Put Option ---" << std::endl;
    BlackScholesPricer bs_pricer_put(euroPut, spot, rate, vol);
    std::cout << "Black-Scholes Price: " << bs_pricer_put.price() << std::endl;

    BinomialPricer tree_pricer_ep(euroPut, spot, rate, vol, binomial_steps);
    std::cout << "Binomial Tree Price: " << tree_pricer_ep.price() << " (" << binomial_steps << " steps)" << std::endl;

    // --- American Put Pricing (where it differs) ---
    std::cout << "\n--- American Put Option (Early Exercise) ---" << std::endl;
    BinomialPricer tree_pricer_ap(americanPut, spot, rate, vol, binomial_steps);
    std::cout << "Binomial Tree Price: " << tree_pricer_ap.price() << " (" << binomial_steps << " steps)" << std::endl;

    // --- Greeks Calculation (for the European Call) ---
    std::cout << "\n--- Greeks for European Call (Black-Scholes) ---" << std::endl;
    Greeks greeks = bs_pricer.calculateGreeks();
    std::cout << "Delta: " << greeks.delta << std::endl;
    std::cout << "Gamma: " << greeks.gamma << std::endl;
    std::cout << "Vega : " << greeks.vega << " (per 1% vol)" << std::endl;
    std::cout << "Theta: " << greeks.theta << " (per day)" << std::endl;
    std::cout << "Rho  : " << greeks.rho << " (per 1% rate)" << std::endl;

    return 0;
}