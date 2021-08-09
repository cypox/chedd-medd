cmake_minimum_required (VERSION 3.0)

project (dbbackend)

add_compile_options(-std=c++17 -Wall -Wextra -Wsign-conversion)

find_package(Boost 1.70.0 COMPONENTS system thread REQUIRED)

add_executable(db_backend db_backend.cpp)
find_package(Boost 1.70.0 COMPONENTS system thread filesystem REQUIRED)
target_link_libraries(db_backend ${Boost_LIBRARIES} stdc++fs)
find_package(SQLite3 REQUIRED)
target_link_libraries(db_backend ${SQLite3_LIBRARIES})
target_include_directories(db_backend PRIVATE ${Boost_INCLUDE_DIR})
