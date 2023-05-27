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
    User{"Just for testing", "1234567890123", "t@gmail.com", "0710000000"}
};

std::unordered_map<std::string, std::vector<std::string> > Server::menuOptions =
{
  { "Start", { "Autentificare", "Inregistrare", "Iesire"} },
  { "Profil", { "Creeaza un cont nou", "Sterge un cont existent", "Deconectare", "Iesire"}},
  { "Creeaza un cont nou", {"Economii", "Debit"}}
};

std::unordered_map<std::string, std::regex> Server::regexRules =
{
    {"CNP", std::regex("^\\d{13}$")},
    {"Email", std::regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+$")},
    {"Numar de telefon", std::regex("^\\d{10}$")},
    {"Nume si prenume", std::regex("^[a-zA-Z ]+$")},
    {"optiunea", std::regex("^[0-9]+$")}
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
    while (true) {
        std::cout << "Va rugam introduceti " + valueName + ".\n";
        std::getline(std::cin, value);

        if (regexRules.find(valueName) == regexRules.end()) {
            throw NoRegexFoundServer(valueName);
        }

        if (!std::regex_match(value, regexRules[valueName])) {
            std::cout << "Optiunea " + valueName + " este invalida. Va rugam sa introduceti o " + valueName + " valida.\n";
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
        // std::cout << Server::users[idxUserActual];
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
            } else {
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
            std::cout << err.what();
            actualMenu = redirect();
        } catch (ServerError& err) {
            std::cout << err.what();
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
    users.push_back(User(nume, cnp, email, numarTelefon));
}

void Server::login() {
    std::string email = readAndValidateWithRegex("Email");
    std::string cnp = readAndValidateWithRegex("CNP");
    for (size_t i = 0; i < Server::users.size(); ++i) {
        if (users[i].checkUserWithEmailAndCnp(email, cnp)) {
            idxUserActual = i;
            userLogat = true;
            std::cout << "User deconectat cu succes. \n";
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