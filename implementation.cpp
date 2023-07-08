#include <iostream>
#include "data.hpp"

#ifndef _WIN32
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

Program::Program() = default;
Program::~Program() = default;

void Program::prompt() const
{
    std::cout << "Enter choice: ";
}

void Program::displayMenu(std::map<int, std::string> m) const
{
    std::cout << "\nMenu:\n";
    for (auto i : m)
        std::cout << i.first << ". " << i.second << "\n";
    std::cout << "\n";
}

void Program::init()
{
    int choice = 0;
    std::cout << "Welcome to the Goal Diggers Grocery System 2.0!\n";
    do
    {
        displayMenu(_choices);
        prompt();
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid choice\n";
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            system(CLEAR);
            std::cout << "--Add items to cart--\n";
            std::cout << "Enter item id: ";
            int id = 0, qty = 0;
            std::cin >> id;
            std::cout << "Enter quantity: ";
            std::cin >> qty;
            Item *item = _inventory->getItem(id);
            if (item == nullptr)
            {
                std::cout << "Error: item not found\n";
                break;
            }
            _cart->addItem(id, item->getName(), item->getPrice() * qty, qty);
            _inventory->returnItem(id, qty);
            _inventory->saveInventory();
            break;
        }
        case 2:
        {
            system(CLEAR);
            std::cout << "--Remove items from cart--\n";
            std::cout << "Enter item id: ";
            int id = 0, qty = 0;
            std::cin >> id;
            std::cout << "Enter quantity: ";
            std::cin >> qty;
            Item *item = _inventory->getItem(id);
            if (item == nullptr)
            {
                std::cout << "Error: item not found\n";
                break;
            }
            _cart->returnItem(id, -qty);
            _inventory->updateQty(id, -qty);
            _inventory->saveInventory();
            break;
        }
        case 3:
        {
            std::cout << "--View cart--\n";
            _cart->displayCart();
            break;
        }
        case 4:
        {
            std::cout << "--View inventory--\n";
            _inventory->displayInventory();
            break;
        }
        case 5:
        {
            system(CLEAR);
            std::cout << "--Save cart--\n";
            _cart->saveCart();
            std::cout << "Success: Cart saved!\n";
            break;
        }
        case 6:
        {
            system(CLEAR);
            std::cout << "--Calculate total--\n";
            std::cout << "Total: " << _cart->getTotal() << "\n";
            break;
        }
        case 7:
        {
            system(CLEAR);
            std::cout << "Exiting...\n\nMembers:\n";
            _inventory->saveInventory();
            _cart->saveCart();
            for (auto i : _members)
                for (auto j : i)
                    std::cout << " - " << j << "\n";
            break;
        }
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    } while (choice != 7);
}