#ifndef KSIAZKAADRESOWA_H
#define KSIAZKAADRESOWA_H


#include <iostream>

#include "UzytkownikMenedzer.h"

using namespace std;

class KsiazkaAdresowa
{
    UzytkownikMenedzer uzytkownikMenedzer;

public:
    KsiazkaAdresowa(string nazwaPlikuZUzytkownikami);
    void rejestracjaUzytkownika();
    void wypiszWszystkichUzytkownikow();
    void logowanieUzytkownika();
    void wyswietlZalogowanegoUzytkownika();

};

#endif // KSIAZKAADRESOWA_H
