#ifndef TRANZACTIE_HPP
#define TRANZACTIE_HPP

#include <iostream>

#include "Card.hpp"
#include "Currencies.hpp"

// the withdraws are made between the company account and the user account
class Tranzactie {
    std::string ibanSender, ibanRecipient;
    float value;
    Currency currency;
    bool realizata;

public:
    Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient,
        float value_, const Currency& currency_, bool realizata_);

    Tranzactie(const Tranzactie& other);

    friend std::ostream& operator<<(std::ostream& os,
        const Tranzactie& tranzactie);

    Tranzactie& operator=(const Tranzactie& tranzactie);

    ~Tranzactie();
};

#endif
