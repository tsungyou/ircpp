#include <iostream>
#include <pqxx/pqxx> // PostgreSQL C++ Library
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iomanip>

using namespace std;

int main() {
    // 连接到 PostgreSQL 数据库
    string pg_host = "10.188.200.16";
    string pg_port = "5432";
    string pg_user = "jimmy";
    string pg_passwd = "123123";
    string database = "tw";

    try {
        pqxx::connection C("dbname=" + database + " user=" + pg_user +
                           " password=" + pg_passwd + " host=" + pg_host +
                           " port=" + pg_port);
        if (C.is_open()) {
            cout << "Connected to " << database << " successfully!" << endl;
        } else {
            cerr << "Connection to database failed!" << endl;
            return 1;
        }

        pqxx::nontransaction N(C);

        // SQL 查询语句
        string sql = R"(
            SELECT * 
            FROM price 
            WHERE da >= '2017-01-01'
            and code IN (
                SELECT code 
                FROM maincode_etf 
                WHERE fund_abbr NOT LIKE '%正%' 
                AND target_area IN ('美國')
            ) order by da asc;
        )";

        pqxx::result R = N.exec(sql);

        // 数据存储
        map<string, vector<pair<string, double>>> data;

        // 遍历结果并处理数据
        for (auto row = R.begin(); row != R.end(); ++row) {
            string date = row[0].as<string>(); // da
            string code = row[1].as<string>(); // code
            double close = row[2].as<double>(); // cl

            data[code].push_back({date, close});
        }

        for (const auto &entry : data) {
            cout << "Code: " << entry.first << endl;
            for (const auto &price_entry : entry.second) {
                cout << "Date: " << price_entry.first << ", Close Price: " << price_entry.second << endl;
            }
        }

        // C.disconnect();
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
