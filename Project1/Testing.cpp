#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <filesystem>

namespace fs = std::filesystem;

int reset = 0;
int column = 0;
std::vector<int> maxSize;

std::vector<std::string> table;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    if (reset == 0) {
        for (int i = 0; i < argc; i++) {
            table.push_back(azColName[i]);
            maxSize.push_back(0);
        }
        reset++;
        column = argc;
    }

    for (int i = 0; i < argc; i++) {
        table.push_back((argv[i] ? argv[i] : "NULL"));
    }

    return 0;
}

static void printTable() {
    int i = 0, j = 0, k = 0;

    for (std::string row : table) {
        if (row.size() > maxSize.at(i)) maxSize.at(i) = row.size();

        i++;
        if (i >= maxSize.size()) i = 0;
    }
    for (std::string row : table) {
        std::cout << std::left << std::setw(maxSize.at(i)) << row << " | ";

        if (j == 0) k += maxSize.at(i);

        i++;
        if (i >= maxSize.size()) {

            if (j == 0) {
                std::string s(k + i*3 - 1, '-');
                std::cout << '\n'<< s;
                j++;
            }

            i = 0;
            std::cout << "\n";
        }
    }

    reset = 0;
    column = 0;
    table.clear();
    maxSize.clear();
    std::cout << "\n";
}

std::vector<std::string> sColumnNames;
int columnsReset = 0;
static int columnNames(void* NotUsed, int argc, char** argv, char** azColName) {
    
    if (columnsReset != 0) return 0;

    sColumnNames.clear();
    for (int i = 0; i < argc; i++) {
        sColumnNames.push_back(azColName[i]);
    }

    columnsReset++;
    return 0;
}

using SqlValue = std::variant<int, double, std::string>;

void bindValue(sqlite3_stmt* stmt, int index, const SqlValue& value) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        int rc = SQLITE_OK;
        if constexpr (std::is_same_v<T, int>) {
            rc = sqlite3_bind_int(stmt, index, arg);
        }
        else if constexpr (std::is_same_v<T, double>) {
            rc = sqlite3_bind_double(stmt, index, arg);
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            rc = sqlite3_bind_text(stmt, index, arg.c_str(), -1, SQLITE_TRANSIENT);
        }
        if (rc != SQLITE_OK) {
            std::cerr << "Bind error: " << sqlite3_errmsg(sqlite3_db_handle(stmt)) << "\n";
        }
        }, value);

}

void updateRow(sqlite3* database, std::string table, std::vector<std::string> column, std::vector<std::string> values) {
    int i = 0;
    char* errMsg = 0;
    std::string update = "UPDATE " + table + " SET";


    for (i = 1; i < values.size(); i++) {
        update += " " + column[i] + " = " + values[i] + ",";
    }
    if (!update.empty()) update.pop_back();
    update += " where " + column[0] + " = " + values[0] + ";";

    //SQL query checking
    //std::cout << update << "\n";

    const char* sql = update.c_str();

    if (sqlite3_exec(database, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        printTable();
    }
}

void deleteRow(sqlite3* database, std::string table, std::vector<std::string> column, int id) {
    char* errMsg = 0;
    std::string dlt = "DELETE From " + table
                    + " where " + column[0] + " = " + std::to_string(id);

    const char* sql = dlt.c_str();

    //SQL query checking
    //std::cout << dlt << "\n";

    if (sqlite3_exec(database, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        printTable();
    }
}

static std::string readSqlFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();
    return content;
}

int main() {
    sqlite3* database;
    char* errMsg = 0;

    if (sqlite3_open("Database/yes.db", &database)) {
        std::cerr << "Can't open DB: " << sqlite3_errmsg(database) << "\n";
        return 1;
    }

    std::cout << "WELCOME" << "\n\n";

    std::string folderPath = "Reports";
    int i = 1;
    char j = 0;

    do {
        i = 1, j = 0;

        std::cout << "What would you like to do?" << "\n\n";

        try {
            // Iterate over the entries in the specified directory
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                // Check if the entry is a regular file
                if (fs::is_regular_file(entry.path())) {
                    std::string reportName = entry.path().filename().string();
                    for (int i = 0; i < reportName.size(); ++i) {
                        if (reportName[i] == '_')
                            reportName[i] = ' ';
                        if (reportName[i] == '.')
                            reportName.erase(i);
                    }

                    std::cout << i << ") " << reportName << " Report" << "\n";
                    i++;
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }

        std::cout << "0) Exit" << "\n\n";
        std::cout << "Number: ";
        std::cin >> j;
        if (j == '0') break;
        std::cout << '\n';

        system("CLS");

        i = 1;
        try {
            // Iterate over the entries in the specified directory
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                // Check if the entry is a regular file
                if (fs::is_regular_file(entry.path())) {
                    if (i == (int) j - 48) {
                        std::string reportName = entry.path().filename().string();
                        for (int i = 0; i < reportName.size(); ++i) {
                            if (reportName[i] == '_')
                                reportName[i] = ' ';
                            if (reportName[i] == '.')
                                reportName.erase(i);
                        }

                        std::cout << reportName << " Report" << "\n\n";
                        i++;

                        std::string sqlQuery = readSqlFile(entry.path().string());
                        const char* query = sqlQuery.c_str();

                        if (sqlite3_exec(database, query, callback, 0, &errMsg) != SQLITE_OK) {
                            std::cerr << "SQL error: " << errMsg << "\n";
                            sqlite3_free(errMsg);
                        }
                        else {
                            printTable();
                        }

                        break;
                    }
                    i++;
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }

    } while (j != '0');


    sqlite3_close(database);
    return 0;
}
