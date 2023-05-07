#ifndef SAVINGACCOUNT_HPP
#define SAVINGACCOUNT_HPP

#include <iostream>
#include <random.hpp>
#include <unordered_map>
#include <vector>

#include "Card.hpp"
#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "Account.hpp"

class SavingAccount: public Account {
    static float interestRate;
    float taxToUseMoney = 0.1;
public:
    SavingAccount() : Account() {
        std::cout << "Constr saving account\n";
    }

    /*std::shared_ptr<Account> clone() const override { 
        return std::make_shared<SavingAccount>(*this);
    };*/

    bool payWithCard(const Card& card, float amount, const Currency& currency) override {
        float amountAfterTax = amount + amount * taxToUseMoney;
        if (haveCard(card) && haveAmountOfCurrency(amountAfterTax, currency)) {
            currencyAccount[currency] -= amount;
            return true;
        }
        return false;
    }
};

#endif
