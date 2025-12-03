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
std::vector<std::string> sColumnNames;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    if (reset == 0) {
        for (int i = 0; i < argc; i++) {
            table.push_back(azColName[i]);
            maxSize.push_back(0);
        }

        sColumnNames.clear();
        for (int i = 0; i < argc; i++) {
            sColumnNames.push_back(azColName[i]);
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
    std::cout << "\n";
}

void Reset() {
    reset = 0;
    table.clear();
    maxSize.clear();
}

using SqlValue = std::variant<int, double, std::string>;

void insertRow(sqlite3* database, std::string table, std::vector<std::string> values) {
    int i = 0;
    char* errMsg = 0;
    std::string update = "INSERT INTO " + table + " VALUES (";


    for (i = 0; i < values.size(); i++) {
        update += + " " + values[i] + ",";
    }
    if (!update.empty()) update.pop_back();
    update += ");";

    //SQL query checking
    //std::cout << update << "\n";

    const char* sql = update.c_str();

    if (sqlite3_exec(database, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
    }
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

void CreationEntity(sqlite3* database, std::string name) {
    char* errMsg = 0;
    std::string j;
    std::vector<std::string> values;
    int i;

    std::string sqlQuery = readSqlFile("Tables/" + name + ".sql");
    const char* query = sqlQuery.c_str();

    if (sqlite3_exec(database, query, callback, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << name << "\n\n";
        printTable();
        Reset();
    }

    for (i = 0; i < column; i++) {
        std::cout << sColumnNames[i] << " : ";
        std::cin >> j;
        values.push_back(j);
    }

    system("CLS");
    insertRow(database, "Salaries", values);

    if (sqlite3_exec(database, query, callback, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << name << "\n\n";
        printTable();
        Reset();
    }
}
void DeletionEntity() {}
void TeamRegistration(sqlite3* database) {
    CreationEntity(database, "Team");
}
void PlayerRegistration(sqlite3* database) {
    CreationEntity(database, "Player");
}
void MatchRegistration(sqlite3* database) {
    CreationEntity(database, "Match");
}
void MatchDataUpdates() {}

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
    std::string j, organizer;

    std::cout << "User Type:" << "\n\n";
    std::cout << "1) Organizer" << "\n";
    std::cout << "2) Player/Team" << "\n";
    std::cout << "0) Exit" << "\n\n";
    std::cout << "Number: ";
    std::cin >> organizer;
    if (organizer == "0") exit(0);

    system("CLS");

    do {
        i = 1, j = "0";

        if (organizer == "1") {
            std::cout << "\n";
            std::cout << "Organizer Priveleges" << "\n\n";
            std::cout << "1) Creation of entity" << "\n";
            std::cout << "2) Deletion of entity" << "\n";
            std::cout << "3) Team Registration" << "\n";
            std::cout << "4) Player Registration" << "\n";
            std::cout << "5) Match Registration" << "\n";
            std::cout << "6) Match Data Updates" << "\n";
            i = 7;
        }
        
        std::cout << "\n" << "Reports View" << "\n\n";

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
        if (j == "0") break;

        system("CLS");

        if (organizer == "1") i = 7;
        else i = 1;

        if (std::stoi(j) >= i) {
            try {
                // Iterate over the entries in the specified directory
                for (const auto& entry : fs::directory_iterator(folderPath)) {
                    // Check if the entry is a regular file
                    if (fs::is_regular_file(entry.path())) {
                        if (i == std::stoi(j)) {
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
                                Reset();
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
        }
        else {
            switch (std::stoi(j))
            {
            case 1: 
                std::cout << "Table Name : ";
                std::cin >> j;
                CreationEntity(database, j);
                    break;
            case 2: DeletionEntity();
                    break;
            case 3: TeamRegistration(database);
                    break;
            case 4: PlayerRegistration(database);
                    break;
            case 5: MatchRegistration(database);
                    break;
            case 6: MatchDataUpdates();
                    break;
            default:
                break;
            }
        }

    } while (j != "0");


    sqlite3_close(database);
    return 0;
}
