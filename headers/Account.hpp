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

class Account {
protected:
    std::string iban;
    std::unordered_map<Currency, float> currencyAccount = {};
    std::vector<Card> carduri = {};

    Account(const Account& other) = default;
    Account& operator=(const Account& other) = default;

    bool haveCurrency(const Currency& currency);

    bool haveAmountOfCurrency(float amount, const Currency& currency);

    bool haveCard(const Card& card_try);

    std::string generareIban(); 
public:
    Account();
    virtual std::shared_ptr<Account> clone () const = 0;
    
    virtual ~Account() = default;

    friend std::ostream& operator<<(std::ostream& os, const Account& user);

    void addFunds(float amount, const Currency& currency);

    bool exchange(float amount, const Currency& currencyFrom,
        const Currency& currencyTo);

    bool withdrawal(float amount, const Currency& currency);

    void addNewCard();

    // bool payWithCard(const Card& card, float amount, const Currency& currency);
    virtual bool payWithCard(const Card& card, float amount, const Currency& currency) = 0;

    Tranzactie tryToMakeTransaction(std::shared_ptr<Account>& recipientAccount, float amount,
        const Currency& currency);

    const std::vector<Card> getCards();
};

#endif
