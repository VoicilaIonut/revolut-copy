#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class AppError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class AccountError : public AppError {
public:
    explicit AccountError(const std::string& mesaj) : AppError(std::move(mesaj)) { }
};

class UserError : public AppError { 
public:
    explicit UserError(const std::string& mesaj) : AppError(std::move(mesaj)) { }
};

class NoAmountOfMoney: public AccountError {
public:
    explicit NoAmountOfMoney(const std::string& mesaj) : 
    AccountError("Nu aveti suma de bani in contul dvs!.") {}
};

class NoAmountOCurrency: public AccountError {
public:
    explicit NoAmountOCurrency(const std::string& mesaj) : 
    AccountError("Nu aveti currency-ul specificat in contul dvs. Depozitiati sau folositi exchange-ul!") {}
};

class InvalidCard :public AccountError {
    explicit InvalidCard(const std::string& mesaj) : AccountError("Cardul specificat este invalid.") {}
};

class InvalidCurrency :public AccountError {
    explicit InvalidCurrency(const std::string& currency) : AccountError("Currency ul " + currency + " nu este disponibil inca.") {}
};

class InvalidCnp :public UserError {
    explicit InvalidCnp(const std::string& mesaj) : UserError("CNP-ul introdus nu este corect.") {}
};

