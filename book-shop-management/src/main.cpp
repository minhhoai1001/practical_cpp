#include <iostream>
#include "books_management.h"
#include "books.h"
#include "suppliers.h"
#include "purchases.h"

// +--------------------------------+
// |		Global Variable         |
// +--------------------------------+
std::unique_ptr<pqxx::connection> Postgres;

// ----------------
// Functions
// ----------------

void book_menu()
{
    int c;
    books book;
    std::cout << "*************************************************" << std::endl;
    std::cout << "                  BOOK MENU" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "   1. ADD" << std::endl;
    std::cout << "   2. UPDATE PRICE" << std::endl;
    std::cout << "   3. SEARCH" << std::endl;
    std::cout << "   4. UPDATE STATUS" << std::endl;
    std::cout << "   5. DISPLAY ALL" << std::endl;
    std::cout << "   6. RETURN TO MAIN MENU" << std::endl << std::endl << std::endl;
    std::cout << "Enter Your Choice : ";
    std::cin >> c;
    switch (c)
    {
        case 1:
            book.add(Postgres);
            break;
        case 2:
            book.update_price(Postgres);
            break;
        case 3:
            book.search(Postgres);
            break;
        case 4:
            book.update(Postgres);
            break;
        case 5:
            book.display(Postgres);
            break;
        case 6:
            return;
            break;
        default:
            std::cout << "Wrong Input" << std::endl << "Invalid input";
            break;
    }
    return;
}

// suppliers menu

void supplier_menu()
{
    int c;
    suppliers supplier;
    std::cout << "*************************************************" << std::endl;
    std::cout << "                SUPPLIER MENU" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "   1. ADD" << std::endl;
    std::cout << "   2. REMOVE" << std::endl;
    std::cout << "   3. SEARCH" << std::endl;
    std::cout << "   4. RETURN TO MAIN MENU" << std::endl << std::endl;
    std::cout << "Enter Your Choice : ";
    std::cin >> c;
    switch (c)
    {
        case 1:
            supplier.add_supplier(Postgres);
            break;
        case 2:
            supplier.remove_supplier(Postgres);
            break;
        case 3:
            supplier.search_id(Postgres);
            break;
        case 4:
            return;
        default:
            std::cout << "Wrong Input" << std::endl << "Invalid input";
            break;
    }
}

// purchase menu
void purchases_menu()
{
    int c;
    purchases p;
    std::cout << "*************************************************" << std::endl;
    std::cout << "                PURCHASES MENU" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "   1. New Order" << std::endl;
    std::cout << "   2. View All" << std::endl;
    std::cout << "   3. Cancel Order" << std::endl;
    std::cout << "   4. Recieved Order" << std::endl;
    std::cout << "   5. RETURN TO MAIN MENU" << std::endl << std::endl;
    std::cout << "Enter Your Choice : ";
    std::cin >> c;
    switch (c)
    {
        case 1:
            p.new_ord(Postgres);
            break;
        case 2:
            p.view(Postgres);
            break;
        case 3:
            p.mar_cancel(Postgres);
            break;
        case 4:
            p.mark_reciv(Postgres);
            break;
        case 5:
            return;
        default:
            std::cout << "Wrong Input" << std::endl << "Invalid input";
            break;
    }
}

void emp_menu();
void mem_menu();
void sal_menu();

// main menu

void main_menu()
{
    int c;
    std::cout << "*************************************************" << std::endl;
    std::cout << "         BOOKSHOP MANGEMENT SYSTEM" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "   1. BOOKS" << std::endl;
    std::cout << "   2. SUPPLIERS" << std::endl;
    std::cout << "   3. PURCHASES" << std::endl;
    std::cout << "   4. EMPLOYEES" << std::endl;
    std::cout << "   5. MEMBERS" << std::endl;
    std::cout << "   6. SALES" << std::endl;
    std::cout << "   7. EXIT" << std::endl << std::endl << std::endl;    
    std::cout << "Enter Your Choice : ";
    std::cin >> c;
    switch (c)
    {
        case 1:
            system("clear");
            book_menu();
            break;
        case 2:
            system("clear");
            supplier_menu();
            break;
        case 3:
            system("clear");
            purchases_menu();
            break;
        // case 4:
        //     system("clear");
        //     emp_menu();
        //     break;
        // case 5:
        //     system("clear");
        //     mem_menu();
        //     break;
        // case 6:
        //     system("clear");
        //     sal_menu();
        //     break;
        case 7:
            exit(1);
        default:
            system("clear");
            std::cout << "Wrong Input" << std::endl << std::endl << "Invalid input";
            break;
    }
    return;
}

int main(int argc, char* argv[])
{
    char db[256];
    snprintf(db, sizeof(db), "dbname = %s user = %s password = %s hostaddr = %s port = %d", 
                DATABASE, USER, PASSWORD, HOST, PORT);
    std::cout<<db<<std::endl;

    try {
        Postgres = std::make_unique<pqxx::connection>(db);
        if (Postgres->is_open()) {
            std::cout << "Opened database successfully: " << Postgres->dbname() << std::endl;
            while(1)
            {
                // system("clear");
                main_menu();
            }
        } else {
            std::cout << "Can't open database \n";
            return 1;
        }
        Postgres->disconnect ();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}