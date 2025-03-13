#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <map>


class DatabaseHandler {
public:
    DatabaseHandler(const std::string& host, const std::string& port,
                    const std::string& user, const std::string& password,
                    const std::string& dbname);
    ~DatabaseHandler();

    std::map<std::string, std::vector<str::pair<std::string, double>>> fetchData(string sqlStr);

private:
    std::string connection_str;
};