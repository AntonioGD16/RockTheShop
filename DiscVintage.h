#ifndef DISCVINTAGE_H
#define DISCVINTAGE_H

#include "Produs.h"
#include "Disc.h"

class DiscVintage: public Disc{
    bool mintCondition = false;
    int coeficientRaritate = 0;
public:
    DiscVintage() = default;
    DiscVintage(int , string , double , int , string , tm , string , string , bool , int );

    bool validareData(const tm& );
    double calculPretFinal() const override;
    void afisareDetalii() const override;
};

#endif