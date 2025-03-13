#ifndef COMANDA_H
#define COMANDA_H

#include "Produs.h"
#include <queue>

class Comanda{
    vector<Produs*> discuri;
    vector<Produs*> discuriVintage;
    vector<Produs*> articoleVestimentare;
    time_t dataPrimire;
    int durataSolutionare = 0;
    double valoareComanda = 0.0;

public:
    Comanda() = default;
    Comanda(vector<Produs*>, vector<Produs*>, vector<Produs*>, int);

    bool esteValida() const;

    double getValoareComanda() const;
    int getDurataSolutionare() const;
    time_t getDataPrimire() const;
    vector<Produs*> getProduse() const;

    void afisareDetalii() const;
};

#endif