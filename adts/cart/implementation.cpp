#include <iostream>
#include <fstream>
#include <string>
#include "data.hpp"
#include "../inventory/data.hpp"

Cart::Cart(std::string path)
{
    _path = path;
    _file.open(path);
    if (!_file.is_open())
    {
        std::cout << "Error: could not open file\n";
        return;
    }
    int id = 0, qty = 0;
    std::string line = "", name = "";
    double price = 0.0;
    while (std::getline(_file, line))
    {
        id = std::stoi(line);
        std::getline(_file, name);
        std::getline(_file, line);
        price = std::stod(line);
        std::getline(_file, line);
        qty = std::stoi(line);
        Item *item = new Item(id, name, price, qty);
        _items->insert(std::pair<int, Item *>(id, item));
        std::getline(_file, line);
    }
    _file.close();
}

Cart::~Cart()
{
    delete _items;
}

void Cart::addItem(int id, std::string name, double price, int qty)
{
    Item *item = new Item(id, name, price, qty);
    _items->insert(std::pair<int, Item *>(id, item));
    _total += price * qty;
}

void Cart::returnItem(int id, int qty)
{
    if (_items->find(id) != _items->end())
    {
        Item *item = _items->at(id);
        item->setQty(item->getQty() + qty);
        _total -= item->getPrice() * qty;
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
    }
}
void Cart::removeItem(int id)
{
    if (_items->find(id) != _items->end())
    {
        _items->erase(id);
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
    }
}
void Cart::updateQty(int id, int qty)
{
    if (_items->find(id) != _items->end())
    {
        Item *item = _items->at(id);
        item->setQty(qty);
        _total -= item->getPrice() * qty;
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
    }
}

void Cart::displayCart() const
{
    std::cout << "\nCart:\n";
    for (auto i : *_items)
    {
        std::cout << "ID: " << i.first << "\n";
        std::cout << "Name: " << i.second->getName() << "\n";
        std::cout << "Qty: " << i.second->getQty() << "\n";
        std::cout << "Price: " << i.second->getPrice() << "\n\n";
    }
}

void Cart::saveCart()
{
    _file.open(_path);
    for (auto i : *_items)
    {
        _file << i.first << "\n";
        _file << i.second->getName() << "\n";
        _file << i.second->getPrice() << "\n";
        _file << i.second->getQty() << "\n\n";
    }
    _file.close();
}

double Cart::getTotal() const
{
    double total = 0.0;
    for (auto i : *_items)
    {
        total += i.second->getPrice() * i.second->getQty();
    }
    return total;

}