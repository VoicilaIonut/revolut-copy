#include "../headers/SavingAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"

float SavingAccount::interestRate = 0.05f;

void SavingAccount::print(std::ostream& os) const {
    os << "Type: Saving Account\n";
    os << "Tax to withdraw the money: " << taxToWithdraw << '\n';
    os << "Tax to use (transfer/payments) the money: " << taxToTransfer << '\n';
}

SavingAccount::SavingAccount() : Account() {
    std::cout << "Constr saving account\n";
}

std::shared_ptr<Account> SavingAccount::clone() const {
    std::cout << "clonare saving account\n";
    return std::make_shared<SavingAccount>(*this);
}

float SavingAccount::calculatePayAmountWithTax(const float& amount) const {
    return amount + amount * taxToTransfer;
}

float SavingAccount::calculateWithdraw(const float& amount) const {
    return amount + amount * taxToWithdraw;
}

float SavingAccount::computeValueWithInterestRate(float value) {
    return value + value * interestRate;
}