template <typename T>
Tranzactie<T>::Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient,
    T value_, const Currency& currency_, bool realizata_) : ibanSender(ibanSender),
    ibanRecipient(ibanRecipient),
    value(value_),
    currency(currency_),
    realizata(realizata_) {
    std::cout << "Contructor tranzactie:\n" << *this << '\n';
}

template <typename T>
Tranzactie<T>::Tranzactie(const Tranzactie<T>& other) : ibanSender(other.ibanSender),
ibanRecipient(other.ibanRecipient),
value(other.value),
currency(other.currency),
realizata(other.realizata) {
    std::cout << "Constructor de copiere.\n";
}

template <typename T>
std::ostream& operator<<(std::ostream& os,
    const Tranzactie<T>& tranzactie) {
    os << "Ibanul contului care a initiat tranzactia: " << tranzactie.ibanSender << '\n';
    os << "Ibanul contului spre care se face tranzactia: " << tranzactie.ibanRecipient << '\n';
    os << "Suma de bani transferata: " << tranzactie.value << " " << typeid(tranzactie.value).name() << '\n';
    os << "Valuta: " << tranzactie.currency << '\n';
    os << "Realizata: " << (tranzactie.realizata == true ? "Da" : "Nu") << '\n';
    return os;
}

template <typename T>
Tranzactie<T>& Tranzactie<T>::operator=(const Tranzactie<T>& tranzactie) {
    // std::cout << "operator= " << *this << "\n";
    ibanSender = tranzactie.ibanSender;
    ibanRecipient = tranzactie.ibanRecipient;
    value = tranzactie.value;
    currency = tranzactie.currency;
    realizata = tranzactie.realizata;
    return *this;
}

template <typename T>
Tranzactie<T>::~Tranzactie() {
    std::cout << "Distrugere tranzactie\n";
}
