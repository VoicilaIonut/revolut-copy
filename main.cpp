#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <random.hpp>
// TODO change all variables name to English :)
// maybe clasa pentru bancomat?
// maybe loan class

enum Currency {
    RON,
    EUR,
    USD
};

class Tranzactie;
class Card {
    std::string cod, dataExpirare, cvv; // maybe import a date type

    const std::string generateCod() {
        using Random = effolkronium::random_static;
        return  std::to_string(Random::get(1000, 9999)) + ' ' + 
                std::to_string(Random::get(1000, 9999)) + ' ' + 
                std::to_string(Random::get(1000, 9999)) + ' ' +
                std::to_string(Random::get(1000, 9999));
    }

    const std::string generateDataExpirare() {
        std::string dataExpirareGenerated = "01/06/2025"; // TODO: Add a random function to generate the date.
        return dataExpirareGenerated;
    }

    const std::string generateCvv() {
        using Random = effolkronium::random_static;
        std::string cvvGenerated =  std::to_string(Random::get(100, 999)); // TODO: Add a random function to generate the cvv.
        return cvvGenerated;
    }

public:
    Card(): cod(generateCod()), dataExpirare(generateDataExpirare()), cvv(generateCvv()) {
        std::cout << "Const " << *this << '\n';
    }

    Card(const Card& other): cod(other.cod), dataExpirare(other.dataExpirare), cvv(other.cvv) {
        std::cout << "Constr de copiere" << *this << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.cod << " " << card.dataExpirare << " " << card.cvv << '\n';
        return os;
    }

    Card& operator=(const Card& other) {
        std::cout << "operator= " << *this << "\n";
        cod = other.cod;
        dataExpirare = other.dataExpirare;
        cvv = other.cvv;
        return *this;
    }

    friend bool operator==(const Card& lhs, const Card& rhs) {
        return lhs.cod == rhs.cod && lhs.dataExpirare == rhs.dataExpirare && lhs.cvv == rhs.cvv;
    }

    ~Card() {
        std::cout << "Destroing card" << *this << "\n";
    }

    // bool checkCod(const std::string& codTry) {
    //     if (cod == codTry) {
    //         return true;
    //     }
    //     return false;
    // }

    // bool checkDataExpirare(const std::string& dataExpirareTry) {
    //     if (dataExpirare == dataExpirareTry) {
    //         return true;
    //     }
    //     return false;
    // }

    // bool checkCvv(const std::string& cvvTry) {
    //     if (cvv == cvvTry) {
    //         return true;
    //     }
    //     return false;
    // }
    // const std::string getCod() {
    //     return cod;
    // }
    // const std::string getDataExpirare() {
    //     return dataExpirare;
    // }
    // const std::string getCvv() {
    //     return cvv;
    // }
};

class User {
    std::string nume, cnp, iban, email, numarTelefon;
    std::unordered_map<Currency, float> currencyAccount = {};
    std::vector<Card> carduri = {};

    bool haveCurrency(const Currency& currency) {
        if (currencyAccount.find(currency) != currencyAccount.end()) {
            return true;
        }
        return false;
    }

    bool haveAmountOfCurrency(float amount, const Currency& currency) {
        if (haveCurrency(currency) && currencyAccount[currency] >= amount) {
            return true;
        }
        return false;
    }
    bool checkCnp(const std::string& testCnp) {
        if (cnp == testCnp) {
            return true;
        }
        return false;
    }

    bool haveCard(const Card& card_try) {
        for (const Card& card : carduri) {
            if (card == card_try) {
                return true;
            }
        }
        return false;
    }

public:
    User() = default;
    User(const std::string& nume_, const std::string& cnp_, const std::string& iban_, const std::string& email_, const std::string& numarTelefon):
        nume(nume_), cnp(cnp_), iban(iban_), email(email_), numarTelefon(numarTelefon) {
        std::cout << "User constructor\n" << *this;
    }

    User(const User& other): nume(other.nume), cnp(other.cnp), iban(other.iban), email(other.email), numarTelefon(other.numarTelefon), currencyAccount(other.currencyAccount), carduri(other.carduri) {
        std::cout << "Constr de copiere" << *this << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "User name: " << user.nume << '\n';
        os << "User cnp: " << user.cnp << '\n';
        os << "User iban: " << user.iban << '\n';
        os << "User email: " << user.email << '\n';
        os << "User numar telefon: " << user.numarTelefon << '\n';
        if (user.currencyAccount.empty()) {
            os << "User has no currency accounts\n";
        }
        else {
            for (auto it = user.currencyAccount.begin(); it != user.currencyAccount.end(); ++it) {
                os << "User currency: " << it->first << " " << it->second << '\n';
            }
        }
        if (user.carduri.empty()) {
            os << "User has no cards\n";
        }
        else {
            for (auto it = user.carduri.begin(); it != user.carduri.end(); ++it) {
                os << "User carduri: " << *it << '\n';
            }
        }
        return os;
    }

    User& operator=(const User& other) {
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

    ~User() {
        std::cout << "Destroing User" << *this << "\n" << *this;
    }

    const std::vector<Card> getCardsWithCnp(const std::string& cnpTry) {
        if (checkCnp(cnpTry)) {
            return carduri;
        }
        return {};
    }


    void addFunds(float amount, const Currency& currency) {
        if (haveCurrency(currency)) {
            currencyAccount[currency] += amount;
        }
        else {
            currencyAccount[currency] = amount;
        }
    }

    bool exchange(float amount, const Currency& currencyFrom, const Currency& currencyTo) {
        if (haveAmountOfCurrency(amount, currencyFrom)) {
            currencyAccount[currencyFrom] -= amount;
            addFunds(amount, currencyTo);
            return true;
        }
        return false;
    }

    bool withdrawal(float amount, const Currency& currency) {
        if (haveAmountOfCurrency(amount, currency)) {
            currencyAccount[currency] -= amount;
            return true;
        }
        return false;
    }

    bool tryToAddNewCardWithCnp(const std::string& cnpTry) {
        if (checkCnp(cnpTry)) {
            carduri.push_back(Card());
            return true;
        }
        return false;
    }

    bool payWithCard(const Card& card, float amount, const Currency& currency) {
        if (haveCard(card) && haveAmountOfCurrency(amount, currency)) {
            currencyAccount[currency] -= amount;
            return true;
        }
        return false;
    }

    Tranzactie tryToMakeTransaction(User& recipientUser, float amount, const Currency& currency);
};

// Tema2
// class AppAccount: public User {
//     std::string username, password;

//     std::string encryptPassword(const std::string& actualPassword) {
//         std::string encryptedPassword = actualPassword; // TODO encrypt password.
//         return encryptedPassword;
//     }
// public:
//     AppAccount(const std::string& username_, const std::string& password_): username(username_), password(encryptPasswordpassword_) {
//         std::cout << "AppAccount constructor\n" << *this << '\n';
//     }

//     AppAccount(const AppAccount& other): username(other.username), password(other.password) {
//         std::cout << "Constr de copiere" << *this << "\n";
//     }

//     friend std::ostream& operator<<(std::ostream& os, const AppAccount& appAccount) {
//         os << "Username: " << appAccount.username << '\n';
//         os << "Encrypted password: " << [REDACTED] << '\n';
//         return os;
//     }

//     AppAccount& operator=(const AppAccount& other) {
//         std::cout << "operator=  " << *this << "\n";
//         username = other.username;
//         password = other.password;
//         return *this;
//     }

//     ~AppAccount() {
//         std::cout << "Destroying AppAccount" << *this << "\n";
//     }

//     bool verifyPassword(const std::string& passwordTry) {
//         if (passwordTry == password) {
//             return true;
//         }
//         return false;
//     }

//     bool schimbaParolaCuCnp(const std::string& testCnp, const std::string& newPassword) {
//         if (checkCnp(testCnp)) {
//             password = newPassword;
//             return true;
//         }
//         return false;
//     }

//     bool tryToAddNewCard(const std::string& passwordTry) {
//         if (verifyPassword(passwordTry)) {
//             carduri.push_back(Card());
//             return true;
//         }
//         return false;
//     }
// };

// the withdraws are made between the company account and the user account
class Tranzactie {
    std::string ibanSender, ibanRecipient;
    float value;
    Currency currency;
    bool realizata;

public:
    Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient, float value_, const Currency& currency_, bool realizata_): ibanSender(ibanSender), ibanRecipient(ibanRecipient), value(value_), currency(currency_), realizata(realizata_) {
        std::cout << "Tranzactie constructor\n" << *this << '\n';
    }

    Tranzactie(const Tranzactie& other): ibanSender(other.ibanSender), ibanRecipient(other.ibanRecipient), value(other.value), currency(other.currency), realizata(other.realizata) {
        std::cout << "Constr de copiere" << *this << "\n";
    }


    friend std::ostream& operator<<(std::ostream& os, const Tranzactie& tranzactie) {
        os << "ibanSender: " << tranzactie.ibanSender << " ibanRecipient: " << tranzactie.ibanRecipient << '\n';
        os << "Value: " << tranzactie.value << '\n';
        os << "Currency: " << tranzactie.currency << '\n';
        os << "Realizata: " << tranzactie.realizata << '\n';
        return os;
    }

    Tranzactie& operator=(const Tranzactie& tranzactie) {
        std::cout << "operator= " << *this << "\n";
        ibanSender = tranzactie.ibanSender;
        ibanRecipient = tranzactie.ibanRecipient;
        value = tranzactie.value;
        currency = tranzactie.currency;
        realizata = tranzactie.realizata;
        return *this;
    }

    ~Tranzactie() {
        std::cout << "Destroing Tranzactie" << *this << "\n";
    }
};


Tranzactie User::tryToMakeTransaction(User& recipientUser, float amount, const Currency& currency) {
    bool realizata = haveAmountOfCurrency(amount, currency);
    if (realizata) {
        currencyAccount[currency] -= amount;
        recipientUser.addFunds(amount, currency);
    }
    return Tranzactie(iban, recipientUser.iban, amount, currency, realizata);
}


std::unordered_map<std::string, std::string> creareDateUser() {
    std::unordered_map<std::string, std::string> dateUser;
    dateUser["nume"] = "ion";
    dateUser["cnp"] = "5020927000000";
    dateUser["iban"] = "42069";
    dateUser["email"] = "test@example";
    dateUser["numarTelefon"] = "0725293000";
    return dateUser;
}


int main() {
    // Consider urmatorii vectori baza de date.
    std::vector<User> users = {};
    std::vector<Tranzactie> tranzactii = {};
    // std::vector<AppAccount> appAccounts = {};
    // ----------------------------------------------------------------
    std::unordered_map<std::string, std::string> dateUser = creareDateUser();
    User test_user(dateUser["nume"], dateUser["cnp"], dateUser["iban"], dateUser["email"], dateUser["numarTelefon"]);

    test_user.addFunds(1003, RON);
    test_user.withdrawal(1, RON);
    test_user.exchange(1, RON, USD);
    test_user.tryToAddNewCardWithCnp(dateUser["cnp"]);

    std::vector<Card> carduri_test_user = test_user.getCardsWithCnp(dateUser["cnp"]);
    test_user.payWithCard(carduri_test_user.back(), 1, RON);
    tranzactii.push_back(test_user.tryToMakeTransaction(test_user, 1000, RON));
    users.push_back(test_user);
    // for (auto x : tranzactii) {
    //     std::cout << x << '\n';
    // }

    // std::cout << "Hello, world!\n";

    // std::unordered_map<std::string, std::string> dateUser = creareDateUser();

    // Card test_card("1234 56789", "27/09/1900", "420");
    // std::cout << test_card << '\n';

    // User test_user(dateUser["nume"], dateUser["cnp"], dateUser["iban"], dateUser["email"], dateUser["numarTelefon"]);
    // std::cout << "test_user: " << test_user << '\n';

    // AppAccount app_account(test_user, "1234");
    // std::cout << "AppAccount: " << app_account << '\n';

    // Tranzactie test_tranzactie(test_user, test_user, float(12.1), RON, true);
    // std::cout << "test_tranzactie: " << test_tranzactie << '\n';

    return 0;
}
