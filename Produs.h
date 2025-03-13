#ifndef PRODUS_H
#define PRODUS_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class Produs{
protected:
    int codUnic = 0;
    string denumire = "default";
    double pretBaza = 0.0;
    int stoc = 0;
public:
    Produs() = default;
    Produs(int , string, double, int);
    
    int getCodUnic() const;
    int getStoc() const;
    string getDenumire() const;
    double getPretBaza() const;
    
    virtual ~Produs() = default;

    void setPretBaza(int );
    void setStoc(int );
    void setCodUnic(int );

    virtual double calculPretFinal() const = 0;
    virtual void afisareDetalii() const;
};

#endif