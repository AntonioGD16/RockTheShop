#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <cctype>
#include "Comanda.h"

class Angajat{
protected:
    int id = 0;
    string nume = "default";
    string prenume = "default";
    string cnp = "default";
    tm dataAngajare;
    double salariuBaza = 3500.0;
public:
    Angajat() = default;
    Angajat(int ,string ,string ,string ,tm );
    virtual ~Angajat() = default;

    virtual double calculSalariu() const = 0;
    virtual void afisareDetalii() const;
    void schimbareNume(const string& , const string& );
    static bool validareCNP(const string& );
    bool validareData(const tm& );
    int getId() const;
    string getCNP() const;
    string getNume() const;
    string getPrenume() const;

    void setDataAngajare(tm );
    void setId(int ) ;
};

#endif