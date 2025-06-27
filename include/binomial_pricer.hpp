#pragma once

#include "Option.hpp" // Use the base class to be generic

class BinomialPricer
{
public:
    // Constructor: Takes a generic option and model parameters
    BinomialPricer(const Option &option, double spot, double rate, double vol, int steps);

    // Main pricing function
    double price() const;

private:
    const Option &m_option;
    double m_spot;
    double m_rate;
    double m_vol;
    int m_steps;
};
