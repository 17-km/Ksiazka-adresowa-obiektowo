#include "PlikZAdresatami.h"

PlikZAdresatami::PlikZAdresatami(string nazwaPlikuZAdresatami, string nazwaTymczasowegoPlikuZAdresatami)
    : PlikTekstowy(nazwaPlikuZAdresatami), NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI(nazwaTymczasowegoPlikuZAdresatami)
{
    idOstatniegoAdresata = 0;
}

bool PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty() == true)
        {
            plikTekstowy << liniaZDanymiAdresata;
        }
        else
        {
            plikTekstowy << endl << liniaZDanymiAdresata ;
        }
        idOstatniegoAdresata++;
        plikTekstowy.close();
        return true;
    }
    return false;
}

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}

vector<Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    vector <Adresat> adresaci;
    Adresat adresat;
    idOstatniegoAdresata = 0;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    plikTekstowy.close();

    if (daneOstaniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
    }
    else
        idOstatniegoAdresata = 0;
    return adresaci;
}

int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}

int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}

Adresat PlikZAdresatami::pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.ustawId(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie(pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko(pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumerTelefonu(pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail(pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres(pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    return idOstatniegoAdresata;
}

void PlikZAdresatami::usunWybranegoAdresataZPliku(int idUsuwanegoAdresata)
{
    fstream odczytywanyPlikTekstowy;
    fstream tymczasowyPlikTekstowy;
    bool czyTymczasowyPlikTekstowyJestPusty = true;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    int idOdczytywanegoAdresata = 0;

    odczytywanyPlikTekstowy.open(NAZWA_PLIKU.c_str(), ios::in);

    if(odczytywanyPlikTekstowy.good() == true)
    {
        tymczasowyPlikTekstowy.open(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI.c_str(),ios::out);

        while(getline(odczytywanyPlikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            int idOdczytywanegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami);
            if (idUsuwanegoAdresata != idOdczytywanegoAdresata)
            {
                idOstatniegoAdresata = idOdczytywanegoAdresata;
                if (czyTymczasowyPlikTekstowyJestPusty)
                {
                    tymczasowyPlikTekstowy << daneJednegoAdresataOddzielonePionowymiKreskami;
                    czyTymczasowyPlikTekstowyJestPusty = false;
                }
                else
                {
                    tymczasowyPlikTekstowy << endl << daneJednegoAdresataOddzielonePionowymiKreskami;
                }
            }
        }
    }
    odczytywanyPlikTekstowy.close();
    tymczasowyPlikTekstowy.close();

    usunPlik(NAZWA_PLIKU);
    zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, NAZWA_PLIKU);
}

void PlikZAdresatami::usunPlik(string nazwaPlikuZRozszerzeniem)
{
    if (remove(nazwaPlikuZRozszerzeniem.c_str()) == 0) {}
    else
        cout << "Nie udalo sie usunac pliku " << nazwaPlikuZRozszerzeniem << endl;
}

void PlikZAdresatami::zmienNazwePliku(string staraNazwa, string nowaNazwa)
{
    if (rename(staraNazwa.c_str(), nowaNazwa.c_str()) == 0) {}
    else
        cout << "Nazwa pliku nie zostala zmieniona." << staraNazwa << endl;
}

void PlikZAdresatami::zaktualizujDaneWybranegoAdresata(Adresat adresat)
{
    string liniaZNowymiDanymiAdresata = "";
    liniaZNowymiDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

    fstream odczytywanyPlikTekstowy;
    fstream tymczasowyPlikTekstowy;
    bool czyTymczasowyPlikTekstowyJestPusty = true;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    odczytywanyPlikTekstowy.open(NAZWA_PLIKU.c_str(), ios::in);

    if(odczytywanyPlikTekstowy.good() == true)
    {
        tymczasowyPlikTekstowy.open(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI.c_str(),ios::out);

        while(getline(odczytywanyPlikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if (adresat.pobierzId() != pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                if (czyTymczasowyPlikTekstowyJestPusty)
                {
                    tymczasowyPlikTekstowy << daneJednegoAdresataOddzielonePionowymiKreskami;
                    czyTymczasowyPlikTekstowyJestPusty = false;
                }
                else
                {
                    tymczasowyPlikTekstowy << endl << daneJednegoAdresataOddzielonePionowymiKreskami;
                }
            }
            else
            {
                if (czyTymczasowyPlikTekstowyJestPusty)
                {
                    tymczasowyPlikTekstowy << liniaZNowymiDanymiAdresata;
                    czyTymczasowyPlikTekstowyJestPusty = false;
                }
                else
                {
                    tymczasowyPlikTekstowy << endl << liniaZNowymiDanymiAdresata;
                }
            }
        }
    }
    odczytywanyPlikTekstowy.close();
    tymczasowyPlikTekstowy.close();

    usunPlik(NAZWA_PLIKU);
    zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, NAZWA_PLIKU);

    cout << endl << "Dane zostaly zaktualizowane." << endl << endl;
}
