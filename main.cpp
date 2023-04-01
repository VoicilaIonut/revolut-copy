#include "headers/Card.hpp"
#include "headers/Currencies.hpp"
#include "headers/User.hpp"
#include "headers/Tranzactie.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>


// maybe clasa pentru bancomat?
// maybe loan class

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
