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

class Tranzactie;
class Card {
    std::string cod, data_expirare, cvv; // maybe import a date type
    
    const std::string generateCod() {
        std::string cod = "420 124 125 126"; // TODO: Add a random function to generate the cod.
        return cod;
    }

    const std::string generateDataExpirare() {
        std::string data_expirare = "01/06/2025"; // TODO: Add a random function to generate the date.
        return data_expirare;
    }

    const std::string generateCvv() {
        std::string cvv = "123"; // TODO: Add a random function to generate the cvv.
        return cvv;
    }

public:
    Card(): cod(generateCod()), data_expirare(generateDataExpirare()), cvv(generateCvv()) {
        std::cout << "Const " << *this << '\n';
    }

    Card(const Card& other): cod(other.cod), data_expirare(other.data_expirare), cvv(other.cvv) {
        std::cout << "Constr de copiere" << *this << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.cod << " " << card.data_expirare << " " << card.cvv << '\n';
        return os;
    }

    Card& operator=(const Card& other) {
        std::cout << "operator= " << *this << "\n";
        cod = other.cod;
        data_expirare = other.data_expirare;
        cvv = other.cvv;
        return *this;
    }

    ~Card() {
        std::cout << "Destroing card" << *this << "\n";
    }

};

class User {
    std::string nume, cnp, iban, email, numarTelefon;
    std::unordered_map<Currency, float> currencyAccount = {};
    protected: std::vector<Card> carduri = {};

public:
    User()=default;
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

    const bool haveCurrency(const Currency& currency) {
        if (currencyAccount.find(currency) != currencyAccount.end()) {
            return true;
        }
        return false;
    }

    const bool haveAmountOfCurrency(float amount, const Currency& currency) {
        if (haveCurrency(currency) && currencyAccount[currency] >= amount) {
            return true;
        }
        return false;
    }
    const bool checkCnp(const std::string testCnp) {
        if (cnp == testCnp) {
            return true;
        }
        return false;
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

    Tranzactie tryToMakeTransaction(User& recipientUser, float amount, const Currency& currency);
    /*
    TODO add functions for:
    adaugare card
    plataCard
    */
};

class AppAccount: public User {
    std::string username, password;

public:
    AppAccount(const std::string& username_, const std::string& password_): username(username_), password(password_) {
        std::cout << "AppAccount constructor\n" << *this << '\n';
    }

    AppAccount(const AppAccount& other): username(other.username), password(other.password) {
        std::cout << "Constr de copiere" << *this << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const AppAccount& appAccount) {
        os << "Username: " << appAccount.username << '\n';
        os << "Encrypted password: " << appAccount.password << '\n';
        return os;
    }

    AppAccount& operator=(const AppAccount& other) {
        std::cout << "operator=  " << *this << "\n";
        username = other.username;
        password = other.password;
        return *this;
    }

    ~AppAccount() {
        std::cout << "Destroing AppAccount" << *this << "\n";
    }

    const bool verifyPassword(const std::string& passwordTry) {
        if (passwordTry == password) {
            return true;
        }
        return false;
    }

    bool schimbaParolaCuCnp(const std::string& testCnp, const std::string& newPassword) {
        if (checkCnp(testCnp)) {
            password = newPassword;
            return true;
        }
        return false;
    }

    bool tryToAddNewCard(const std::string& passwordTry) {
        if (verifyPassword(passwordTry)) {
            carduri.push_back(Card());
            return true;
        }
        return false;
    }
};

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
    // Consider urmatorii vectori date de baza.
    std::vector<User> users = {};
    std::vector<Tranzactie> tranzactii = {};
    std::vector<AppAccount> appAccounts = {};
    // ----------------------------------------------------------------
    std::unordered_map<std::string, std::string> dateUser = creareDateUser();
    User test_user(dateUser["nume"], dateUser["cnp"], dateUser["iban"], dateUser["email"], dateUser["numarTelefon"]);

    test_user.addFunds(1002, RON);
    test_user.withdrawal(1, RON);
    test_user.exchange(1, RON, USD);
    tranzactii.push_back(test_user.tryToMakeTransaction(test_user, 1000, RON));
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
