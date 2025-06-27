#include "monte_carlo_pricer.hpp"
#include <random>  // For std::random_device, std::mt19937, std::normal_distribution
#include <cmath>   // For std::exp, std::sqrt, std::log
#include <numeric> // For std::accumulate

MonteCarloPricer::MonteCarloPricer(const Option &option, double spot, double rate, double vol,
                                   long num_simulations, bool useAntithetic)
    : m_option(option), m_spot(spot), m_rate(rate), m_vol(vol),
      m_num_simulations(num_simulations), m_useAntithetic(useAntithetic) {}

double MonteCarloPricer::price() const
{
    double T = m_option.getMaturity();

    // Calculate the risk-neutral drift and volatility adjustment once
    double drift = (m_rate - 0.5 * m_vol * m_vol) * T;
    double vol_sqrt_T = m_vol * std::sqrt(T);

    // Setup the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());                           // Mersenne Twister engine seeded with a random device
    std::normal_distribution<> normal_dist(0.0, 1.0); // Standard normal distribution

    double sum_payoffs = 0.0;

    if (m_useAntithetic)
    {
        // Run half the number of simulations, but generate two paths each time
        for (long i = 0; i < m_num_simulations / 2; ++i)
        {
            double Z = normal_dist(gen); // Random number from N(0, 1)

            // Path 1
            double S_T1 = m_spot * std::exp(drift + vol_sqrt_T * Z);
            sum_payoffs += m_option.payoff(S_T1);

            // Path 2 (Antithetic)
            double S_T2 = m_spot * std::exp(drift + vol_sqrt_T * -Z);
            sum_payoffs += m_option.payoff(S_T2);
        }
    }
    else
    {
        // Standard Monte Carlo simulation
        for (long i = 0; i < m_num_simulations; ++i)
        {
            double Z = normal_dist(gen); // Random number from N(0, 1)
            double S_T = m_spot * std::exp(drift + vol_sqrt_T * Z);
            sum_payoffs += m_option.payoff(S_T);
        }
    }

    // Calculate the average payoff
    double average_payoff = sum_payoffs / m_num_simulations;

    // Discount the average payoff back to today
    return average_payoff * std::exp(-m_rate * T);
}
