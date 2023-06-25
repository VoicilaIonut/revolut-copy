#ifndef CARDFACTORY_HPP
#define CARDFACTORY_HPP

#include <iostream>
#include <date.h>

#include "Card.hpp"
#include "CardTypes.hpp"


class CardFactory {
public:
    static Card cardGold(const std::string& ownerName, const std::string& accountNumber) { return Card(ownerName, 1, Gold, accountNumber); }
    static Card cardSilver(const std::string& ownerName, const std::string& accountNumber) { return Card(ownerName, 0.5, Silver, accountNumber); }
    static Card cardBasic(const std::string& ownerName, const std::string& accountNumber) { return Card(ownerName, 0, Basic, accountNumber); }
};

#endif