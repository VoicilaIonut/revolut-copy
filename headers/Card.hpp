#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <date.h>

#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "CardTypes.hpp"

class Card {
    date::year_month_day dataExpirare;
    std::string cod, cvv, ownerName;
    double cashBack;
    CardType tip;
    std::string accountNumber;

    const std::string generateCod();

    const date::year_month_day generateDataExpirare();

    const std::string generateCvv();

public:
    Card(const std::string& ownerName_, const double& cashBack_, const CardType& tip_, const std::string& accountNumber_);

    Card(const Card& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    Card& operator=(const Card& other) = default;

    bool operator==(const Card& other) const;

    void checkExpired() const;

    double getCashBack() const;

    ~Card() = default;

    // bool checkCod(const std::string& codTry);
    // bool checkDataExpirare(const std::string& dataExpirareTry);
    // bool checkCvv(const std::string& cvvTry);
    // const std::string getCod();
    // const std::string getDataExpirare();
    // const std::string getCvv();
};

#endif