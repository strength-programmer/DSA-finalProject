#pragma once
#include <string>

class Item
{
private:
    int _id = 0;
    std::string _name = "";
    double _price = 0.0;
    int _qty = 0;

public:
    Item(int id, std::string name, double price, int qty);
    ~Item();
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQty() const;
    void setQty(int qty);
};