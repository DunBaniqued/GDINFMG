#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        if (j == '0') exit(0);
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
