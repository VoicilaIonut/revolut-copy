#include "../headers/Card.hpp"

#include <date.h>

#include <iostream>
#include <random.hpp>

#include "../headers/Tranzactie.hpp"
#include "../headers/User.hpp"

const std::string Card::generateCod() {
    using Random = effolkronium::random_static;
    return std::to_string(Random::get(1000, 9999)) + ' ' +
           std::to_string(Random::get(1000, 9999)) + ' ' +
           std::to_string(Random::get(1000, 9999)) + ' ' +
           std::to_string(Random::get(1000, 9999));
}

const std::string Card::generateDataExpirare() {
    return date::format("%Y-%m-%d", std::chrono::system_clock::now() +
                                        std::chrono::hours(24 * 30 * 60));
}

const std::string Card::generateCvv() {
    using Random = effolkronium::random_static;
    std::string cvvGenerated = std::to_string(Random::get(100, 999));
    return cvvGenerated;
}

Card::Card()
    : cod(generateCod()),
      dataExpirare(generateDataExpirare()),
      cvv(generateCvv()) {
    std::cout << "Const " << *this << '\n';
}

Card::Card(const Card &other)
    : cod(other.cod), dataExpirare(other.dataExpirare), cvv(other.cvv) {
    std::cout << "Constr de copiere" << *this << "\n";
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << card.cod << " " << card.dataExpirare << " " << card.cvv << '\n';
    return os;
}

Card &Card::operator=(const Card &other) {
    std::cout << "operator= " << *this << "\n";
    cod = other.cod;
    dataExpirare = other.dataExpirare;
    cvv = other.cvv;
    return *this;
}

bool Card::operator==(const Card &other) const {
    return other.cod == this->cod && other.dataExpirare == this->dataExpirare &&
           other.cvv == this->cvv;
}

Card::~Card() { std::cout << "Destroing card" << *this << "\n"; }

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
