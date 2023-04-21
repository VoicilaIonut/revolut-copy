#include "../headers/User.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"

bool User::haveCurrency(const Currency& currency) {
    if (currencyAccount.find(currency) != currencyAccount.end()) {
        return true;
    }
    return false;
}

bool User::haveAmountOfCurrency(float amount, const Currency& currency) {
    if (haveCurrency(currency) && currencyAccount[currency] >= amount) {
        return true;
    }
    return false;
}

bool User::checkCnp(const std::string& testCnp) {
    if (cnp == testCnp) {
        return true;
    }
    return false;
}

bool User::haveCard(const Card& card_try) {
    for (const Card& card : carduri) {
        if (card == card_try) {
            return true;
        }
    }
    return false;
}

// void User::changeNumarTelefon(const std::string& numarTelefonNew) {
//     numarTelefon = numarTelefonNew;
// }

// void User::changeEmail(const std::string& emailNew) { email = emailNew; }

User::User() = default;

User::User(const std::string& nume_, const std::string& cnp_,
           const std::string& iban_, const std::string& email_,
           const std::string& numarTelefon)
    : nume(nume_),
      cnp(cnp_),
      iban(iban_),
      email(email_),
      numarTelefon(numarTelefon) {
    std::cout << "User constructor\n" << *this;
}

User::User(const User& other)
    : nume(other.nume),
      cnp(other.cnp),
      iban(other.iban),
      email(other.email),
      numarTelefon(other.numarTelefon),
      currencyAccount(other.currencyAccount),
      carduri(other.carduri) {
    std::cout << "Constr de copiere" << *this << "\n";
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User name: " << user.nume << '\n';
    os << "User cnp: " << user.cnp << '\n';
    os << "User iban: " << user.iban << '\n';
    os << "User email: " << user.email << '\n';
    os << "User numar telefon: " << user.numarTelefon << '\n';
    if (user.currencyAccount.empty()) {
        os << "User has no currency accounts\n";
    } else {
        for (auto it = user.currencyAccount.begin();
             it != user.currencyAccount.end(); ++it) {
            os << "User currency: " << it->first << " " << it->second << '\n';
        }
    }
    if (user.carduri.empty()) {
        os << "User has no cards\n";
    } else {
        for (auto it = user.carduri.begin(); it != user.carduri.end(); ++it) {
            os << "User carduri: " << *it << '\n';
        }
    }
    return os;
}

User& User::operator=(const User& other) {
    std::cout << "operator= " << *this << "\n";
    nume = other.nume;
    cnp = other.cnp;
    iban = other.iban;
    email = other.email;
    numarTelefon = other.numarTelefon;
    currencyAccount = other.currencyAccount;
    carduri = other.carduri;
    return *this;
}

User::~User() { std::cout << "Destroing User" << *this << "\n" << *this; }

const std::vector<Card> User::getCardsWithCnp(const std::string& cnpTry) {
    if (checkCnp(cnpTry)) {
        return carduri;
    }
    return {};
}

void User::addFunds(float amount, const Currency& currency) {
    if (haveCurrency(currency)) {
        currencyAccount[currency] += amount;
    } else {
        currencyAccount[currency] = amount;
    }
}

bool User::exchange(float amount, const Currency& currencyFrom,
                    const Currency& currencyTo) {
    if (haveAmountOfCurrency(amount, currencyFrom)) {
        currencyAccount[currencyFrom] -= amount;
        addFunds(amount, currencyTo);
        return true;
    }
    return false;
}

bool User::withdrawal(float amount, const Currency& currency) {
    if (haveAmountOfCurrency(amount, currency)) {
        currencyAccount[currency] -= amount;
        return true;
    }
    return false;
}

bool User::tryToAddNewCardWithCnp(const std::string& cnpTry) {
    if (checkCnp(cnpTry)) {
        carduri.push_back(Card());
        return true;
    }
    return false;
}

bool User::payWithCard(const Card& card, float amount,
                       const Currency& currency) {
    if (haveCard(card) && haveAmountOfCurrency(amount, currency)) {
        currencyAccount[currency] -= amount;
        return true;
    }
    return false;
}

Tranzactie User::tryToMakeTransaction(User& recipientUser, float amount,
                                      const Currency& currency) {
    bool realizata = haveAmountOfCurrency(amount, currency);
    if (realizata) {
        currencyAccount[currency] -= amount;
        recipientUser.addFunds(amount, currency);
    }
    return Tranzactie(iban, recipientUser.iban, amount, currency, realizata);
}
