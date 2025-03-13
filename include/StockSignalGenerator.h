#ifndef STOCKSIGNALGENERATOR_H
#define STOCKSIGNALGENERATOR_H

#include<vector>
#include<map>
#include<string>
#include<algorithm>

class StockSignalGenerator {
public:
    StockSignalGenerator(const std::vector<double>& close_prices);

    std::vector<int> getSignal(int signal_threshold = 2);

private:
    std::vector<double> close_prices;
    std::map<std::string, int> signal_dict;

    double calculateMovingAverage(int period);
    double calculatePctChange(int index);
    double calculatePower(int index);
    
    // params
    const int tajm = 242;
    const double alpha = 2.0 / (tajm + 1);
    const double dip_range = -0.1;
    const int extreme_last_for_days = 40;
    const int signal_last_for_days = 25;
};

#endif