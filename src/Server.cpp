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
  { "Welcome", { "Login", "Register", "Exit"} },
  { "Profil", { "Creeaza Account nou", "Sterge Account", "Logout", "Exit"}},
  { "Creeaza Account nou", {"Savings", "Debit"}}
};

std::unordered_map<std::string, std::regex> Server::regexRules =
{
    {"CNP", std::regex("^\\d{13}$")},
    {"Email", std::regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6}$")},
    {"Phone Number", std::regex("^\\d{10}$")},
    {"Nume si prenume", std::regex("^[a-zA-Z ]+$")},
    {"option", std::regex("^[0-9]+$")}
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
        std::cout << "Enter an " + valueName + " (or type -1 for exit): \n";
        std::getline(std::cin, value);

        if (regexRules.find(valueName) == regexRules.end()) {
            throw NoRegexFoundServer(valueName);
        }

        if (!std::regex_match(value, regexRules[valueName])) {
            if (value == "-1")
                throw ExitChooserServer();
            std::cout << "Invalid " + valueName + ". Please enter a valid " + valueName + ".\n";
            continue;
        }

        std::cout << "You entered the " + valueName << " " << value << "\n";
        return value;
    }
    if (userLogat)
        return "Profil";
    return "Welcome";
}

void Server::start() {
    std::string actualMenu = "Welcome";
    while (true) {
        try {
            if (actualMenu == "Exit") {
                break;
            } else if (actualMenu == "Register") {
                registerr();
                actualMenu = "Welcome";
            } else if (actualMenu == "Login") {
                login();
                if (userLogat) {
                    actualMenu = "Profil";
                    std::cout << Server::users[idxUserActual];
                } else {
                    actualMenu = "Welcome";
                }
            } else if (actualMenu == "Logout") {
                logout();
                actualMenu = "Welcome";
            } else if (actualMenu == "Savings" || actualMenu == "Debit") {
                addAccount(actualMenu);
                actualMenu = "Profil";
            } else {
                printOptions(actualMenu);
                int option = std::stoi(readAndValidateWithRegex("option"));
                if (option < 0 || option >= (int)menuOptions[actualMenu].size()) {
                    std::cout << "Optiune inexistenta. Mai incearca odata.\n";
                    continue;
                }
                actualMenu = menuOptions[actualMenu][option];
            }
        } catch (ExitChooserServer& err) {
            std::cout << err.what();
            if (userLogat) {
                actualMenu = "Profil";
            } else {
                actualMenu = "Welcome";
            }
        } catch (NoRegexFoundServer& err) {
            std::cout << err.what();
            actualMenu = "Welcome";
        } catch (ServerError& err) {
            std::cout << err.what();
            actualMenu = "Welcome";
        }
        // outUsers();
    }
}

void Server::registerr() {
    std::string nume = readAndValidateWithRegex("Nume si prenume");
    std::string cnp = readAndValidateWithRegex("CNP");
    std::string numarTelefon = readAndValidateWithRegex("Phone Number");
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
            std::cout << "User logat cu succes. \n";
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
        std::cout << "Trebuie sa va logati!\n";
        return;
    }
    Server::users[idxUserActual].createAccount(typeOfAccount);
}

void Server::outUsers() const {
    std::cout << "Users in databse: \n";
    for (const auto& user : users) {
        std::cout << user << '\n';
    }
}