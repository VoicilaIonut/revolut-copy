#ifndef ACCOUNTPROXY_HPP
#define ACCOUNTPROXY_HPP

#include "Server.hpp"
#include "Tranzactie.hpp"
#include <memory>

class AccountProxy {
    std::shared_ptr<Account> account;
    Card card;

public:
    AccountProxy(std::shared_ptr<Account> account_, const Card& card_) : account(account_), card(card_) {};

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
        if (account->haveCard(card)) {
            if (account->payWithCard(card, amount, currency)) {
                std::cout << "Allowed\n";
            }
        } else {
            std::cout << "Not allowed\n";
        }
    }

    template <typename T>
    std::enable_if_t<std::is_arithmetic<T>::value, void> makeTransaction(std::shared_ptr<Account>& recipientAccount, T amount, const Currency& currency) {
        if (std::is_arithmetic<decltype(amount)>::value) {
            account->tryToMakeTransaction(recipientAccount, amount, currency);
            std::cout << "Allowed\n";
        }
        std::cout << "Not allowed\n";
    }
};

#endif 