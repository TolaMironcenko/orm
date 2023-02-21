#include "SqliteDatabase.hpp"

namespace Orm
{
    SqliteDatabase::SqliteDatabase()
    {
        this->db = nullptr;
    }

    SqliteDatabase::SqliteDatabase(const char *database_url)
    {
        this->db = this->open_database(database_url, this->db);
    }

    SqliteDatabase::~SqliteDatabase()
    {
        delete (this->db);
    }

    sqlite3 *SqliteDatabase::open_database(const char *url, sqlite3 *db)
    {
        int rc = sqlite3_open(url, &db);

        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        }
        else
        {
            //        fprintf(stderr, "Opened database successfully\n");
            return db;
        }
        return nullptr;
    }

    int SqliteDatabase::create_table(const char *table_name, int colnums, const char *column_names[], const char *column_types[])
    {
        std::stringstream sql;
        sql << "create table if not exists " << table_name << "(";
        for (int i = 0; i < colnums; i++)
        {
            sql << column_names[i] << " " << column_types[i];
            if (i != colnums - 1)
            {
                sql << ",";
            }
        }
        sql << ");";
        return this->execute(sql.str().c_str());
    }

    int SqliteDatabase::drop_table(const char *table_name)
    {
        std::stringstream sql;
        sql << "drop table if exists " << table_name << ";";
        return this->execute(sql.str().c_str());
    }

    int SqliteDatabase::execute(const char *sql)
    {
        char *zErrMsg = nullptr;
        int rc = sqlite3_exec(this->db, sql, nullptr, nullptr, &zErrMsg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 1;
        }
        return 0;
    }

    void SqliteDatabase::connect(const char *database_url)
    {
        this->db = this->open_database(database_url, this->db);
    }

    int SqliteDatabase::delete_all(const char *table_name)
    {
        std::stringstream sql;
        sql << "delete from " << table_name << ";";
        return this->execute(sql.str().c_str());
    }

    int SqliteDatabase::insert(const char *table_name, int columns, const char *column_names[], const char *values[])
    {
        std::stringstream sql;
        sql << "insert into " << table_name << " (";
        for (int i = 0; i < columns; i++)
        {
            sql << "'" << column_names[i] << "'";
            if (i != columns - 1)
            {
                sql << ",";
            }
        }
        sql << ") values (";
        for (int i = 0; i < columns; i++)
        {
            sql << "'" << values[i] << "'";
            if (i != columns - 1)
            {
                sql << ",";
            }
        }
        sql << ");";
        return this->execute(sql.str().c_str());
    }

    std::string select_columns_from_database(int select_nums, const char *select_columns[])
    {
        if (select_columns == nullptr)
        {
            return "*";
        }
        std::string columns = "";
        for (int i = 0; i < select_nums; i++)
        {
            columns += select_columns[i];
            if (i != select_nums - 1)
            {
                columns += ",";
            }
        }
        return columns;
    }

    nlohmann::json SqliteDatabase::select(const char *table_name, int columns_num, int nums, const char *column_names[], const char *values[], int select_nums, const char *select_columns[])
    {
        nlohmann::json result;
        sqlite3_stmt *query;
        std::stringstream sql;
        char *zErrMsg = nullptr;
        sql << "select " << select_columns_from_database(select_nums, select_columns) << " from " << table_name << " where ";
        for (int i = 0; i < nums; i++)
        {
            sql << column_names[i] << "='" << values[i] << "'";
            if (i != nums - 1)
            {
                sql << " and ";
            }
        }
        sql << ";";
        // std::cout << sql.str() << '\n';

        int rc = sqlite3_prepare_v2(this->db, sql.str().c_str(), -1, &query, nullptr);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            int iterator = 0;
            while ((rc = sqlite3_step(query) == SQLITE_ROW))
            {
                nlohmann::json::object_t::value_type();
                for (int j = 0; j < columns_num; j++)
                {
                    result += nlohmann::json::object_t::value_type{std::string(column_names[j]), (const char *)sqlite3_column_text(query, j)};
                    // std::cout << "result = " << result << "\n";
                }
                iterator++;
            }
            // std::cout << "result = " << result << "\n";
        }
        return result;
    }
}
