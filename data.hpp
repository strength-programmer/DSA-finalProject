#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "./adts/inventory/data.hpp"
#include "./adts/cart/data.hpp"

class BaseProgram
{
protected:
    struct Paths
    {
        std::string _inventory = "./data/inventory.txt";
        std::string _persist = "./data/_persist.txt";
        std::string _cart = "./data/cart.txt";
    };
    const Paths _paths = Paths();
};

class Program : BaseProgram
{
private:
    const std::map<int, std::string> _choices = {
        {1, "Add items to cart"},
        {2, "Remove items from cart"},
        {3, "View cart"},
        {4, "View inventory"},
        {5, "Save cart"},
        {6, "Calculate total"},
        {7, "Exit"}};

    Inventory *_inventory = new Inventory(_paths._inventory);
    Cart *_cart = new Cart(_paths._cart);

    const std::vector<std::vector<std::string>> _members = {
        {"Julian Carl Oñate: Lead Programmer"},
        {"Maxeene Alyssa Gamas: Programmer 1"},
        {"Michael Jr. Udarbe: Programmer 2"},
        {"Nikki Mikhaella M. Rosario: Programmer 3"},
        {"Jazz Angelyn N. Bitancor: Programmer 4"}};

    void prompt() const;
    void displayMenu(std::map<int, std::string> m) const;

public:
    Program();
    ~Program();
    void init();
};
