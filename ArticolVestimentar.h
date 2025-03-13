#ifndef ARTICOLVESTIMENTAR_H
#define ARTICOLVESTIMENTAR_H

#include "Produs.h"

class ArticolVestimentar: public Produs{
    string culoare = "default";
    string marca = "default";
public:
    ArticolVestimentar() = default;
    ArticolVestimentar(int , string, double, int, string, string);
    
    double calculPretFinal() const override;
    void afisareDetalii() const override;
};

#endif