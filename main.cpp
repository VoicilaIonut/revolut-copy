#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "headers/Card.hpp"
#include "headers/Currencies.hpp"
#include "headers/Tranzactie.hpp"
#include "headers/User.hpp"
#include "headers/Account.hpp"
#include "headers/SavingAccount.hpp"
#include "headers/Errors.hpp"
#include "headers/Server.hpp"
#include "headers/CardTypes.hpp"
#include "headers/AccountProxy.hpp"

std::unordered_map<std::string, std::string> creareDateUser() {
    std::unordered_map<std::string, std::string> dateUser;
    dateUser["nume"] = "ion";
    dateUser["cnp"] = "4020927000000";
    // dateUser["iban"] = "42069";
    dateUser["email"] = "test@example";
    dateUser["numarTelefon"] = "0725293000";
    return dateUser;
}

void test() {
    std::unordered_map<std::string, std::string> dateUser = creareDateUser();

    User test_user1("Ion", "4020927000000", "test1@example", "0710000000");
    User copie_test_user1(test_user1);
    User test_user2("Gigel", "3020927000000", "test2@example", "0720000000");

    std::string accountTypeSavings = "Savings", accountTypeDebit = "Debit";
    test_user1.createAccount(accountTypeSavings);
    test_user2.createAccount(accountTypeDebit);

    std::shared_ptr<Account> accountTestUser1 = test_user1.getAccounts().front();
    std::shared_ptr<Account> accountTestUser2 = test_user2.getAccounts().front();

    std::cout << "Testare afisare Account: \n" << *accountTestUser1 << '\n';

    auto x = std::dynamic_pointer_cast<SavingAccount>(accountTestUser1);
    if (x != nullptr) {
        std::cout << "value with interest rate: " << x->computeValueWithInterestRate(1003) << '\n';
    }
    accountTestUser1->addFunds(1003, RON);

    // --- testare clonare
    std::shared_ptr<Account> cloneTest = accountTestUser1->clone();
    cloneTest->withdrawal(1002, RON);
    std::cout << "Testare clonare (trebuie sa dea diferit): \n" << *accountTestUser1 << '\n' << *cloneTest << "\n\n";
    //--- end testare clonare

    try {
        accountTestUser1->withdrawal(1, RON); // works
        accountTestUser1->exchange(1, RON, USD); // works
        accountTestUser1->withdrawal(10000000000.0f, RON); // fails
    } catch (NoAmountOfMoneyInCurrency& err) {
        std::cout << err.what() << '\n';
    }

    test_user1.tryToAddNewCardWithCnp(dateUser["cnp"], accountTestUser1);
    std::vector<Card> carduri_test_user = accountTestUser1->getCards();

    CardProxy cardProxy = CardProxy(accountTestUser1, carduri_test_user.back());
    cardProxy.pay(1, RON);

    Tranzactie test_tranzactie =
        accountTestUser1->tryToMakeTransaction(accountTestUser2, 1000, RON);
    std::cout << "Tranzactie fara taxe pentru contul debit pentru: \n" << test_tranzactie;
}

int main() {
    test();
    Server server;
    server.outUsers();
    server.start();
    return 0;
}

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