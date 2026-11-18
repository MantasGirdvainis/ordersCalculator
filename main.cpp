#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_PREKIU = 100;

void meniu() {
    cout << endl;
    cout << "=== DVIRAČIŲ PARDUOTUVĖS UŽSAKYMO SKAIČIUOKLĖ ===" << endl;
    cout << "1. Peržiūrėti visas užsakymo prekes" << endl;
    cout << "2. Peržiūrėti pasirinktos kategorijos prekes" << endl;
    cout << "3. Peržiūrėti viso užsakymo sumas" << endl;
    cout << "4. Peržiūrėti sumas pagal kategorijas" << endl;
    cout << "5. Parodyti visą užsakymo ataskaitą" << endl;
    cout << "6. Išsaugoti visą ataskaitą į failą" << endl;
    cout << "7. Išeiti" << endl;
    cout << "Pasirinkite: ";
}

bool teisingaKategorija(string kategorija) {
    return kategorija == "Dviraciai" || kategorija == "Dalys" || kategorija == "Aksesuarai";
}

int nuskaitytiDuomenis(string failoPavadinimas, string kategorijos[], string pavadinimai[],
                       double kainos[], int kiekiai[]) {
    ifstream fin(failoPavadinimas);
    if (!fin.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << endl;
        return 0;
    }

    int n;
    fin >> n;
    if (fin.fail()) {
        cout << "Klaida: pirmoje failo eilutėje turi būti prekių įrašų skaičius." << endl;
        return 0;
    }
    if (n < 1 || n > MAX_PREKIU) {
        cout << "Klaida: įrašų skaičius turi būti nuo 1 iki " << MAX_PREKIU << " (faile: " << n << ")." << endl;
        return 0;
    }
    fin.ignore(1000, '\n');

    for (int i = 0; i < n; i++) {
        string kategorija;
        string pavadinimas;
        double kaina;
        char kabliataskis;
        int kiekis;
        string likutis;

        getline(fin, kategorija, ';');
        getline(fin, pavadinimas, ';');
        fin >> kaina >> kabliataskis >> kiekis;

        if (fin.fail()) {
            cout << "Klaida: nepavyko nuskaityti " << i + 1 << "-o įrašo. Faile nurodyta "
                 << n << " įrašų, bet duomenų trūksta arba jie netinkami." << endl;
            return 0;
        }

        getline(fin, likutis);
        if (likutis.length() > 0 && likutis[likutis.length() - 1] == '\r') {
            likutis.erase(likutis.length() - 1);
        }

        if (kabliataskis != ';' || likutis != "") {
            cout << "Klaida: " << i + 1 << "-o įrašo formatas netinkamas "
                 << "(kaina turi būti su tašku, kiekis - sveikasis skaičius)." << endl;
            return 0;
        }
        if (!teisingaKategorija(kategorija)) {
            cout << "Klaida: " << i + 1 << "-o įrašo kategorija \"" << kategorija
                 << "\" netinkama. Galimos: Dviraciai, Dalys, Aksesuarai." << endl;
            return 0;
        }
        if (pavadinimas == "") {
            cout << "Klaida: " << i + 1 << "-o įrašo prekės pavadinimas tuščias." << endl;
            return 0;
        }
        if (kaina <= 0) {
            cout << "Klaida: " << i + 1 << "-o įrašo kaina turi būti teigiama." << endl;
            return 0;
        }
        if (kiekis <= 0) {
            cout << "Klaida: " << i + 1 << "-o įrašo kiekis turi būti teigiamas sveikasis skaičius." << endl;
            return 0;
        }

        kategorijos[i] = kategorija;
        pavadinimai[i] = pavadinimas;
        kainos[i] = kaina;
        kiekiai[i] = kiekis;
    }

    fin.close();
    return n;
}

int main() {
    string kategorijos[MAX_PREKIU];
    string pavadinimai[MAX_PREKIU];
    double kainos[MAX_PREKIU];
    int kiekiai[MAX_PREKIU];

    int prekiuKiekis = nuskaitytiDuomenis("uzsakymas.txt", kategorijos, pavadinimai, kainos, kiekiai);
    if (prekiuKiekis == 0) {
        cout << "Duomenų nuskaityti nepavyko. Programa baigiama." << endl;
        return 1;
    }
    cout << "Duomenys nuskaityti sėkmingai. Prekių įrašų: " << prekiuKiekis << endl;

    cout << fixed << setprecision(2);

    int pasirinkimas;

    do {
        meniu();
        cin >> pasirinkimas;
        while (cin.fail() || pasirinkimas < 1 || pasirinkimas > 7) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Tokio pasirinkimo nėra. Pasirinkite nuo 1 iki 7: ";
            cin >> pasirinkimas;
        }

        switch (pasirinkimas) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                cout << "Ši funkcija dar neįgyvendinta." << endl;
                break;
            case 7:
                cout << "Programa uždaryta" << endl;
                break;
        }
    } while (pasirinkimas != 7);

    return 0;
}
