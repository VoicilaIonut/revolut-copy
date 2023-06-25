#include "../headers/Server.hpp"

#include <iostream>

#include "../headers/Card.hpp"
#include "../headers/User.hpp"
#include "../headers/Errors.hpp"

#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <map>
#include <regex>

std::vector<User> Server::users = {
    User{"tester", "1234567890123", "t@t", "0710000000"}
};

std::unordered_map<std::string, std::vector<std::string> > Server::menuOptions =
{
  { "Start", { "Autentificare", "Inregistrare", "Iesire"} },
  { "Profil", {"Executa un transfer", "Plateste cu cardul", "Adauga bani in cont", "Afiseaza detaliile conturilor mele", "Creeaza un cont nou", "Adauga un card nou unui cont", "Sterge un cont existent", "Deconectare", "Iesire"}},
  { "Creeaza un cont nou", {"Economii", "Debit"}}
};

std::unordered_map<std::string, std::regex> Server::regexRules =
{
    {"CNP", std::regex("^\\d{13}$")},
    {"Email", std::regex("^(.+)@(.+)$")},
    {"Numar de telefon", std::regex("^\\d{10}$")},
    {"Nume si prenume", std::regex("^[a-zA-Z ]+$")},
    {"Suma", std::regex("^(0|[1-9]\\d*)(\\.\\d+)?$")},
    {"Iban", std::regex("^[A-Z]{2}\\d{16}$")},
    {"optiunea", std::regex("^[0-9]+$")}
};

std::unordered_map<std::string, std::string> Server::helpForInputs {
    {"CNP", "Trebuie sa introduceti 13 cifre!"},
    {"Email", "Emailul trebuie sa contina caracterul @ si caractere inainte si dupa acesta!"},
    {"Numar de telefon", "Trebuie sa introduceti 10 cifre!"},
    {"Nume si prenume", "Numele si prenumele trebuie sa fie formate doar din litere ale alfabetului englez!"},
    {"Iban", "Ibanul trebuie sa contina 2 litere mari ale alfabetului englez urmate 16 cifre."},
};


void Server::printLine() const {
    std::cout << "----------------------------------------------\n";
}

void Server::printOptions(const std::string& menu) const {
    printLine();
    for (size_t i = 0; i < menuOptions[menu].size(); ++i) {
        std::cout << i << " " << menuOptions[menu][i] << '\n';
    }
    std::cout << "Alegeti una dintre optiuni introducand cifra:\n";
    printLine();
}

std::string Server::readAndValidateWithRegex(std::string valueName) const {
    std::string value;
    int attempts = 0;
    while (true) {
        ++attempts;
        std::cout << "Va rugam introduceti " + valueName + ".\n";
        std::getline(std::cin, value);

        if (regexRules.find(valueName) == regexRules.end()) {
            throw NoRegexFoundServer(valueName);
        }

        if (!std::regex_match(value, regexRules[valueName])) {
            std::cout << "Optiunea " + valueName + " este invalida. Va rugam sa reintroduceti optiunea! Mai aveti " << 5 - attempts << " incercari.\n";
            if (helpForInputs.find(valueName) != helpForInputs.end()) {
                std::cout << helpForInputs[valueName] << '\n';
            }
            if (attempts >= 5) {
                throw ToManyInvalidInputs();
            }
            continue;
        }

        std::cout << "Ati introdus " + valueName << ": " << value << "\n";
        return value;
    }
    return "Start";
}

std::string Server::redirect() {
    if (userLogat) {
        return "Profil";
    } else {
        return "Start";
    }
}

void Server::start() {
    std::string actualMenu = "Start";
    while (true) {
        try {
            if (actualMenu == "Iesire") {
                break;
            } else if (actualMenu == "Inregistrare") {
                registerr();
            } else if (actualMenu == "Autentificare") {
                login();
            } else if (actualMenu == "Deconectare") {
                logout();
            } else if (actualMenu == "Economii" || actualMenu == "Debit") {
                addAccount(actualMenu);
            } else if (actualMenu == "Sterge un cont existent") {
                removeAccount();
            } else if (actualMenu == "Afiseaza detaliile conturilor mele") {
                std::cout << users[idxUserActual] << '\n';
            } else if (actualMenu == "Adauga bani in cont") {
                addFundsToAccount();
            } else if (actualMenu == "Adauga un card nou unui cont") {
                addCard();
            } else if (actualMenu == "Plateste cu cardul") {
                payWithCardWithProxy();
            } else if (actualMenu == "Executa un transfer") {
                transferWithProxy();
            } else { // profil or start
                printOptions(actualMenu);
                int option = std::stoi(readAndValidateWithRegex("optiunea"));
                if (option < 0 || option >= (int)menuOptions[actualMenu].size()) {
                    std::cout << "Optiune inexistenta. Mai incearca odata.\n";
                    continue;
                }
                actualMenu = menuOptions[actualMenu][option];
                continue; // am schimbat meniul, nu mai trebuie sa dau redirect la final
            }
            actualMenu = redirect();
        } catch (NoRegexFoundServer& err) {
            std::cout << err.what() << '\n';
            actualMenu = redirect();
        } catch (ServerError& err) {
            std::cout << err.what() << '\n';
            actualMenu = redirect();
        }
        // outUsers();
    }
}

void Server::registerr() {
    std::string nume = readAndValidateWithRegex("Nume si prenume");
    std::string cnp = readAndValidateWithRegex("CNP");
    std::string numarTelefon = readAndValidateWithRegex("Numar de telefon");
    std::string email = readAndValidateWithRegex("Email");

    User userNou = User(nume, cnp, email, numarTelefon);

    if (std::find(users.begin(), users.end(), userNou) != users.end()) {
        std::cout << "Deja exista un utilizator cu acest CNP! Va rugam sa va inregistrati.\n";
    } else {
        users.push_back(userNou);
    }
}

void Server::login() {
    std::string email = readAndValidateWithRegex("Email");
    std::string cnp = readAndValidateWithRegex("CNP");
    for (size_t i = 0; i < Server::users.size(); ++i) {
        if (users[i].checkUserWithEmailAndCnp(email, cnp)) {
            idxUserActual = i;
            userLogat = true;
            std::cout << "User conectat cu succes.\n";
            std::cout << users[idxUserActual] << '\n';
            return;
        }
    }
    std::cout << "Nu am gasit un user cu datele specificate in baza noastra de date :(.\n";
}

void Server::logout() {
    idxUserActual = -1;
    userLogat = false;
}

void Server::addAccount(const std::string& typeOfAccount) {
    if (!userLogat) {
        std::cout << "Trebuie sa va autentificati!\n";
        return;
    }
    if (typeOfAccount == "Economii")
        Server::users[idxUserActual].createAccount("Savings");
    else if (typeOfAccount == "Debit")
        Server::users[idxUserActual].createAccount("Debit");
}

void Server::outUsers() const {
    std::cout << "Useri in baza de date: \n";
    for (const auto& user : users) {
        std::cout << user << '\n';
    }
}

void Server::removeAccount() {
    std::vector<std::shared_ptr<Account>> accountsUser = users[idxUserActual].getAccounts();
    if (accountsUser.empty()) {
        std::cout << "Nu aveti niciun cont momentan!\n";
        return;
    }

    std::cout << "Alegeti una dintre optiuni introducand cifra:\n";

    for (int i = 0; i < (int)accountsUser.size(); ++i) {
        std::cout << i << " -> " << *accountsUser[i] << '\n';
    }
    int option = std::stoi(readAndValidateWithRegex("optiunea"));
    if (option < 0 || option >= (int)accountsUser.size()) {
        std::cout << "Cont inexistenta. Mai incearca odata.\n";
        return;
    }
    users[idxUserActual].removeAccount(option);
    std::cout << "Cont sters cu succes\n";
}

std::shared_ptr<Account> Server::selectAccount() const {
    std::vector<std::shared_ptr<Account>> accounts = users[idxUserActual].getAccounts();
    if (accounts.empty()) {
        std::cout << "Nu aveti nici un cont inca!\n";
        return nullptr;
    } else if ((int)accounts.size() == 1) { // If there is only one option, send it without asking the user which one to choose.
        return accounts.back();
    }
    std::cout << "Va rugam introduceti numarul contului pe care vreti sa il folositi:\n";
    for (int i = 0; i < (int)accounts.size(); ++i) {
        std::cout << "Contul " << i << ": " << *accounts[i] << '\n';
    }
    int option = std::stoi(readAndValidateWithRegex("optiunea"));
    if (option < 0 || option >= (int)accounts.size()) {
        std::cout << "Optiune inexistenta. Mai incearca odata.\n";
        return nullptr;
    } else {
        std::cout << "Ati ales contul " << option << " cu succes!\n";
    }
    return accounts[option];
}

int Server::selectCurrencyCode() const {
    int sz = std::extent<decltype(stringCurrency)>::value;
    std::cout << "Va rugam introduceti numarul valutei pe care vreti sa il folositi:\n";
    for (int i = 0; i < sz; ++i) {
        std::cout << i << ": " << stringCurrency[i] << '\n';
    }
    int option = std::stoi(readAndValidateWithRegex("optiunea"));
    if (option < 0 || option >= sz) {
        std::cout << "Optiune inexistenta. Mai incearca odata.\n";
        return -1;
    } else {
        std::cout << "Ati ales valuta " << stringCurrency[option] << " cu succes!\n";
    }
    return option;
}

void Server::addFundsToAccount() {
    std::shared_ptr<Account> account = selectAccount();
    if (account == nullptr)
        return;
    int currencyCode = selectCurrencyCode();
    if (currencyCode == -1)
        return;
    float amount = std::stof(readAndValidateWithRegex("Suma"));

    account->addFunds(amount, (Currency)currencyCode);
    std::cout << "Ati adaugat " << amount << " de " << stringCurrency[currencyCode] << " cu succes\n";
}

int Server::selectCardTypeCode() const {
    int sz = std::extent<decltype(stringCardType)>::value;
    // If there is only one option, send it without asking the user which one to choose.
    if (sz == 1) {
        return 0;
    }
    std::cout << "Va rugam introduceti numarul tipului de card pe care il doriti:\n";
    for (int i = 0; i < sz; ++i) {
        std::cout << i << ": " << stringCardType[i] << '\n';
    }
    int option = std::stoi(readAndValidateWithRegex("optiunea"));
    if (option < 0 || option >= sz) {
        std::cout << "Optiune inexistenta. Mai incearca odata.\n";
        return -1;
    } else {
        std::cout << "Ati ales cardul " << stringCardType[option] << " cu succes!\n";
    }
    return option;
}

void Server::addCard() {
    std::shared_ptr<Account> account = selectAccount();
    if (account == nullptr) {
        return;
    }
    int cardTypeCode = selectCardTypeCode();
    if (cardTypeCode == -1)
        return;
    account->addNewCard(users[idxUserActual].getName(), (CardType)cardTypeCode);
}

std::shared_ptr<Card> Server::selectCard(const std::shared_ptr<Account> account) const {
    std::vector<Card> cards = account->getCards();
    if (cards.empty()) {
        std::cout << "Nu aveti niciun card asociat acestui cont!\n";
        return nullptr;
    } else if ((int)cards.size() == 1) {
        return std::make_shared<Card>(cards.back());
    }
    std::cout << "Va rugam introduceti numarul cardului pe care vreti sa il folositi:\n";
    for (int i = 0; i < (int)cards.size(); ++i) {
        std::cout << "Cardul " << i << ": " << cards[i] << '\n';
    }
    int option = std::stoi(readAndValidateWithRegex("optiunea"));
    if (option < 0 || option >= (int)cards.size()) {
        std::cout << "Optiune inexistenta. Mai incearca odata.\n";
        return nullptr;
    } else {
        std::cout << "Ati ales cardul " << option << " cu succes!\n";
    }
    return std::make_shared<Card>(cards[option]);
}


void Server::payWithCardWithProxy() {
    std::shared_ptr<Account> account = selectAccount();
    if (account == nullptr) {
        return;
    }
    std::shared_ptr<Card> card = selectCard(account);
    if (card == nullptr) {
        return;
    }
    int currencyCode = selectCurrencyCode();
    if (currencyCode == -1)
        return;
    float amount = std::stof(readAndValidateWithRegex("Suma"));
    AccountProxy accountProxy = AccountProxy(account, card);
    try {
        accountProxy.pay(amount, (Currency)currencyCode);
    } catch (AppError& err) {
        std::cout << "A aparut o eroare: " << err.what() << '\n';
    }
}

std::shared_ptr<Account> Server::getAccountFromUsersWithNameAndIban(const std::string& name, const std::string& iban) const {
    for (auto& user : users) {
        if (user.getName() == name) {
            std::shared_ptr<Account> account = user.getAccountWithIban(iban);
            if (account == nullptr) {
                std::cout << "Utilizatorul nu detine niciun cont cu iban-ul specificat.";
            } else {
                std::cout << "Cont gasit cu succes!";
                return account;
            }
            return nullptr;
        }
    }
    return nullptr;
}

void Server::transferWithProxy() {
    std::shared_ptr<Account> account = selectAccount();
    if (account == nullptr) {
        return;
    }
    std::string name = readAndValidateWithRegex("Nume si prenume");
    std::string iban = readAndValidateWithRegex("Iban");

    std::shared_ptr<Account> accountRecipient = getAccountFromUsersWithNameAndIban(name, iban);
    if (accountRecipient == nullptr) {
        return;
    }

    int currencyCode = selectCurrencyCode();
    if (currencyCode == -1)
        return;
    float amount = std::stof(readAndValidateWithRegex("Suma"));
    AccountProxy accountProxy = AccountProxy(account, nullptr);
    accountProxy.makeTransaction(accountRecipient, amount, (Currency)currencyCode);
}