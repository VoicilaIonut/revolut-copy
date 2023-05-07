#include "../headers/SavingAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"


bool SavingAccount::payWithCard(const Card& card, float amount, const Currency& currency) {
        float amountAfterTax = amount + amount * taxToUseMoney;
        if (haveCard(card) && haveAmountOfCurrency(amountAfterTax, currency)) {
            currencyAccount[currency] -= amount;
            return true;
        }
        return false;
    } 