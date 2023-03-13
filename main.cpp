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
    Card(std::string cod, std::string data_expirare_, std::string cvv_) : cod(cod), data_expirare(data_expirare_), cvv(cvv_) {
        std::cout << *this  << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.cod << " " << card.data_expirare << " " << card.cvv << '\n';
        return os;
    }

    Card& operator=(const Card& other) {
        cod = other.cod;
        data_expirare = other.data_expirare;
        cvv = other.cvv;
        std::cout << "operator= copiere Card" << *this << "\n";
        return *this;
    }
    ~Card() {
        std::cout << "Destroing card" << *this << "\n";
    }

};

/*
User main class:
Need: name, cnp, iban, numar_telefon
Can have: multiple currency, multiple cards (normal, bronze, silver, golden, platinum) 
*/
class User {
    std::string nume, cnp, iban, email, numar_telefon;
    std::unordered_map<Currency, float> currencyAccount = {}; 
    std::vector<Card> carduri = {}; 

public:
    User()=default;

    User(const std::string& nume_, std::string cnp_, std::string iban_, std::string email_, std::string numar_telefon_) : nume(nume_), cnp(cnp_), email(email_), numar_telefon(numar_telefon_) {
        std::cout << "User constructor\n" << *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "User name: " << user.nume << '\n';
        os << "User cnp: " << user.cnp << '\n';
        os << "User iban: " << user.iban << '\n';
        os << "User email: " << user.email << '\n';
        os << "User numar telefon: " << user.numar_telefon << '\n';
        if (user.currencyAccount.empty()) {
            os << "User has no currency accounts\n";
        } else {
            for (auto it = user.currencyAccount.begin(); it != user.currencyAccount.end(); ++it) {
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

    User& operator=(const User& other) {
        std::cout << "operator= copiere " << *this << "\n";
        nume = other.nume;
        cnp = other.cnp;
        iban = other.iban;
        email = other.email;
        numar_telefon = other.numar_telefon;
        currencyAccount = other.currencyAccount;
        carduri = other.carduri;
        return *this;
    }
    
    ~User() {
        std::cout << "Destroing User\n" << *this;
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
    AppAccount(User user_, std::string password_) : user(user_), password(password_) { 
        std::cout << "AppAccount constructor\n" << *this << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const AppAccount& appAccount) {
        os << "User account: " << appAccount.user << '\n';
        os << "Encrypted password: " << appAccount.password << '\n';
        return os;
    }

    AppAccount& operator=(const AppAccount& other) {
        user = other.user;
        password = other.password;
        std::cout << "operator= copiere AppAccount\n";
        return *this;
    }

    ~AppAccount() {
        std::cout << "Destroing AppAccount" << *this << "\n";
    }
};

class Tranzactie {
    User user1, user2; // the withdraws are made between the company account and the user account
    float value;
    Currency currency;
    bool realizata;

public:
    Tranzactie(User user1_, User user2_, float value_, Currency currency_, bool realizata_) : user1(user1_), user2(user2_), value(value_), currency(currency_), realizata(realizata_) {
        std::cout << "Tranzactie constructor\n" << *this << '\n';
    }
    Tranzactie(User user1_, User user2_, float value_) : user1(user1_), user2(user2_), value(value_) {
        std::cout << "Tranzactie constructor\n" << *this << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const Tranzactie& tranzactie) {
        os << "User1: " << tranzactie.user1 << "\nUser2: " << tranzactie.user2 << '\n';
        os << "Value: " << tranzactie.value << '\n';
        os << "Currency: " << tranzactie.currency << '\n';
        os << "Realizata: " << tranzactie.realizata << '\n';
        return os;
    }

    Tranzactie& operator=(const Tranzactie& tranzactie) {
        user1 = tranzactie.user1;
        user2 = tranzactie.user2;
        value = tranzactie.value;
        currency = tranzactie.currency;
        realizata = tranzactie.realizata;
        std::cout << "operator= copiere Tranzactie\n";
        return *this;
    }

    ~Tranzactie() {
        std::cout << "Destroing Tranzactie" << *this << "\n";
    }
};


std::unordered_map<std::string, std::string> creareDateUser() {
    std::unordered_map<std::string, std::string> dateUser;
    dateUser["nume"] = "ion";
    dateUser["cnp"] = "5020927000000";
    dateUser["iban"] = "42069";
    dateUser["email"] = "test@example";
    dateUser["numar_telefon"] = "0725293000";
    return dateUser;
}


int main() {
    std::cout << "Hello, world!\n";
    
    std::unordered_map<std::string, std::string> dateUser = creareDateUser();

    Card test_card("1234 56789", "27/09/1900", "420");
    std::cout << test_card << '\n';

    User test_user(dateUser["nume"], dateUser["cnp"], dateUser["iban"], dateUser["email"], dateUser["numar_telefon"]);
    std::cout << "test_user: " << test_user <<  '\n';

    AppAccount app_account(test_user, "1234");
    std::cout << "AppAccount: " << app_account << '\n';
    
    Tranzactie test_tranzactie(test_user, test_user, 12.1, RON, true);
    std::cout << "test_tranzactie: " << test_tranzactie << '\n';

    return 0;
}
