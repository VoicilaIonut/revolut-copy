#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <date.h>

#include "Currencies.hpp"
#include "Tranzactie.hpp"

class Card {
    date::year_month_day dataExpirare;
    std::string cod, cvv;

    const std::string generateCod();

    const date::year_month_day generateDataExpirare();

    const std::string generateCvv();

public:
    Card();

    Card(const Card& other);

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    Card& operator=(const Card& other);

    bool operator==(const Card& other) const;

    void checkExpired() const;

    ~Card();

    // bool checkCod(const std::string& codTry);
    // bool checkDataExpirare(const std::string& dataExpirareTry);
    // bool checkCvv(const std::string& cvvTry);
    // const std::string getCod();
    // const std::string getDataExpirare();
    // const std::string getCvv();
};

#endif