#ifndef DEBITACCOUNT_HPP
#define DEBITACCOUNT_HPP

#include <iostream>
#include <random.hpp>
#include <unordered_map>
#include <vector>

#include "Card.hpp"
#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "Account.hpp"

class DebitAccount : public Account {
    void print(std::ostream& os) const override;

    virtual float calculatePayAmountWithTax(const float& amount) const override;
public:
    DebitAccount();

    std::shared_ptr<Account> clone() const override;

};

#endif
