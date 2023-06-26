#include "../headers/Account.hpp"

#include <iostream>
#include <random.hpp>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"
#include "../headers/Errors.hpp"

std::string Account::generareIban() {
    using Random = effolkronium::random_static;
    return "RO" + std::to_string(Random::get(1000, 9999)) +
        std::to_string(Random::get(1000, 9999)) +
        std::to_string(Random::get(1000, 9999)) +
        std::to_string(Random::get(1000, 9999));
}

Account::Account() : iban(generareIban()) {
    // std::cout << "Const " << *this << '\n'; this will call a virtual function, nono
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "Iban cont: " << account.iban << '\n';
    if (account.currencyAccount.empty()) {
        os << "Contul nu detine nicio valuta.\n";
    } else {
        for (auto it = account.currencyAccount.begin();
            it != account.currencyAccount.end(); ++it) {
            os << "Sold curent: " << stringCurrency[it->first] << " " << it->second << '\n';
        }
    }
    if (account.carduri.empty()) {
        os << "Contul nu are carduri asociate.\n";
    } else {
        os << "Contul detine urmatoarele carduri:\n";
        for (auto it = account.carduri.begin(); it != account.carduri.end(); ++it) {
            os << "Cardul: " << *it << '\n';
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

void Account::addFunds(float amount, const Currency& currency) {
    if (haveCurrency(currency)) {
        currencyAccount[currency] += amount;
    } else {
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

// Throws NoAmountOfMoneyInCurrency if there is not enough money in the account
void Account::withdrawal(float amount, const Currency& currency) {
    amount = calculateWithdraw(amount);
    if (!haveAmountOfCurrency(amount, currency)) {
        throw NoAmountOfMoneyInCurrency(amount, currency);
    }
    currencyAccount[currency] -= amount;
}

// Throws ExpiredCard if called with a expired card. 
bool Account::payWithCard(const Card& card, float amount, const Currency& currency) {
    card.checkExpired();
    amount = calculatePayAmountWithTax(amount);
    if (haveAmountOfCurrency(amount, currency)) {
        currencyAccount[currency] -= amount;
        currencyAccount[currency] += amount * card.getCashBack();
        return true;
    }
    return false;
}

bool Account::haveCard(const Card& card) const {
    return std::find(carduri.begin(), carduri.end(), card) != carduri.end();
}

void Account::addNewCard(const std::string& ownerName, const CardType& cardType) {
    if (cardType == Gold) {
        carduri.push_back(CardFactory::cardGold(ownerName, iban));
    } else if (cardType == Silver) {
        carduri.push_back(CardFactory::cardSilver(ownerName, iban));
    } else {
        carduri.push_back(CardFactory::cardBasic(ownerName, iban));
    }
}

std::vector<Card> Account::getCards() const {
    return carduri;
}

bool Account::checkIban(const std::string& iban_) const {
    return this->iban == iban_;
}