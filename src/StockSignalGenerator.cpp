#include "../include/StockSignalGenerator.h"
#include <iostream>
#include <cmath> // for std::pow


StockSignalGenerator::StockSignalGenerator(const std::vector<double>& close_prices)
    : close_prices(close_prices) {}


std::vector<int> StockSignalGenerator::getSignal(int signal_threshold) {
    int signal = 1;
    int short_signal = 0;
    int extreme_counter = extreme_last_for_days + 1;
    int signal_counter = signal_last_for_days + 1;
    int current_number_of_signal = 0;
    
    std::vector<int> signals(close_prices.size(), 0);
    
    for (std::vector<double>::size_type index = tajm; index < close_prices.size(); ++index) {
        // Calculate moving averages
        double ma10 = calculateMovingAverage(10);
        double ma5 = calculateMovingAverage(5);

        double pct = calculatePctChange(index);
        double power = std::pow(pct, 5);
        double power_ema = power * alpha;
        double power_ema_shift1 = (index > 0) ? power_ema : 0;
        
        double diff_5d = 0;
        for (size_t i = index - 5; i < static_cast<size_t>(index); ++i) {
            diff_5d += calculatePctChange(i);
        }
            
        if (extreme_counter < extreme_last_for_days) {
            extreme_counter++;
            signals[index] = signal;
            continue;
        }

        // Buy the dip
        if (diff_5d < dip_range) {
            signal = 1;
            extreme_counter = 0;
            signals[index] = signal;
            continue;
        }

        if (signal_counter < signal_last_for_days) {
            signal_counter++;
            signals[index] = short_signal;
            continue;
        }

        // Signal generation logic
        if (current_number_of_signal >= signal_threshold) {
            signal = short_signal;
            signal_counter = 0;
        } else {
            signal = 1;
            current_number_of_signal++;
        }
        
        signals[index] = signal;
    }

    return signals;
}


double StockSignalGenerator::calculateMovingAverage(int period) {
    double sum = 0.0;
    for (int i = 0; i < period; ++i) {
        sum += close_prices[i];
    }
    return sum / period;
}


double StockSignalGenerator::calculatePctChange(int index) {
    if (index == 0) return 0;
    return (close_prices[index] - close_prices[index - 1]) / close_prices[index - 1];
}


double StockSignalGenerator::calculatePower(int index) {
    return std::pow(calculatePctChange(index), 5);
}
