#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

// Sablonova trida pro jednorozmerne pole
template <class T>
class Array1D {
private:
    T* data;                // Ukazatel na dynamicky alokovane pole
    unsigned int pocet;     // Pocet prvku v poli

public:
    // --- KONSTRUKTORY A DESTRUKTOR ---

    // Konstruktor s velikosti pole
    Array1D(unsigned int velikost) {
        if (velikost == 0) {
            throw invalid_argument("Chyba: Velikost nesmi byt nula");
        }

        this->pocet = velikost;
        this->data = new T[velikost];

        for (int i = 0; i < velikost; i++) {
            this->data[i] = 0;
        }
    }

    // Konverzni konstruktor - vytvori pole o 1 prvku z hodnoty
    Array1D(T hodnota) {
        this->pocet = 1;
        this->data = new T[this->pocet];
        this->data[0] = hodnota;
    }

    // Kopirovaci konstruktor - hluboka kopie dat
    Array1D(const Array1D& other) {
        this->pocet = other.pocet;
        this->data = new T[this->pocet];

        for (int i = 0; i < this->pocet; i++) {
            this->data[i] = other.data[i];
        }
    }

    // Destruktor - uvolneni pameti
    ~Array1D() {
        delete[] this->data;
    }

    // --- OPERATORY ---

    // Operator prirazeni - hluboka kopie
    Array1D& operator=(const Array1D& other) {
        if (this != &other) {
            delete[] this->data;

            this->pocet = other.pocet;
            this->data = new T[this->pocet];

            for (int i = 0; i < this->pocet; i++) {
                this->data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Operator indexovani s kontrolou mezÃ­
    T& operator[](int index) {
        if (index < 0 || index >= this->pocet) {
            throw out_of_range("Chyba: Index je mimo rozsah pole");
        }

        return this->data[index];
    }

    // Operator indexovani pro konstantni pole
    const T& operator[](int index) const {
        if (index < 0 || index >= this->pocet) {
            throw out_of_range("Chyba: Index je mimo rozsah pole");
        }

        return this->data[index];
    }

    // Unarni operator minus - negace vsech hodnot pole
    Array1D operator-() const {
        Array1D vysledek(this->pocet);

        for (int i = 0; i < this->pocet; i++) {
            vysledek.data[i] = -this->data[i];
        }

        return vysledek;
    }

    // Hlavicky spratelenich operatoru
    template <class P>
    friend bool operator==(const Array1D<P>& a, const Array1D<P>& b);

    template <class P>
    friend bool operator!=(const Array1D<P>& a, const Array1D<P>& b);

    // Binarni operator scitani dvou poli
    friend Array1D operator+(const Array1D& a, const Array1D& b) {
        if (a.pocet == 1) {
            Array1D vysledek(b.pocet);
            for (int i = 0; i < b.pocet; i++) {
                vysledek.data[i] = a.data[0] + b.data[i];
            }
            return vysledek;
        }

        if (b.pocet == 1) {
            Array1D vysledek(a.pocet);
            for (int i = 0; i < a.pocet; i++) {
                vysledek.data[i] = a.data[i] + b.data[0];
            }
            return vysledek;
        }

        if (a.pocet != b.pocet) {
            throw invalid_argument("Chyba: Pole musi mit stejnou velikost");
        }

        Array1D vysledek(a.pocet);
        for (int i = 0; i < a.pocet; i++) {
            vysledek.data[i] = a.data[i] + b.data[i];
        }

        return vysledek;
    }

    // Binarni operator odcitani dvou poli
    friend Array1D operator-(const Array1D& a, const Array1D& b) {
        if (a.pocet == 1) {
            Array1D vysledek(b.pocet);
            for (int i = 0; i < b.pocet; i++) {
                vysledek.data[i] = a.data[0] - b.data[i];
            }
            return vysledek;
        }

        if (b.pocet == 1) {
            Array1D vysledek(a.pocet);
            for (int i = 0; i < a.pocet; i++) {
                vysledek.data[i] = a.data[i] - b.data[0];
            }
            return vysledek;
        }

        if (a.pocet != b.pocet) {
            throw invalid_argument("Chyba: Pole musi mit stejnou velikost");
        }

        Array1D vysledek(a.pocet);
        for (int i = 0; i < a.pocet; i++) {
            vysledek.data[i] = a.data[i] - b.data[i];
        }

        return vysledek;
    }

    // Binarni operator nasobeni pole hodnotou
    friend Array1D operator*(const Array1D& a, const Array1D& b) {
        if (a.pocet == 1) {
            Array1D vysledek(b.pocet);
            for (int i = 0; i < b.pocet; i++) {
                vysledek.data[i] = a.data[0] * b.data[i];
            }
            return vysledek;
        }

        if (b.pocet == 1) {
            Array1D vysledek(a.pocet);
            for (int i = 0; i < a.pocet; i++) {
                vysledek.data[i] = a.data[i] * b.data[0];
            }
            return vysledek;
        }

        if (a.pocet != b.pocet) {
            throw invalid_argument("Chyba: Pole musi mit stejnou velikost");
        }

        Array1D vysledek(a.pocet);

        for (int i = 0; i < a.pocet; i++) {
            vysledek.data[i] = a.data[i] * b.data[i];
        }

        return vysledek;
    }

    // Binarni operator deleni pole hodnotou
    friend Array1D operator/(const Array1D& a, const Array1D& b) {
        if (a.pocet == 1) {
            Array1D vysledek(b.pocet);
            for (int i = 0; i < b.pocet; i++) {
                if (b.data[i] == 0) {
                    throw invalid_argument("Chyba: Deleni nulou");
                }
                vysledek.data[i] = a.data[0] / b.data[i];
            }
            return vysledek;
        }

        if (b.pocet == 1) {
            Array1D vysledek(a.pocet);
            for (int i = 0; i < a.pocet; i++) {
                if (b.data[0] == 0) {
                    throw invalid_argument("Chyba: Deleni nulou");
                }
                vysledek.data[i] = a.data[i] / b.data[0];
            }
            return vysledek;
        }

        if (a.pocet != b.pocet) {
            throw invalid_argument("Chyba: Pole musi mit stejnou velikost");
        }

        Array1D vysledek(a.pocet);
        for (int i = 0; i < a.pocet; i++) {
            if (b.data[i] == 0) {
                throw invalid_argument("Chyba: Deleni nulou");
            }
            vysledek.data[i] = a.data[i] / b.data[i];
        }

        return vysledek;
    }

    template <class P>
    friend ostream& operator<<(ostream& out, const Array1D<P>& arr);

    // --- STATISTIKY ---

    // Vypocet souctu prvku pole
    double sum() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        T soucet = 0;
        for (int i = 0; i < this->pocet; i++) {
            soucet += this->data[i];
        }

        return (double)soucet;
    }

    // Vypocet prumeru prvku pole
    double average() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        return this->sum() / this->pocet;
    }

    // Vypocet smerodatne odchylky prvku pole
    double stdev() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        double prumer = this->average();
        double rozptyl = 0;

        for (int i = 0; i < this->pocet; i++) {
            rozptyl += pow(this->data[i] - prumer, 2);
        }

        return sqrt(rozptyl / this->pocet);
    }

    // Nalezeni maxima v poli
    T maximum() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        T max = this->data[0];
        for (int i = 1; i < this->pocet; i++) {
            if (this->data[i] > max) {
                max = this->data[i];
            }
        }

        return max;
    }

    // Nalezeni minima v poli
    T minimum() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        T min = this->data[0];
        for (int i = 1; i < this->pocet; i++) {
            if (this->data[i] < min) {
                min = this->data[i];
            }
        }

        return min;
    }

    // Vypocet medianu
    double median() const {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        Array1D<T> kopie = *this;
        kopie.sortAsc();

        if (this->pocet % 2 != 0) {
            T mid = kopie.data[this->pocet / 2];

            return (double)mid;
        }
        else {
            T first = kopie.data[this->pocet / 2 - 1];
            T second = kopie.data[this->pocet / 2];

            return (double)(first + second) / 2.0;
        }
    }

    // --- RAZENI ---

    // Razeni prvku pole vzestupne
    void sortAsc() {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        sort(this->data, this->data + this->pocet);
    }

    // Razeni prvku pole sestupne - porovnava a > b
    void sortDesc() {
        if (this->pocet <= 0) {
            throw logic_error("Chyba: Pole je prazdne");
        }

        this->sortAsc();
        reverse(this->data, this->data + this->pocet);
    }
};

// --- IMPLEMENTACE SPRATELENICH OPERATORU MIMO TRIDU ---

// Operator rovnosti - porovna dve pole prvek po prvku
template <class P>
bool operator==(const Array1D<P>& a, const Array1D<P>& b) {
    if (a.pocet != b.pocet) {
        return false;
    }

    for (int i = 0; i < a.pocet; i++) {
        if (a.data[i] != b.data[i]) {
            return false;
        }
    }

    return true;
}

// Operator nerovnosti
template <class P>
bool operator!=(const Array1D<P>& a, const Array1D<P>& b) {
    return !(a == b);
}

// Operator vypisu pole na konzoli
template <class P>
ostream& operator<<(ostream& out, const Array1D<P>& arr) {
    out << "[";

    for (int i = 0; i < arr.pocet; i++) {
        out << arr.data[i];
        if (i < arr.pocet - 1) {
            out << ", ";
        }
    }

    out << "]";
    return out;
}

int main() {
    cout << "--- Projekt P05: Jednorozmerne pole ---" << endl;

    try {
        // Vytvoreni pole A o velikosti 4 a naplneni hodnotami
        Array1D<double> A(4u);
        A[0] = 40.5;
        A[1] = 10.2;
        A[2] = 30.8;
        A[3] = 20.1;
        cout << "Pole A: " << A << endl;

        // Nasobeni pole hodnotou - vysledek ulozime do pole B
        Array1D<double> B = A * 2.0;
        cout << "Pole B (A * 2): " << B << endl;

        // Scitani dvou poli - vysledek ulozime do pole C
        Array1D<double> C = A + B;
        cout << "Pole C (A + B): " << C << endl;

        // Odcitani dvou poli - vysledek ulozime do pole D
        Array1D<double> D = B - A;
        cout << "Pole D (B - A): " << D << endl;

        // Deleni pole hodnotou - vysledek ulozime do pole E
        Array1D<double> E = B / 2.0;
        cout << "Pole E (B / 2): " << E << endl;

        // Negace pole A - vysledek ulozime do pole F
        Array1D<double> F = -A;
        cout << "Pole F (-A): " << F << endl;

        // Test kopirovacÃ­ho konstruktoru a porovnani poli
        Array1D<double> G = A;
        cout << "\nTest porovnani:" << endl;
        if (A == G) {
            cout << "Pole A a G jsou stejna." << endl;
        }
        if (A != B) {
            cout << "Pole A a B jsou ruzna." << endl;
        }

        // Vypocet statistik pro pole A
        cout << "\nStatistiky pole A:" << endl;
        cout << "Soucet: " << A.sum() << endl;
        cout << "Prumer: " << A.average() << endl;
        cout << "Smerodatna odchylka: " << A.stdev() << endl;
        cout << "Maximum: " << A.maximum() << endl;
        cout << "Minimum: " << A.minimum() << endl;
        cout << "Median: " << A.median() << endl;

        // Razeni prvku pole A
        cout << "\nRazeni pole A:" << endl;
        A.sortAsc();
        cout << "Pole A (vzestupne): " << A << endl;
        A.sortDesc();
        cout << "Pole A (sestupne): " << A << endl;

    }
    catch (const exception& e) {
        cerr << "CHYBA: " << e.what() << endl;
    }

    // Test: Zaporna velikost
    try {
        cout << "Test 1 (Nulova velikost): ";
        Array1D<int> I(0u);
    }
    catch (const exception& e) {
        cerr << "CHYBA: " << e.what() << endl;
    }

    // Test: Index mimo rozsah
    try {
        cout << "Test 2 (Index mimo rozsah): ";
        Array1D<int> I(3u);
        I[5] = 10;
    }
    catch (const exception& e) {
        cerr << "CHYBA: " << e.what() << endl;
    }

    // Test: Deleni nulou
    try {
        cout << "Test 3 (Deleni nulou): ";
        Array1D<double> J(2u);
        Array1D<double> K = J / 0.0;
    }
    catch (const exception& e) {
        cerr << "CHYBA: " << e.what() << endl;
    }

    // Test: Operace s polemi ruznych velikosti
    try {
        cout << "Test 4 (Ruzne velikosti pri scitani): ";
        Array1D<double> X(2u);
        Array1D<double> Y(3u);
        Array1D<double> Z = X + Y;
    }
    catch (const exception& e) {
        cerr << "CHYBA: " << e.what() << endl;
    }

    return 0;
}