#ifndef TRANZACTIE_HPP
#define TRANZACTIE_HPP

#include <iostream>

#include "Card.hpp"
#include "Currencies.hpp"

template <typename T>
class Tranzactie {
    std::string ibanSender, ibanRecipient;
    T value;
    Currency currency;
    bool realizata;

public:
    Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient,
        T value_, const Currency& currency_, bool realizata_);

    Tranzactie(const Tranzactie<T>& other);

    template <typename TT>
    friend std::ostream& operator<<(std::ostream& os,
        const Tranzactie<TT>& tranzactie);

    Tranzactie<T>& operator=(const Tranzactie<T>& tranzactie);

    ~Tranzactie();
};

#include "../src/Tranzactie.cpp"
#endif
