#include "Produs.h"

Produs::Produs(int cod, string d, double p, int s): codUnic(cod), denumire(d), pretBaza(p), stoc(s){
    if(codUnic <= 0){
        throw invalid_argument("Codul unic al produsului este invalid!");
    }

    if(pretBaza <= 0){
        throw invalid_argument("Pretul de baza al produsului este invalid!");
    }

    if(stoc <= 0){
        throw invalid_argument("Stocul produsului este invalid!");
    }
}

int Produs::getCodUnic() const{
    return codUnic;
}

int Produs::getStoc() const{
    return stoc;
}

string Produs::getDenumire() const{
    return denumire;
}

double Produs::getPretBaza() const{
    return pretBaza;
}

void Produs::setStoc(int nouStoc){
    stoc = nouStoc;
}

void Produs::setPretBaza(int nouPretBaza){
    pretBaza = nouPretBaza;
}

void Produs::setCodUnic(int codNou){
    codUnic = codNou;
}

void Produs::afisareDetalii() const{
    cout<<"Cod Unic: "<<codUnic<<endl<<"Denumire: "<<denumire<<endl<<"Pret Baza: "<<pretBaza<<" RON"<<endl<<"Stoc: "<<stoc<<" bucati"<<endl;
}