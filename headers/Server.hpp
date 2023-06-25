#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <map>
#include <regex>

#include "User.hpp"
#include "AccountProxy.hpp"

class Server {
    static std::vector<User> users;
    static std::unordered_map<std::string, std::vector<std::string> > menuOptions;
    // static std::unordered_map<std::string, std::vector<std::string>> inputs;
    static std::unordered_map<std::string, std::regex> regexRules;
    static std::unordered_map<std::string, std::string> helpForInputs;
    int idxUserActual = -1;
    bool userLogat = false;

    void printLine() const;

    void printOptions(const std::string& menu) const;

    std::string readAndValidateWithRegex(std::string valueName) const;

    std::string redirect();

    void registerr();

    void login();

    void logout();

    void addAccount(const std::string& typeOfAccount);

    void removeAccount();

    std::shared_ptr<Account> selectAccount() const;

    std::shared_ptr<Card> selectCard(const std::shared_ptr<Account> account) const;

    int selectCurrencyCode() const;

    int selectCardTypeCode() const;

    void addFundsToAccount();

    void addCard();

    void payWithCardWithProxy();

    void transferWithProxy();

    std::shared_ptr<Account> getAccountFromUsersWithNameAndIban(const std::string& name,const std::string& iban) const;
public:
    void start();

    void outUsers() const;
};

#endif