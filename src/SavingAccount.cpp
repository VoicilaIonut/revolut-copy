#include "../headers/SavingAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"


float SavingAccount::interestRate = 0.05f;

void SavingAccount::print(std::ostream& os) const {
    os << "Type: Saving Account\n";
    os << "Tax to use the money: " << taxToUseMoney << '\n';
}

SavingAccount::SavingAccount() : Account() {
    std::cout << "Constr saving account\n";
}

std::shared_ptr<Account> SavingAccount::clone() const {
    std::cout << "clonare saving account\n";
    return std::make_shared<SavingAccount>(*this);
}

bool SavingAccount::payWithCard(const Card& card, float amount, const Currency& currency) {
    float amountAfterTax = amount + amount * taxToUseMoney;
    if (haveCard(card) && haveAmountOfCurrency(amountAfterTax, currency)) {
        currencyAccount[currency] -= amountAfterTax;
        return true;
    }
    return false;
}

float SavingAccount::computeValueWithInterestRate(float value) {
    return value + value * interestRate;
}