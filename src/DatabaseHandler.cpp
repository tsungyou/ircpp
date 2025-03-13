#include "DatabaseHandler.h"
#include <iostream>
#include <stdexcept>

DatabaseHandler::DatabaseHandler(const std::string& host, const std::string& port, 
                                 const std::string& user, const std::string& password, 
                                 const std::string& dbname) {
    connection_str = "dbname=" + dbname + " user=" + user + 
                     " password=" + password + " host=" + host + 
                     " port=" + port;
}

DatabaseHandler::~DatabaseHandler() {}

std::map<std::string, std::vector<std::pair<std::string, double>>> DatabaseHandler::fetchData(string sqlStr) {
    std::map<std::string, std::vector<std::pair<std::string, double>>> data;

    try {
        pqxx::connection C(connection_str);
        if (!C.is_open()) {
            throw std::runtime_error("Failed to connect to database");
        }

        pqxx::nontransaction N(C);
        // std::string sql = R"(
        //     SELECT * 
        //     FROM price 
        //     WHERE da >= '2017-01-01'
        //     and code IN (
        //         SELECT code 
        //         FROM maincode_etf 
        //         WHERE fund_abbr NOT LIKE '%正%' 
        //         AND target_area IN ('美國')
        //     ) order by da asc;
        // )";

        pqxx::result R = N.exec(sqlStr);

        // push_back() 會先創建一個物件，然後再將它複製（或移動）到 vector 裡。
        // 適用於已經建立的物件。
        // std::vector<std::pair<std::string, double>> data;
        // std::pair<std::string, double> p("2024-03-13", 120.5);
        // data.push_back(p);  // 先創建 p，再複製到 vector
        // ====or====
        // data.push_back(std::make_pair("2024-03-13", 120.5));  // std::make_pair 建立物件

        
        for (auto row = R.begin(); row != R.end(); ++row) {
            std::string date = row[0].as<std::string>(); 
            std::string code = row[1].as<std::string>(); 
            double close = row[2].as<double>(); 

            data[code].emplace_back(date, close);
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return data;
}
