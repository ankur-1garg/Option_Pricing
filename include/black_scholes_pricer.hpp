// include/black_scholes_pricer.hpp
#pragma once

#include "european_option.hpp"

// A struct to hold all the Greeks together
struct Greeks
{
    double delta;
    double gamma;
    double vega;
    double theta;
    double rho;
};

class BlackScholesPricer
{
public:
    // Constructor
    BlackScholesPricer(const EuropeanOption &option, double spot, double rate, double vol);

    // Pricing function
    double price() const;

    // Greeks calculation function
    Greeks calculateGreeks() const;

private:
    // Helper function for the cumulative distribution function (CDF) of a standard normal
    double N(double x) const;

    // Helper function for the probability density function (PDF) of a standard normal
    double n(double x) const;

    // Model parameters
    const EuropeanOption &m_option;
    double m_spot; // S
    double m_rate; // r
    double m_vol;  // sigma
};