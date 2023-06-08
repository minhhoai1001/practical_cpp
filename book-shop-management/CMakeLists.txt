cmake_minimum_required(VERSION 3.10)

project(books_management)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

# include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(books_management
    src/main.cpp
    src/books.cpp
    src/suppliers.cpp
    src/purchases.cpp
    src/employees.cpp
    src/members.cpp
    src/sales.cpp
)

target_link_libraries(books_management ${PQXX_LIB} ${PQ_LIB})