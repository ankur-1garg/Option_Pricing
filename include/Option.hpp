// include/option.hpp
#pragma once

#include <string>

// Enum to define the type of option
enum class OptionType {
    Call,
    Put
};

class Option {
public:
    // Constructor: Initializes option properties
    Option(double strike, double maturity, OptionType type)
        : m_strike(strike), m_maturity(maturity), m_type(type) {}

    // Virtual destructor: essential for base classes
    virtual ~Option() = default;

    // Public getter methods
    double getStrike() const { return m_strike; }
    double getMaturity() const { return m_maturity; }
    OptionType getType() const { return m_type; }

    // Pure virtual function for calculating payoff.
    // This makes Option an abstract class. Derived classes MUST implement this.
    virtual double payoff(double spotPrice) const = 0;

protected:
    double m_strike;   // K
    double m_maturity; // T (in years)
    OptionType m_type;
};