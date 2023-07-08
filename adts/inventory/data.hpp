#pragma once
#include <map>
#include <string>
#include <fstream>
#include "../item/data.hpp"

class Inventory
{
private:
    std::string _path = "";
    std::fstream _file = {};
    std::map<int, Item *> *_items = new std::map<int, Item *>();

public:
    Inventory(std::string path);
    ~Inventory();
    Item *getItem(int id);
    void addItem(int id, std::string name, double price, int qty);
    void returnItem(int id, int qty);
    void updateQty(int id, int qty);
    void displayInventory() const;
    void displayItem(int id) const;
    void saveInventory();
};