#include "../include/DatabaseHandler.h"
#include <iostream>

int main() {
    // 初始化資料庫處理物件
    DatabaseHandler db("10.188.200.16", "5432", "jimmy", "123123", "tw");

    // 取得查詢結果
    auto data = db.fetchData("SELECT * from price limit 100;");

    // 顯示結果
    for (const auto& entry : data) {
        std::cout << "Code: " << entry.first << std::endl;
        for (const auto& price_entry : entry.second) {
            std::cout << "Date: " << price_entry.first << ", Close Price: " << price_entry.second << std::endl;
        }
    }

    return 0;
}
