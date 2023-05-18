#include "../headers/Account.hpp"

#include <iostream>
#include <random.hpp>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"
#include "../headers/Errors.hpp"

std::string Account::generareIban() {
    using Random = effolkronium::random_static;
    return "RO" + std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999)) + ' ' +
        std::to_string(Random::get(1000, 9999));
}

Account::Account() : iban(generareIban()) {
    // std::cout << "Const " << *this << '\n'; this will call a virtual function, nono
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "Account iban: " << account.iban << '\n';
    if (account.currencyAccount.empty()) {
        os << "Account has no currency accounts\n";
    }
    else {
        for (auto it = account.currencyAccount.begin();
            it != account.currencyAccount.end(); ++it) {
            os << "Account currency: " << it->first << " " << it->second << '\n';
        }
    }
    if (account.carduri.empty()) {
        os << "Account has no cards\n";
    }
    else {
        for (auto it = account.carduri.begin(); it != account.carduri.end(); ++it) {
            os << "Account carduri: " << *it << '\n';
        }
    }
    account.print(os);
    return os;
}

bool Account::haveCurrency(const Currency& currency) {
    if (currencyAccount.find(currency) != currencyAccount.end()) {
        return true;
    }
    return false;
}

bool Account::haveAmountOfCurrency(float amount, const Currency& currency) {
    if (haveCurrency(currency) && currencyAccount[currency] >= amount) {
        return true;
    }
    return false;
}

bool Account::haveCard(const Card& card_try) {
    return std::find(carduri.begin(), carduri.end(), card_try) != carduri.end();
}

void Account::addFunds(float amount, const Currency& currency) {
    if (haveCurrency(currency)) {
        currencyAccount[currency] += amount;
    }
    else {
        currencyAccount[currency] = amount;
    }
}

void Account::exchange(float amount, const Currency& currencyFrom,
    const Currency& currencyTo) {
    if (!haveAmountOfCurrency(amount, currencyFrom)) {
        throw NoAmountOfMoneyInCurrency(amount, currencyFrom);
    }
    currencyAccount[currencyFrom] -= amount;
    addFunds(amount, currencyTo);
}

void Account::withdrawal(float amount, const Currency& currency) {
    if (!haveAmountOfCurrency(amount, currency)) {
        throw NoAmountOfMoneyInCurrency(amount, currency);
    }
    currencyAccount[currency] -= amount;
}

bool Account::payWithCard(const Card& card, float amount, const Currency& currency) {
    try {
        card.checkExpired();
    } catch (ExpiredCard& err) {
        std::cout << err.what() << '\n';
    }
    amount = calculatePayAmountWithTax(amount);
    if (haveCard(card) && haveAmountOfCurrency(amount, currency)) {
        currencyAccount[currency] -= amount;
        return true;
    }
    return false;
}

void Account::addNewCard() {
    carduri.push_back(Card());
}

Tranzactie Account::tryToMakeTransaction(std::shared_ptr<Account>& recipientAccount, float amount, const Currency& currency) {
    amount = calculatePayAmountWithTax(amount);
    bool realizata = haveAmountOfCurrency(amount, currency);
    if (realizata) {
        currencyAccount[currency] -= amount;
        recipientAccount->addFunds(amount, currency);
    }
    return Tranzactie(iban, recipientAccount->iban, amount, currency, realizata);
}

const std::vector<Card> Account::getCards() {
    return carduri;
}
