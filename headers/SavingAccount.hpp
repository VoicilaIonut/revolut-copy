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
    float taxToTransfer = 0.1f;
    float taxToWithdraw = 0.2f;

    void print(std::ostream& os) const override;

    float calculatePayAmountWithTax(const float& amount) const override;

    float calculateWithdraw(const float& amount) const override;
public:
    SavingAccount();

    std::shared_ptr<Account> clone() const override;

    static float computeValueWithInterestRate(float value);
};

#endif
