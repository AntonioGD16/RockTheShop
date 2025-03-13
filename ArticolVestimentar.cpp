#include "ArticolVestimentar.h"

ArticolVestimentar::ArticolVestimentar(int cod, string d, double p, int s, string c, string m): Produs(cod, d, p, s), culoare(c), marca(m){
}

double ArticolVestimentar::calculPretFinal() const{
    return pretBaza + 20;
}

void ArticolVestimentar::afisareDetalii() const{
    Produs::afisareDetalii();
    cout<<"Culoare: "<<culoare<<endl<<"Marca: "<<marca<<endl<<"Pret Final: "<<calculPretFinal()<<" RON"<<endl<<endl;
}