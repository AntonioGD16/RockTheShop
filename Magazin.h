#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "Produs.h"
#include "ArticolVestimentar.h"
#include "Disc.h"
#include "DiscVintage.h"
#include "Angajat.h" 
#include "Manager.h"
#include "Operator.h"
#include "Asistent.h"
#include "Comanda.h"
#include <fstream>

class Magazin {
    vector<Angajat*> angajati;
    vector<Produs*> produse;
    vector<Comanda*> comenzi;

public:
    Magazin() = default;
    Magazin(vector<Angajat*>, vector<Produs*>, vector<Comanda*>);
    int calculVarsta(const string& );
    void adaugaAngajat(Angajat* );
    void stergeAngajat(int );
    void modificaAngajat(int );
    void afisareAngajat(int ) const;
    void afisareAngajati() const;

    void adaugaProdus(Produs* );
    void stergeProdus(int );
    void modificaProdus(int );
    void afisareProdus(int ) const;
    void afisareProduse() const;

    bool verificaStocProduse(Comanda* );

    void procesareComenzi();
    void finalizeazaComenziInProces();
    bool verificaFunctionare() const;

    void genereazaRaportTop3AngajatiSalariu(const string& ) const;
    void genereazaRaportTop3AngajatiValoare(const string& ) const;
    void genereazaRaportAngajatMaxComenzi(const string& ) const;

    ~Magazin();
};

#endif