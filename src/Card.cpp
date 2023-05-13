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
    return act + date::years{4};
}

const std::string Card::generateCvv() {
    using Random = effolkronium::random_static;
    std::string cvvGenerated = std::to_string(Random::get(100, 999));
    return cvvGenerated;
}

Card::Card()
    : dataExpirare(generateDataExpirare()),
    cod(generateCod()),
    cvv(generateCvv()) {
    std::cout << "Const " << *this << '\n';
}

Card::Card(const Card& other)
    : dataExpirare(other.dataExpirare), cod(other.cod), cvv(other.cvv) {
    std::cout << "Constr de copiere" << *this << "\n";
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.cod << " " << card.dataExpirare << " " << card.cvv << '\n';
    return os;
}

Card& Card::operator=(const Card& other) {
    std::cout << "operator= " << *this << "\n";
    dataExpirare = other.dataExpirare;
    cod = other.cod;
    cvv = other.cvv;
    return *this;
}

bool Card::operator==(const Card& other) const {
    return other.cod == this->cod && other.dataExpirare == this->dataExpirare &&
        other.cvv == this->cvv;
}

void Card::checkExpired() const {
    if (date::floor<date::days>(std::chrono::system_clock::now()) > dataExpirare) {
        throw ExpiredCard();
    }
}

Card::~Card() { std::cout << "Destroing card: " << *this << "\n"; }

// bool Card::checkCod(const std::string& codTry) {
//     if (cod == codTry) {
//         return true;
//     }
//     return false;
// }

// bool Card::checkDataExpirare(const std::string& dataExpirareTry) {
//     if (dataExpirare == dataExpirareTry) {
//         return true;
//     }
//     return false;
// }

// bool Card::checkCvv(const std::string& cvvTry) {
//     if (cvv == cvvTry) {
//         return true;
//     }
//     return false;
// }
// const std::string Card::getCod() {
//     return cod;
// }
// const std::string Card::getDataExpirare() {
//     return dataExpirare;
// }
// const std::string Card::getCvv() {
//     return cvv;
// }
