#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Card.hpp"
#include "Tranzactie.hpp"
#include "Currencies.hpp"

class Card;

class User {
    std::string nume, cnp, iban, email, numarTelefon;
    std::unordered_map<Currency, float> currencyAccount = {};
    std::vector<Card> carduri = {};

    bool haveCurrency(const Currency& currency);

    bool haveAmountOfCurrency(float amount, const Currency& currency);

    bool checkCnp(const std::string& testCnp);

    bool haveCard(const Card& card_try);

public:
    User();
    
    User(const std::string& nume_, const std::string& cnp_, const std::string& iban_, const std::string& email_, const std::string& numarTelefon);

    User(const User& other);

    friend std::ostream& operator<<(std::ostream& os, const User& user);

    User& operator=(const User& other);

    ~User();

    const std::vector<Card> getCardsWithCnp(const std::string& cnpTry);


    void addFunds(float amount, const Currency& currency);

    bool exchange(float amount, const Currency& currencyFrom, const Currency& currencyTo);

    bool withdrawal(float amount, const Currency& currency);

    bool tryToAddNewCardWithCnp(const std::string& cnpTry);

    bool payWithCard(const Card& card, float amount, const Currency& currency);

    Tranzactie tryToMakeTransaction(User& recipientUser, float amount, const Currency& currency);
};

#endif