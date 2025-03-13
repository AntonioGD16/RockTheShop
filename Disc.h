#ifndef DISC_H
#define DISC_H

#include "Produs.h"

class Disc: public Produs{
protected:
    string casaDisc = "default";
    tm dataVanzare;
    string trupa = "default";
    string album = "default";
public:
    Disc() = default;
    Disc(int , string, double , int , string, tm, string, string);

    bool validareData(const tm& );
    double calculPretFinal() const override;
    void afisareDetalii() const override;
};

#endif