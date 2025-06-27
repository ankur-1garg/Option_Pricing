// src/black_scholes_pricer.cpp
#include "black_scholes_pricer.hpp"
#include <cmath>     // For std::log, std::sqrt, std::exp, std::erf
#include <stdexcept> // For std::logic_error

BlackScholesPricer::BlackScholesPricer(const EuropeanOption &option, double spot, double rate, double vol)
    : m_option(option), m_spot(spot), m_rate(rate), m_vol(vol) {}

double BlackScholesPricer::price() const
{
    // Get option parameters
    double K = m_option.getStrike();
    double T = m_option.getMaturity();
    OptionType type = m_option.getType();

    // Get market data from the pricer
    double S = m_spot;
    double r = m_rate;
    double v = m_vol; // sigma is often denoted as 'v' for volatility

    // Check for zero maturity, as it can cause division by zero
    if (T <= 0)
    {
        return m_option.payoff(S);
    }

    // Calculate d1 and d2
    double d1 = (std::log(S / K) + (r + 0.5 * v * v) * T) / (v * std::sqrt(T));
    double d2 = d1 - v * std::sqrt(T);

    // Calculate price based on option type
    double optionPrice = 0.0;

    if (type == OptionType::Call)
    {
        optionPrice = S * N(d1) - K * std::exp(-r * T) * N(d2);
    }
    else
    { // OptionType::Put
        optionPrice = K * std::exp(-r * T) * N(-d2) - S * N(-d1);
    }

    return optionPrice;
}

Greeks BlackScholesPricer::calculateGreeks() const
{
    // Get option parameters
    double K = m_option.getStrike();
    double T = m_option.getMaturity();
    OptionType type = m_option.getType();

    // Get market data
    double S = m_spot;
    double r = m_rate;
    double v = m_vol;

    // Handle edge case of zero maturity
    if (T <= 0)
    {
        // At expiry, greeks are either 0 or behave erratically.
        // Returning all zeros is a reasonable simplification.
        return {0.0, 0.0, 0.0, 0.0, 0.0};
    }

    // Re-calculate d1 and d2 as they are central to all Greeks
    double d1 = (std::log(S / K) + (r + 0.5 * v * v) * T) / (v * std::sqrt(T));
    double d2 = d1 - v * std::sqrt(T);

    // Common term n(d1) used in multiple greeks
    double n_d1 = n(d1);

    // Create a struct to hold the results
    Greeks greeks;

    // --- Calculate each Greek ---

    // GAMMA: Same for Call and Put
    greeks.gamma = n_d1 / (S * v * std::sqrt(T));

    // VEGA: Same for Call and Put
    greeks.vega = S * n_d1 * std::sqrt(T) / 100; // Divide by 100 to get price change per 1% vol change

    if (type == OptionType::Call)
    {
        // DELTA
        greeks.delta = N(d1);
        // THETA (per day)
        greeks.theta = -(S * n_d1 * v) / (2 * std::sqrt(T)) - r * K * std::exp(-r * T) * N(d2);
        greeks.theta /= 365; // Convert from per year to per day
        // RHO
        greeks.rho = K * T * std::exp(-r * T) * N(d2) / 100; // Divide by 100 for price change per 1% rate change
    }
    else
    { // OptionType::Put
        // DELTA
        greeks.delta = N(d1) - 1.0;
        // THETA (per day)
        greeks.theta = -(S * n_d1 * v) / (2 * std::sqrt(T)) + r * K * std::exp(-r * T) * N(-d2);
        greeks.theta /= 365; // Convert from per year to per day
        // RHO
        greeks.rho = -K * T * std::exp(-r * T) * N(-d2) / 100; // Divide by 100 for price change per 1% rate change
    }

    return greeks;
}

double BlackScholesPricer::N(double x) const
{
    // To be implemented in Phase 2
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

// Implementation of the Normal PDF
double BlackScholesPricer::n(double x) const
{
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}