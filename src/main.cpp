#include <iostream>
#include "Orm/SqliteDatabase.hpp"
// #include <string>
#include "Orm/lib/json.hpp"

int main()
{
    Orm::SqliteDatabase conn("database.sqlite3");
    const char *names[] = {"id", "name", "email"};
    const char *types[] = {"integer primary key autoincrement", "text", "char(50) unique"};
    conn.create_table("User", 3, names, types);
    const char *columns[] = {"id", "name", "email"};
    const char *values[] = {"1", "tola", "tolamironcenko@gmail.com"};
    const char *values2[] = {"2", "tola", "mironcenkotola@gmail.com"};
    conn.insert("User", 3, columns, values);
    conn.insert("User", 3, columns, values2);
    // conn.delete_all("User");
    const char *columnss[] = {"id", "name"};
    const char *valuess[] = {"1", "tola"};
    // const char *select_columns[] = {"name"};
    nlohmann::json user_username = conn.select("User", 3, 2, columnss, valuess, 0, NULL, names);
    std::cout << user_username << "\n";
    // conn.delete_from("User", 2, columnss, valuess);
    // conn.drop_table("User");
    return 0;
}