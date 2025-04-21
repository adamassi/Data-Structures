#include "Costumer.h"



int Costumer::getid() const {
    return this->id;
}
bool Costumer::operator==(const Costumer &c) const {
    return id == c.id;
}

bool Costumer::operator!=(const Costumer &c) const {
    return !(c == *this);
}

bool Costumer::operator<(const Costumer &c) const {
    return id < c.id;
}

bool Costumer::operator>(const Costumer &c) const {
    return c < *this;
}

bool Costumer::operator<=(const Costumer &c) const {
    return !(c < *this);
}

bool Costumer::operator>=(const Costumer &c) const {
    return !(*this < c);
}


