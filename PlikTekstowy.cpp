#include "PlikTekstowy.h"

PlikTekstowy::PlikTekstowy(string nazwaPliku)
    : NAZWA_PLIKU(nazwaPliku){}


bool PlikTekstowy::czyPlikJestPusty()
{
    bool pusty = true;
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU.c_str(), ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy.seekg(0, ios::end);
    if (plikTekstowy.tellg() != 0)
        pusty = false;
    }

    plikTekstowy.close();
    return pusty;
}

