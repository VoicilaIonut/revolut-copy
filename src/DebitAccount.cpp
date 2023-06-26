#include "../headers/DebitAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"


void DebitAccount::print(std::ostream& os) const {
    os << "Tip: Debit.\n";
}

DebitAccount::DebitAccount() : Account() {
    std::cout << "Constructor cont debit.\n";
}

std::shared_ptr<Account> DebitAccount::clone() const {
    std::cout << "Clonare cont debit.\n";
    return std::make_shared<DebitAccount>(*this);
}

float DebitAccount::calculatePayAmountWithTax(const float& amount) const {
    return amount;
}

float DebitAccount::calculateWithdraw(const float& amount) const {
    return amount;
}