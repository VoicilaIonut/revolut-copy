#include "../headers/SavingAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"

float SavingAccount::interestRate = 0.05f;

void SavingAccount::print(std::ostream& os) const {
    os << "Tipul contului: Cont de economii.\n";
    os << "Taxa pentru a efectua o retragere: " << taxToWithdraw << '\n';
    os << "Taxa pentru a utiliza (a transfera sau a face o plata cu) o suma de bani: " << taxToTransfer << '\n';
}

SavingAccount::SavingAccount() : Account() {
    std::cout << "Constructor cont de ecnomii.\n";
}

std::shared_ptr<Account> SavingAccount::clone() const {
    std::cout << "Clonare cont de ecnomii.\n";
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