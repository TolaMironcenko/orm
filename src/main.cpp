#include <iostream>
#include "Orm/SqliteDatabase.hpp"
#include <string>

int main() {
    Orm::SqliteDatabase conn("database.sqlite3");
    // const char* names[] = {"id", "name", "email"};
    // const char* types[] = {"integer primary key autoincrement", "text", "char(50) unique"};
    // conn.create_table("User", 3, names, types);
    conn.drop_table("User");
    return 0;
}