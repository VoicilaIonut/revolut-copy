#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>

#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "User.hpp"

class Card {
    std::string cod, dataExpirare, cvv;

    const std::string generateCod();

    const std::string generateDataExpirare();

    const std::string generateCvv();

   public:
    Card();

    Card(const Card& other);

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    Card& operator=(const Card& other);

    bool operator==(const Card& other) const;

    ~Card();

    // bool checkCod(const std::string& codTry);
    // bool checkDataExpirare(const std::string& dataExpirareTry);
    // bool checkCvv(const std::string& cvvTry);
    // const std::string getCod();
    // const std::string getDataExpirare();
    // const std::string getCvv();
};

#endif