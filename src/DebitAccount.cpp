#include "../headers/DebitAccount.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"


void DebitAccount::print(std::ostream& os) const {
    os << "Type: Debit Account\n";
}

DebitAccount::DebitAccount() : Account() {
    std::cout << "Constr debit account\n";
}

std::shared_ptr<Account> DebitAccount::clone() const {
    std::cout << "clonare debit account\n";
    return std::make_shared<DebitAccount>(*this);
}

float DebitAccount::calculatePayAmountWithTax(const float& amount) const {
    return amount;
}

float DebitAccount::calculateWithdraw(const float& amount) const {
    return amount;
}