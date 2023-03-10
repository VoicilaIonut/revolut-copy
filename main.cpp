#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
// TODO change all variables name to English :)
// maybe clasa pentru bancomat?
// maybe loan class

enum Currency {
    RON,
    EUR,
    USD
};

class Card {
    std::string cod, data_expirare, cvv; // maybe import a date type
    
public:
    Card() = default;

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        // TODO: add all parameters
        os << "Card cod: " << card.cod;
        return os;
    }

    Card& operator=(const Card& card) {
        // TODO: add all parameters
        cod = card.cod;
        std::cout << "operator= copiere Card\n";
        return *this;
    }
    ~Card() {
        std::cout << "Destroing card\n";
    }

};

/*
User main class:
Need: name, cnp, iban, numar_telefon
Can have: multiple currency, multiple cards (normal, bronze, silver, golden, platinum) TODO (i should add an enum here but idk how yet)
*/
class User {
    std::string nume, cnp, iban, email, numar_telefon;
    std::unordered_map<Currency, float> currencyAccount; // maybe create a vector instead of a hash table for tests
    std::vector<Card> carduri = {};                      // this should be optional

public:
    User() = default;

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        // TODO: add all parameters
        os << "User name: " << user.nume;
        return os;
    }

    User& operator=(const User& user) {
        // TODO: add all parameters
        nume = user.nume;
        std::cout << "operator= copiere User\n";
        return *this;
    }
    
    ~User() {
        std::cout << "Destroing User\n";
    }
   
    /*
    TODO add functions for:
    exchange
    adaugare card
    plataCard
    retragere
    */
};

class AppAccount {
    User user;
    std::string password;

public:
    AppAccount() = default;
    friend std::ostream& operator<<(std::ostream& os, const AppAccount& appAccount) {
        // TODO: add all parameters
        os << "User account: " << appAccount.user;
        return os;
    }

    AppAccount& operator=(const AppAccount& appAccount) {
        // TODO: add all parameters
        user = appAccount.user;
        std::cout << "operator= copiere AppAccount\n";
        return *this;
    }

    ~AppAccount() {
        std::cout << "Destroing AppAccount\n";
    }
};

class Tranzactie {
    User user1, user2; // the withdraws are made between the company account and the user account
    float value;
    Currency currency;
    bool realizata;

public:
    Tranzactie() = default;

    friend std::ostream& operator<<(std::ostream& os, const Tranzactie& tranzactie) {
        // TODO: add all parameters
        os << "User1: " << tranzactie.user1 << " - User2 " << tranzactie.user2;
        return os;
    }

    Tranzactie& operator=(const Tranzactie& tranzactie) {
        // TODO: add all parameters
        user1 = tranzactie.user1;
        user2 = tranzactie.user2;
        std::cout << "operator= copiere Tranzactie\n";
        return *this;
    }

    ~Tranzactie() {
        std::cout << "Destroing Tranzactie\n";
    }
};

int main() {
    std::cout << "Hello, world!\n";
    return 0;
}
