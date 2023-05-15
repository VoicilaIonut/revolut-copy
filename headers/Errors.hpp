#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Currencies.hpp"

class AppError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class AccountError : public AppError {
public:
    explicit AccountError(const std::string& mesaj) : AppError(std::move(mesaj)) {}
};

class NoAmountOfMoneyInCurrency : public AccountError {
public:
    explicit NoAmountOfMoneyInCurrency(const float amount, const Currency& currency) :
        AccountError("Nu aveti suma de " + std::to_string(amount) + " " + stringCurrency[currency] + " in contul dvs!.") {}
};


class CardError : public AppError {
public:
    explicit CardError(const std::string& mesaj) : AppError(std::move(mesaj)) {}
};

class ExpiredCard : public CardError {
public:
    explicit ExpiredCard() :
        CardError("Cardul pe care incercati sa il folositi este expirat!") {}
};

class ServerError : public AppError {
public:
    explicit ServerError(const std::string& mesaj) : AppError(std::move(mesaj)) {}
};

class ExitChooserServer : public ServerError {
public:
    explicit ExitChooserServer() :
        ServerError("Exit executat din Server Chooser") {}
};

class NoRegexFoundServer : public ServerError {
public:
    explicit NoRegexFoundServer(const std::string& option) :
        ServerError("Not regex found for the option: " + option) {}
};
