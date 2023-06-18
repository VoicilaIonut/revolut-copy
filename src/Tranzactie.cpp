template <typename T>
Tranzactie<T>::Tranzactie(const std::string& ibanSender, const std::string& ibanRecipient,
    T value_, const Currency& currency_, bool realizata_) : ibanSender(ibanSender),
    ibanRecipient(ibanRecipient),
    value(value_),
    currency(currency_),
    realizata(realizata_) {
    std::cout << "Tranzactie constructor\n" << *this << '\n';
}

template <typename T>
Tranzactie<T>::Tranzactie(const Tranzactie<T>& other) : ibanSender(other.ibanSender),
ibanRecipient(other.ibanRecipient),
value(other.value),
currency(other.currency),
realizata(other.realizata) {
    std::cout << "Constr de copiere" << *this << "\n";
}

template <typename T>
std::ostream& operator<<(std::ostream& os,
    const Tranzactie<T>& tranzactie) {
    os << "ibanSender: " << tranzactie.ibanSender
        << " ibanRecipient: " << tranzactie.ibanRecipient << '\n';
    os << "Value: " << tranzactie.value << " " << typeid(tranzactie.value).name() << '\n';
    os << "Currency: " << tranzactie.currency << '\n';
    os << "Realizata: " << tranzactie.realizata << '\n';
    return os;
}

template <typename T>
Tranzactie<T>& Tranzactie<T>::operator=(const Tranzactie<T>& tranzactie) {
    std::cout << "operator= " << *this << "\n";
    ibanSender = tranzactie.ibanSender;
    ibanRecipient = tranzactie.ibanRecipient;
    value = tranzactie.value;
    currency = tranzactie.currency;
    realizata = tranzactie.realizata;
    return *this;
}

template <typename T>
Tranzactie<T>::~Tranzactie() {
    std::cout << "Destroing Tranzactie" << *this << "\n";
}
