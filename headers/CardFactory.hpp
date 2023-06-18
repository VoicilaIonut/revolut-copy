#ifndef CARDFACTORY_HPP
#define CARDFACTORY_HPP

#include <iostream>
#include <date.h>

#include "Card.hpp"
#include "CardTypes.hpp"


class CardFactory {
public:
    static Card cardGold() { return Card(Gold, 1); }
    static Card cardSilver() { return Card(Silver, 0.5); }
    static Card cardBasic() { return Card(Basic, 0); }
};

#endif