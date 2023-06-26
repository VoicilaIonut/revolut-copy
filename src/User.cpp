#include "../headers/User.hpp"

#include <iostream>
#include <memory>
#include <utility>

#include "../headers/Card.hpp"
#include "../headers/Tranzactie.hpp"
#include "../headers/DebitAccount.hpp"

bool User::checkCnp(const std::string& testCnp) {
  if (cnp == testCnp) {
    return true;
  }
  return false;
}

std::vector<std::shared_ptr<Account>> User::getAccounts() { return accounts; }

User::User() = default;

User::User(const std::string& nume_, const std::string& cnp_,
  const std::string& email_, const std::string& numarTelefon)
  : nume(nume_), cnp(cnp_), email(email_), numarTelefon(numarTelefon) {
  std::cout << "Constructor utilizator:\n" << *this << '\n';
}

User::User(const User& other)
  : nume(other.nume), cnp(other.cnp), email(other.email),
  numarTelefon(other.numarTelefon) {
  accounts.clear();
  for (const auto& account : other.accounts) {
    accounts.emplace_back(account->clone());
  }
  std::cout << "Constructor de copiere.\n";
}

User& User::operator=(User other) {
  swap(*this, other);
  return *this;
}

bool User::operator==(const User& other) {
  return this->cnp == other.cnp;
}

void swap(User& user1, User& user2) {
  using std::swap;
  swap(user1.nume, user2.nume);
  swap(user1.cnp, user2.cnp);
  swap(user1.email, user2.email);
  swap(user1.numarTelefon, user2.numarTelefon);
  swap(user1.accounts, user2.accounts);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "Nume utilizator: " << user.nume << '\n';
  // os << "User cnp: " << user.cnp << '\n';
  // os << "User email: " << user.email << '\n';
  // os << "User numar telefon: " << user.numarTelefon << '\n';
  if (user.accounts.empty()) {
    os << "Utilizatorul nu detine conturi.\n";
  } else {
    os << "Conturile utilizatorului: \n";
    for (auto account : user.accounts) {
      os << *account << '\n';
    }
  }
  return os;
}

User::~User() {
  std::cout << "Distrugere utilizator: " << nume << ", cu un numar de " << accounts.size() << " conturi detinute.\n";
}

void User::createAccount(const std::string& typeOfAccount) {
  if (typeOfAccount == "Savings") {
    accounts.emplace_back(std::make_shared<SavingAccount>());
  } else if (typeOfAccount == "Debit") {
    accounts.emplace_back(std::make_shared<DebitAccount>());
  } else {
    std::cout << "Nu s-a gasit un tipul de cont specificat.\n";
  }
}

void User::removeAccount(const int& accountIndex) {
  if (accountIndex < 0 || accountIndex >= (int)accounts.size()) {
    return;
  }
  accounts.erase(accounts.begin() + accountIndex);
}

bool User::tryToAddNewCardWithCnp(const std::string& cnpTry, std::shared_ptr<Account>& account) {
  if (checkCnp(cnpTry)) {
    account->addNewCard(nume);
    return true;
  }
  return false;
}

bool User::checkUserWithEmailAndCnp(const std::string& email_, const std::string& cnp_) const {
  return (email == email_ && cnp == cnp_);
}

std::string User::getName() const {
  return nume;
}

// std::shared_ptr<Account> User::getAccountWithIban(std::string& iban) const {
//   return std::find(accounts.begin(), accounts.end(), iban);
// };


std::shared_ptr<Account> User::getAccountWithIban(const std::string& iban) const {
  for (auto& account : accounts) {
    if (account->checkIban(iban)) {
      return account;
    }
  }
  return nullptr;
}