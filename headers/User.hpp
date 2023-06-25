#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Card.hpp"
#include "Currencies.hpp"
#include "Tranzactie.hpp"
#include "Account.hpp"
#include "SavingAccount.hpp"

class User {
    std::string nume, cnp, email, numarTelefon;
    std::vector<std::shared_ptr<Account>> accounts;

    bool checkCnp(const std::string& testCnp);

    // void changeEmail(const std::string &emailNew);

public:
    User();

    User(const std::string& nume_, const std::string& cnp_,
        const std::string& email_,
        const std::string& numarTelefon);

    User(const User& other);

    User& operator=(User other);

    bool operator==(const User& other);

    friend void swap(User& user1, User& user2);

    friend std::ostream& operator<<(std::ostream& os, const User& user);

    ~User();

    void createAccount(const std::string& typeOfAccount);

    void removeAccount(const int& accountIndex);

    std::vector<std::shared_ptr<Account>> getAccounts();

    bool tryToAddNewCardWithCnp(const std::string& cnpTry, std::shared_ptr<Account>& account);

    bool checkUserWithEmailAndCnp(const std::string& email_, const std::string& cnp_) const;

    std::string getName() const;

    //Returns nullptr if no account is found with this iban.
    std::shared_ptr<Account> getAccountWithIban(const std::string& iban) const;
};

#endif