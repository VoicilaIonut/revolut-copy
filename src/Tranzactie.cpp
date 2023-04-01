#include <iostream>
#include "../headers/User.hpp"
#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"

Tranzactie::Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient, float value_, const Currency& currency_, bool realizata_): ibanSender(ibanSender), ibanRecipient(ibanRecipient), value(value_), currency(currency_), realizata(realizata_) {
    std::cout << "Tranzactie constructor\n" << *this << '\n';
}

Tranzactie::Tranzactie(const Tranzactie& other): ibanSender(other.ibanSender), ibanRecipient(other.ibanRecipient), value(other.value), currency(other.currency), realizata(other.realizata) {
    std::cout << "Constr de copiere" << *this << "\n";
}


std::ostream& operator<<(std::ostream& os, const Tranzactie& tranzactie) {
    os << "ibanSender: " << tranzactie.ibanSender << " ibanRecipient: " << tranzactie.ibanRecipient << '\n';
    os << "Value: " << tranzactie.value << '\n';
    os << "Currency: " << tranzactie.currency << '\n';
    os << "Realizata: " << tranzactie.realizata << '\n';
    return os;
}

Tranzactie &Tranzactie::operator=(const Tranzactie& tranzactie) {
    std::cout << "operator= " << *this << "\n";
    ibanSender = tranzactie.ibanSender;
    ibanRecipient = tranzactie.ibanRecipient;
    value = tranzactie.value;
    currency = tranzactie.currency;
    realizata = tranzactie.realizata;
    return *this;
}

Tranzactie::~Tranzactie() {
    std::cout << "Destroing Tranzactie" << *this << "\n";
}
