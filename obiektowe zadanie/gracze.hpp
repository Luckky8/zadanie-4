#ifndef GRACZE_HPP
#define GRACZE_HPP

#include <string>
#include <vector>
#include <iostream>

struct Gracz
{
    std::string imie;
    int kasa;
    int portfel;
    Gracz(const std::string& im) : imie(im), kasa(0), portfel(0) {}
};

class Gracze
{
public:
    Gracze();
    //void dodajGracza(const std::string& imie);
    
    
    void przejdzDoNastepnegoGracza();
    void obecnyGraczBankrutuje();
    void dodajKase(int kwota);
    std::string obecnyGracz() const;
    void wypiszGraczy() const;

    //przeciazenia operatorow
    void operator+=(const Gracz& gracz)
    {
        listaGraczy.push_back(gracz);
    }

    void operator-=(const Gracz& gracz)
    {
        for (auto it = listaGraczy.begin(); it != listaGraczy.end(); ++it)
        {
            if (it->imie == gracz.imie)
            {
                listaGraczy.erase(it);
                break;
            }
        }
    }

    Gracze& operator++()
    {
        indeksObecnegoGracza = (indeksObecnegoGracza + 1) % listaGraczy.size();
        return *this;
    }

    Gracze& operator--()
    {
        if (listaGraczy.size() > 0)
        {
            listaGraczy.erase(listaGraczy.begin() + indeksObecnegoGracza);

            if (indeksObecnegoGracza >= listaGraczy.size())
            {
                indeksObecnegoGracza = listaGraczy.size() - 1;
            }
        }
        return *this;
    }


    
private:
    std::vector<Gracz> listaGraczy;
    int indeksObecnegoGracza;
};

#endif
