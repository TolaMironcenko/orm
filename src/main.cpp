#include <iostream>
#include "Orm/SqliteDatabase.hpp"
#include <string>
#include "Orm/lib/json.hpp"

int main()
{
    Orm::SqliteDatabase conn("database.sqlite3");
    const char *names[] = {"id", "name", "email"};
    const char *types[] = {"integer primary key autoincrement", "text", "char(50) unique"};
    conn.create_table("User", 3, names, types);
    const char *columns[] = {"id", "name", "email"};
    const char *values[] = {"1", "tola", "tolamironcenko@gmail.com"};
    conn.insert("User", 3, columns, values);
    // conn.delete_all("User");
    const char *columnss[] = {"id", "name"};
    const char *valuess[] = {"1", "tola"};
    nlohmann::json userdata = conn.select("User", 3, 2, columns, valuess, 0, nullptr);
    std::cout << userdata["email"] << "\n";
    // conn.drop_table("User");
    return 0;
}