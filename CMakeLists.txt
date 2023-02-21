cmake_minimum_required(VERSION 3.16)
project(Orm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(./src/Orm/)

find_package(SQLite3 REQUIRED)

add_executable(orm src/main.cpp src/Orm/SqliteDatabase.cpp)
target_link_libraries(orm sqlite3)