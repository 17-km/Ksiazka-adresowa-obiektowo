#ifndef PLIKTEKSTOWY_H
#define PLIKTEKSTOWY_H

#include <iostream>
#include <fstream>

using namespace std;

class PlikTekstowy
{
protected:
    const string NAZWA_PLIKU;

public:
    PlikTekstowy(string nazwaPliku);
    bool czyPlikJestPusty();

};

#endif // PLIKTEKSTOWY_H
