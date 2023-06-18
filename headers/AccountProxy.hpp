#ifndef CARDPROXY_HPP
#define CARDPROXY_HPP

#include "Server.hpp"
#include <memory>

class CardProxy {
    std::shared_ptr<Account> account;
    Card card;

    void printResponse(const bool& response) {
        if (response) {
            std::cout << "Allowed\n";
        } else {
            std::cout << "Not allowed\n";
        }
    };

public:
    CardProxy(std::shared_ptr<Account> account_, const Card& card_) : account(account_), card(card_) {};

    void pay(const float amount, const Currency& currency) {
        bool answer = false;
        if (account->haveCard(card)) {
            try {
                answer = account->payWithCard(card, amount, currency);
            } catch (ExpiredCard& err) {
                std::cout << err.what() << '\n';
            }
        }
        printResponse(answer);
        if (answer) {
            std::cout << "Paid " << amount << " " << stringCurrency[currency] << '\n';
        }
    }
};

#endif 