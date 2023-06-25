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

    AccountProxy accountProxy = AccountProxy(accountTestUser1, carduri_test_user.back());
    try {
        accountProxy.pay(1, RON);
    } catch (CardError& err) {
        std::cout << err.what() << '\n';
    }
    accountProxy.makeTransaction(accountTestUser2, 0, RON);

    Tranzactie<int> test_tranzactie =
        accountTestUser1->tryToMakeTransaction(accountTestUser2, 1000, RON);
    std::cout << "Tranzactie fara taxe pentru contul debit pentru: \n" << test_tranzactie;

    Tranzactie<float> test_tranzactie1 =
        accountTestUser1->tryToMakeTransaction(accountTestUser2, (float)0.1, RON);
    std::cout << "Tranzactie fara taxe pentru contul debit pentru: \n" << test_tranzactie1;

    Tranzactie<double> test_tranzactie2 =
        accountTestUser1->tryToMakeTransaction(accountTestUser2, (double)0.999999, RON);
    std::cout << "Tranzactie fara taxe pentru contul debit pentru: \n" << test_tranzactie2;
}

int main() {
    test();
    Server server;
    server.outUsers();
    server.start();
    return 0;
}