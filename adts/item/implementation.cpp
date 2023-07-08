#include <string>
#include "data.hpp"

Item::Item(int id, std::string name, double price, int qty)
{
    _id = id;
    _name = name;
    _price = price;
    _qty = qty;
}

Item::~Item() = default;

int Item::getId() const
{
    return _id;
}

std::string Item::getName() const
{
    return _name;
}

double Item::getPrice() const
{
    return _price;
}

int Item::getQty() const
{
    return _qty;
}

void Item::setQty(int qty)
{
    _qty = qty;
}