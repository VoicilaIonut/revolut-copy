#include "../headers/Card.hpp"


#include <iostream>
#include <random.hpp>

#include "../headers/Tranzactie.hpp"
#include "../headers/User.hpp"
#include "../headers/Errors.hpp"

const std::string Card::generateCod() {
    using Random = effolkronium::random_static;
    return std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999));
}

const date::year_month_day Card::generateDataExpirare() {
    date::year_month_day act = date::floor<date::days>(std::chrono::system_clock::now());
    return act + date::years { 4 };
}

const std::string Card::generateCvv() {
    using Random = effolkronium::random_static;
    std::string cvvGenerated = std::to_string(Random::get(100, 999));
    return cvvGenerated;
}

Card::Card(const std::string& ownerName_, const double& cashBack_, const CardType& tip_, const std::string& accountNumber_) :
    dataExpirare(generateDataExpirare()),
    cod(generateCod()),
    cvv(generateCvv()),
    ownerName(ownerName_),
    cashBack(cashBack_),
    tip(tip_),
    accountNumber(accountNumber_) {
    std::cout << "Constructor card: \n" << *this << '\n';
}


std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "Data de expirare: " << card.dataExpirare;
    os << " Numarul cardului: " << card.cod;
    os << " CVV: " << card.cvv;
    os << " Detinator: " << card.ownerName;
    os << " Cashback: " << card.cashBack;
    os << " Tip card: " << card.tip;
    os << " Numar cont: " << card.accountNumber;
    os << '\n';
    return os;
}


bool Card::operator==(const Card& other) const {
    return other.dataExpirare == this->dataExpirare
        && other.cod == this->cod
        && other.cvv == this->cvv
        && other.ownerName == this->ownerName
        && other.cashBack == this->cashBack
        && other.tip == this->tip
        && other.accountNumber == this->accountNumber;
}

void Card::checkExpired() const {
    if (date::floor<date::days>(std::chrono::system_clock::now()) > dataExpirare) {
        throw ExpiredCard();
    }
}

double Card::getCashBack() const {
    return cashBack;
}

