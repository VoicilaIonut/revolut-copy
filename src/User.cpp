#include "../headers/User.hpp"

#include <iostream>
#include <memory>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"

bool User::checkCnp(const std::string &testCnp) {
  if (cnp == testCnp) {
    return true;
  }
  return false;
}

 std::vector<std::shared_ptr<Account>> User::getAccounts() { return accounts; }

User::User() = default;

User::User(const std::string &nume_, const std::string &cnp_,
           const std::string &email_, const std::string &numarTelefon)
    : nume(nume_), cnp(cnp_), email(email_), numarTelefon(numarTelefon) {
  std::cout << "User constructor\n" << *this;
}

User::User(const User &other)
    : nume(other.nume), cnp(other.cnp), email(other.email),
      numarTelefon(other.numarTelefon), accounts(other.accounts) {
  std::cout << "Constr de copiere" << *this << "\n";
}

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "User name: " << user.nume << '\n';
  // os << "User cnp: " << user.cnp << '\n';
  // os << "User email: " << user.email << '\n';
  // os << "User numar telefon: " << user.numarTelefon << '\n';
  os << "User accounts: \n";
  for (auto account : user.accounts) {
    os << *account << '\n';
  }
  return os;
}

User &User::operator=(const User &other) {
  std::cout << "operator= " << *this << "\n";
  nume = other.nume;
  cnp = other.cnp;
  email = other.email;
  numarTelefon = other.numarTelefon;
  accounts = other.accounts;
  return *this;
}

User::~User() { std::cout << "Destroing User" << *this << "\n" << *this; }

void User::createAccount(const std::string& typeOfAccount) {
    if (typeOfAccount == "Savings") 
        accounts.push_back(std::make_shared<SavingAccount>()); 
}

bool User::tryToAddNewCardWithCnp(const std::string &cnpTry, std::shared_ptr<Account>& account) {
  if (checkCnp(cnpTry)) {
    account->addNewCard();
    return true;
  }
  return false;
}
