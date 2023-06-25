#ifndef ACCOUNTPROXY_HPP
#define ACCOUNTPROXY_HPP

#include "Server.hpp"
#include "Tranzactie.hpp"
#include <memory>

class AccountProxy {
    std::shared_ptr<Account> account;
    std::shared_ptr<Card> card;

public:
    AccountProxy(std::shared_ptr<Account> account_, std::shared_ptr<Card> card_) : account(account_), card(card_) {};

    AccountProxy(const AccountProxy& other) : account(other.account->clone()), card(other.card) {}

    AccountProxy& operator=(AccountProxy other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(AccountProxy& user1, AccountProxy& user2) {
        using std::swap;
        swap(user1.account, user2.account);
        swap(user1.card, user2.card);
    }

    // Throws ExpiredCard if called with a expired card because it calls payWithCard. 
    void pay(const float amount, const Currency& currency) {
        if (account->haveCard(*card)) {
            if (account->payWithCard(*card, amount, currency)) {
                std::cout << "Plata permisa si efectuata cu succes\n";
            } else {
                std::cout << "Plata nu s-a putut efectua\n";
            }
        } else {
            std::cout << "Operatie nepermisa!\n";
        }
    }

    template <typename T>
    void makeTransaction(std::shared_ptr<Account>& recipientAccount, T amount, const Currency& currency) {
        if (std::is_arithmetic<decltype(amount)>::value) {
            std::cout << "Tranzactie permisa\n";
            auto transaction = account->tryToMakeTransaction(recipientAccount, amount, currency);
            std::cout << "Detalii tranzactie: \n" << transaction << '\n';
            return;
        }
        std::cout << "Tranzactie nepermisa\n";
    }
};

#endif 