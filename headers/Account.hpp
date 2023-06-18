#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <random.hpp>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Card.hpp"
#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "CardFactory.hpp"

class Account {
private:
    virtual void print(std::ostream& os) const = 0;

protected:
    std::string iban;
    std::unordered_map<Currency, float> currencyAccount = {};
    std::vector<Card> carduri = {};

    Account();

    Account(const Account& other) = default;

    virtual ~Account() = default;

    Account& operator=(const Account& other) = default;

    bool haveCurrency(const Currency& currency);

    bool haveAmountOfCurrency(float amount, const Currency& currency);

    std::string generareIban();

    virtual float calculatePayAmountWithTax(const float& amount)const = 0;
public:
    virtual std::shared_ptr<Account> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Account& user);

    void addFunds(float amount, const Currency& currency);

    void exchange(float amount, const Currency& currencyFrom,
        const Currency& currencyTo);

    void withdrawal(float amount, const Currency& currency);

    void addNewCard(const CardType& cardType = Basic);

    bool payWithCard(const Card& card, float amount, const Currency& currency);

    bool haveCard(const Card& card) const;

    Tranzactie tryToMakeTransaction(std::shared_ptr<Account>& recipientAccount, float amount,
        const Currency& currency);

    const std::vector<Card> getCards();
};

#endif
