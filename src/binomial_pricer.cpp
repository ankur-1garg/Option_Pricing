#include "binomial_pricer.hpp"
#include "american_option.hpp" // Needed for dynamic_cast to check for American options
#include <vector>
#include <cmath>

BinomialPricer::BinomialPricer(const Option &option, double spot, double rate, double vol, int steps)
    : m_option(option), m_spot(spot), m_rate(rate), m_vol(vol), m_steps(steps) {}

double BinomialPricer::price() const
{
    // 1. Calculate tree parameters
    double dt = m_option.getMaturity() / m_steps;
    double u = std::exp(m_vol * std::sqrt(dt));       // Up-factor
    double d = 1.0 / u;                               // Down-factor
    double p = (std::exp(m_rate * dt) - d) / (u - d); // Risk-neutral probability

    // 2. Initialize option values at maturity (the last column of the tree)
    std::vector<double> values(m_steps + 1);
    for (int i = 0; i <= m_steps; ++i)
    {
        double spot_at_maturity = m_spot * std::pow(u, m_steps - i) * std::pow(d, i);
        values[i] = m_option.payoff(spot_at_maturity);
    }

    // 3. Step backward through the tree
    for (int step = m_steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
        {
            // Calculate discounted expected value (hold value)
            double hold_value = (p * values[i] + (1 - p) * values[i + 1]) * std::exp(-m_rate * dt);

            // For American options, check for early exercise
            // We use dynamic_cast to see if the option is American.
            if (dynamic_cast<const AmericanOption *>(&m_option))
            {
                double spot_at_node = m_spot * std::pow(u, step - i) * std::pow(d, i);
                double exercise_value = m_option.payoff(spot_at_node);
                values[i] = std::max(hold_value, exercise_value);
            }
            else
            {
                // For European options, value is just the hold value
                values[i] = hold_value;
            }
        }
    }

    // The price is the value at the root of the tree
    return values[0];
}
