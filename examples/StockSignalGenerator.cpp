#include <iostream>
#include "../include/StockSignalGenerator.h"

int main() {
    // 假設這是我們的股市數據（收盤價）
    std::vector<double> close_prices = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};

    // 初始化 StockSignalGenerator 類
    StockSignalGenerator signal_generator(close_prices);

    // 獲取信號
    std::vector<int> signals = signal_generator.getSignal();

    // 輸出信號
    for (int signal : signals) {
        std::cout << signal << std::endl;
    }

    return 0;
}
