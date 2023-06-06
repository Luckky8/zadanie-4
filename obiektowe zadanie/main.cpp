#include <iostream>
#include <cstdlib>
#include <ctime>
#include "menu.hpp"
#include "haslo.hpp"
#include "gracze.hpp"
#include "kolo.hpp"

using namespace std;

int main()
{
    srand(time(NULL));

    Menu menu;
    Gracze gracze;
    Haslo haslo;
    Kolo kolo;

    gracze += Gracz("Bryanusz");
    gracze += Gracz("Jessica");
    gracze += Gracz("Nepomucen");

    gracze.wypiszGraczy();

    //haslo.wczytajHaslaZPliku("dane.txt");
    std::ifstream plik("dane.txt");
    plik >> haslo;
    plik.close();
    haslo.losujHaslo();

    while (!haslo.czyHasloZgadniete())
    {
        menu.wyswietlMenu();
        char wybor = menu.wczytajWybor();

        switch (wybor)
        {
        case '1':
        {
            string proba;
            cout << "Podaj haslo: ";
            getline(cin >> ws, proba);
            haslo.sprawdzHaslo(proba);
            break;
        }
        case '2':
        {
            kolo.wyswietlWynik();
            if (kolo.czyStrataKolejki())
            {
                gracze.przejdzDoNastepnegoGracza();
                break;
            }
            else if (kolo.czyBankrut())
            {
                --gracze;
                break;
            }
            else
            {
                char literka = menu.wczytajZnak();
                int zgadl = haslo.sprawdzZgadniecie(literka);
                if (zgadl > 0)
                {
                    int kwota = kolo.zwrocWartosc() * zgadl;
                    gracze.dodajKase(kwota);
                    menu.wyswietlKomunikatZgadl(gracze.obecnyGracz(), kwota);
                }
                else
                {
                    ++gracze;
                    menu.wyswietlKomunikatNieZgadl();
                }
                break;
            }
        }
        default:
            cout << "Nieprawidlowy wybor. Sprobuj jeszcze raz." << endl;
        }

        menu.wyswietlSeparator();
    }

    cout << "BRAWO! Wygrales gre!" << endl;
    return 0;
}
