#include "Disc.h"

Disc::Disc(int cod, string d, double p, int s, string c, tm data, string t, string a): Produs(cod, d, p, s), casaDisc(c), dataVanzare(data), trupa(t), album(a){
    if(!validareData(dataVanzare)){
        throw invalid_argument("Data punerii in vanzare este invalida!");
    }
}

bool Disc::validareData(const tm& data){
    if(data.tm_year < 0 || data.tm_mon < 0 || data.tm_mon > 11 || data.tm_mday < 1 || data.tm_mday > 31){
        return false;
    }

    if((data.tm_mon == 3 || data.tm_mon == 5 || data.tm_mon == 8 || data.tm_mon == 10) && data.tm_mday > 30){
        return false;
    }

    bool anBisect = ((data.tm_year + 1900) % 4 == 0 && ((data.tm_year + 1900) % 100 != 0 || (data.tm_year + 1900) % 400 == 0));
    if(data.tm_mon == 1){
        if(anBisect && data.tm_mday > 29){
            return false;
        }
        if(!anBisect && data.tm_mday > 28){
            return false;
        }
    }

    return true;
}

double Disc::calculPretFinal() const{
    return pretBaza + 5;
}

void Disc::afisareDetalii() const{
    Produs::afisareDetalii();
    cout<<"Casa Disc: "<<casaDisc<<endl<<"Trupa: "<<trupa<<endl<<"Album: "<<album<<endl<<"Pret Final: "<<calculPretFinal()<<" RON"<<endl<<endl;
}