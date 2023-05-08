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

class SavingAccount : public Account {
    static float interestRate;
    float taxToUseMoney = 0.1f;

    void print(std::ostream& os) const override;

public:
    SavingAccount();

    std::shared_ptr<Account> clone() const override;

    bool payWithCard(const Card& card, float amount, const Currency& currency) override;

    static float computeValueWithInterestRate(float value);
};

#endif
