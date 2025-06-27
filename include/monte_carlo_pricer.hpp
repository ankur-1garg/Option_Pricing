#pragma once

#include "Option.hpp" // Use the base class to be generic

class MonteCarloPricer {
public:
    // Constructor: Takes option, market data, and simulation parameters
    MonteCarloPricer(const Option& option, double spot, double rate, double vol, 
                     long num_simulations, bool useAntithetic = true);

    // Main pricing function
    double price() const;

private:
    const Option& m_option;
    double m_spot;
    double m_rate;
    double m_vol;
    long m_num_simulations;
    bool m_useAntithetic;
};
