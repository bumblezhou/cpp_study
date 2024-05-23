#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    int rc = sqlite3_open("test_sqlite3.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    std::cout << "Open database successfully." << std::endl;

    // Create table 
    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS COMPANY("
                                "ID INT PRIMARY KEY     NOT NULL,"
                                "NAME           TEXT    NOT NULL,"
                                "AGE            INT     NOT NULL,"
                                "ADDRESS        CHAR(50),"
                                "SALARY         REAL );";
    char* err_msg = nullptr;
    rc = sqlite3_exec(db, create_table_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }
    std::cout << "Table created successfully" << std::endl;

    // Insert data
    const char* insert_sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
                             "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "
                             "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
                             "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "
                             "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
                             "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"
                             "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
                             "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    rc = sqlite3_exec(db, insert_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }
    std::cout << "Records created successfull" << std::endl;

     // Select data
    const char* select_sql = "SELECT * FROM COMPANY";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            int age = sqlite3_column_int(stmt, 2);
            const unsigned char* address = sqlite3_column_text(stmt, 3);
            double salary = sqlite3_column_double(stmt, 4);

            std::cout << "ID = " << id << std::endl;
            std::cout << "NAME = " << name << std::endl;
            std::cout << "AGE = " << age << std::endl;
            std::cout << "ADDRESS = " << address << std::endl;
            std::cout << "SALARY = " << salary << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    // Close database
    sqlite3_close(db);

    return 0;
}