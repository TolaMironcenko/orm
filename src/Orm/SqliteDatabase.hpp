#ifndef ORM_SQLITE_DATABASE_HPP
#define ORM_SQLITE_DATABASE_HPP

#include <sqlite3.h>
#include <iostream>

namespace Orm
{
    class SqliteDatabase
    {
    private:
        sqlite3 *db = nullptr;

    public:
        SqliteDatabase();
        SqliteDatabase(const char *database_url);
        ~SqliteDatabase();

        int create_table(const char *table_name, int colnums, const char* column_names[], const char* column_types[]);
        int drop_table(const char *table_name);

        int execute(const char *sql);

        sqlite3 *open_database(const char *url, sqlite3 *db);
    };
}

#endif // ORM_SQLITE_DATABASE_HPP