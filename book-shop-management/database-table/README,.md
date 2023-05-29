# Start with Postgres SQL

## Create database Books_Management
```
$ sudo -u postgres psql
postgres=# CREATE DATABASE books_management;
```

## Connecting to the Books_Management Database
```
# list all databases
postgres=# \l
postgres=# \c books_management
>> You are now connected to database "analysis" as user "postgres".
```

## Creating a Table
```
postgres=# \i database-table/book.sql

books_management=# \i database-table/suppliers.sql 

books_management=# \i database-table/members.sql 

books_management=# \i database-table/employees.sql 

books_management=# \i database-table/purchases.sql

books_management=# \i database-table/sales.sql
```

## List all table in database
```
postgres=# \dt
```