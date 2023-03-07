#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
// TODO change all variables name to English :)

enum Currency {
    RON,
    EUR,
    USD
};

class Card {
    std::string cod, data_expirare, cvv; // maybe import a date type
public: 
    Card() = default;
};

/*
User main class:
Need: name, cnp, iban, numar_telefon
Can have: multiple currency, multiple cards (normal, bronze, silver, golden, platinum) TODO (i should add an enum here but idk how yet)
*/
class User {
    std::string nume, cnp, iban, email, numar_telefon;
    std::unordered_map<Currency, float> currencyAccount; // maybe create a vector instead of a hash table for tests
    std::vector<Card> carduri = {}; // this should be optional

public:
    User()= default;

};


class AppAccount {
    User user;
    std::string password;
};

class Tranzactie {
    User user1, user2; // the withdraws are made between the company account and the user account
    float value;
    Currency currency;
    bool realizata;
public:
    Tranzactie()= default;

};



class main
{
private:
    /* data */
public:
    main(/* args */);
    ~main();
};

main::main(/* args */)
{
}

main::~main()
{
}



int main() {
    std::cout << "Hello, world!\n";
    return 0;
}
