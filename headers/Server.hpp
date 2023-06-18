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

class Server {
    static std::vector<User> users;
    static std::unordered_map<std::string, std::vector<std::string> > menuOptions;
    // static std::unordered_map<std::string, std::vector<std::string>> inputs;
    static std::unordered_map<std::string, std::regex> regexRules;
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
public:
    void start();

    void outUsers() const;
};

#endif