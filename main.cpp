#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "headers/Card.hpp"
#include "headers/Currencies.hpp"
#include "headers/Tranzactie.hpp"
#include "headers/User.hpp"

// maybe clasa pentru bancomat?
// maybe loan class

// Tema2
// class AppAccount: public User {
//     std::string username, password;

//     std::string encryptPassword(const std::string& actualPassword) {
//         std::string encryptedPassword = actualPassword; // TODO encrypt
//         password. return encryptedPassword;
//     }
// public:
//     AppAccount(const std::string& username_, const std::string& password_):
//     username(username_), password(encryptPasswordpassword_) {
//         std::cout << "AppAccount constructor\n" << *this << '\n';
//     }

//     AppAccount(const AppAccount& other): username(other.username),
//     password(other.password) {
//         std::cout << "Constr de copiere" << *this << "\n";
//     }

//     friend std::ostream& operator<<(std::ostream& os, const AppAccount&
//     appAccount) {
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

//     bool schimbaParolaCuCnp(const std::string& testCnp, const std::string&
//     newPassword) {
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

void test() {
    // Consider urmatorii vectori baza de date.
    std::vector<User> users = {};
    std::vector<Tranzactie> tranzactii = {};
    // ----------------------------------------

    std::unordered_map<std::string, std::string> dateUser = creareDateUser();

    User test_user1("Ion", "4020927000000", "1", "test1@example", "0710000000");
    users.push_back(test_user1);
    User test_user2("Gigel", "3020927000000", "2", "test2@example",
                    "0720000000");
    users.push_back(test_user2);

    test_user1.addFunds(1003, RON);
    test_user1.withdrawal(1, RON);
    test_user1.exchange(1, RON, USD);

    test_user1.tryToAddNewCardWithCnp(dateUser["cnp"]);
    std::vector<Card> carduri_test_user =
        test_user1.getCardsWithCnp(dateUser["cnp"]);
    test_user1.payWithCard(carduri_test_user.back(), 1, RON);

    Tranzactie test_tranzactie =
        test_user1.tryToMakeTransaction(test_user2, 1000, RON);
    tranzactii.push_back(test_tranzactie);

    for (auto x : tranzactii) {
        std::cout << x << '\n';
    }

    // AppAccount app_account(test_user, "1234");
    // std::cout << "AppAccount: " << app_account << '\n';
}

int main() {
    test();
    return 0;
}
