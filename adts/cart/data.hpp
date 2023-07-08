#pragma once
#include <string>
#include <map>
#include <fstream>
#include "../item/data.hpp"

class Cart
{
public:
    Cart(std::string path);
    ~Cart();
    void addItem(int id, std::string name, double price, int qty);
    void returnItem(int id, int qty);
    void removeItem(int id);
    void updateQty(int id, int qty);
    void displayCart() const;
    void saveCart();
    double getTotal() const;

private:
    std::map<int, Item *> *_items = new std::map<int, Item *>();
    std::string _path = "";
    std::fstream _file = {};
    double _total = 0.0;
};