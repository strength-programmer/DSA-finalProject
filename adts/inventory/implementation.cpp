#include <iostream>
#include "data.hpp"

Inventory::Inventory(std::string path)
{
    _path = path;
    _file.open(_path);
    int id = 0, qty = 0;
    std::string line = "", name = "";
    double price = 0.0;
    while (std::getline(_file, line))
    {
        id = std::stoi(line);      // id
        std::getline(_file, name); // name
        std::getline(_file, line);
        price = std::stod(line); // price
        std::getline(_file, line);
        qty = std::stoi(line); // qty
        Item *item = new Item(id, name, price, qty);
        _items->insert(std::pair<int, Item *>(id, item));
        std::getline(_file, line);
    }
    _file.close();
}
Inventory::~Inventory()
{
    while (!_items->empty())
    {
        _items->erase(_items->begin());
    }
    delete _items;
};

void Inventory::addItem(int id, std::string name, double price, int qty)
{
    Item *item = new Item(id, name, price, qty);
    _items->insert(std::pair<int, Item *>(id, item));
}
Item *Inventory::getItem(int id)
{
    if (_items->find(id) != _items->end())
    {
        return _items->at(id);
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
        return nullptr;
    }
}
void Inventory::returnItem(int id, int qty)
{
    if (_items->find(id) != _items->end())
    {
        Item *item = _items->at(id);
        item->setQty(item->getQty() - qty);
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
    }
}
void Inventory::updateQty(int id, int qty)
{
    if (_items->find(id) != _items->end())
    {
        Item *item = _items->at(id);
        int qt = item->getQty();
        if (qt < qty)
        {
            std::cout << "Error: not enough items in stock\n";
            return;
        }
        item->setQty(qt - qty);
    }
    else
    {
        std::cout << "Error: item with ID " << id << " not found\n";
    }
}
void Inventory::displayInventory() const
{
    for (auto i : *_items)
    {
        std::cout << i.first << ". " << i.second->getName() << "\n"
                  << "Price: " << i.second->getPrice() << "\n"
                  << "Quantity: " << i.second->getQty() << "\n\n";
    }
}

void Inventory::displayItem(int id) const
{
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << _items->at(id)->getName() << "\n";
    std::cout << "Price: " << _items->at(id)->getPrice() << "\n";
    std::cout << "Quantity: " << _items->at(id)->getQty() << "\n";
}

void Inventory::saveInventory()
{
    _file.open(_path);
    if (!_file.is_open())
    {
        std::cout << "Error: could not open file " << _path << "\n";
        return;
    }
    for (auto i : *_items)
    {
        _file << i.first << "\n";
        _file << i.second->getName() << "\n";
        _file << i.second->getPrice() << "\n";
        _file << i.second->getQty() << "\n";
        _file << "\n";
    }
    _file.close();
}