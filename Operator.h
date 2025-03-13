#ifndef OPERATOR_H
#define OPERATOR_H

#include "Angajat.h"
#include "Disc.h"
#include "DiscVintage.h"
#include "ArticolVestimentar.h"

class Operator: public Angajat{
    double bonusComenzi = 0.0;
    int numarComenzi = 0;
    int numarComenziProcesate = 0;
    double valoareTotalaComenziProcesate = 0.0;
    queue<Comanda*> comenziInProces;
public:
    Operator() = default;
    Operator(int id, string, string, string, tm);

    double calculSalariu() const override;
    void finalizeazaComanda();
    void asigneazaComanda(Comanda* );
    
    int getNumarComenzi() const;
    int getNumarComenziProcesate() const;
    string getNumeComplet() const;
    queue<Comanda*> getComenziInProces() const;
    double getValoareTotalaComenziProcesate() const;
};

#endif