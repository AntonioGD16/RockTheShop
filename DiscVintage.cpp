#include "DiscVintage.h"

DiscVintage::DiscVintage(int cod, string d, double pret, int s, string c, tm data, string t, string a, bool m, int coeficient): Disc(cod, d, pret, s, c, data, t, a), mintCondition(m), coeficientRaritate(coeficient){
    if(!validareData(dataVanzare)){
        throw invalid_argument("Data punerii in vanzare este invalida!");
    }

    if(mintCondition != 0 && mintCondition != 1){
        throw invalid_argument("Conditia discului este invalida!");
    }

    if(coeficientRaritate < 0 && coeficientRaritate > 5){
        throw invalid_argument("Coeficientul de raritate este invalid!");
    }
}

bool DiscVintage::validareData(const tm& data){
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

double DiscVintage::calculPretFinal() const{
    double pretFinal = Disc::calculPretFinal();
    pretFinal = pretFinal + coeficientRaritate * 15;
    return pretFinal;
}

void DiscVintage::afisareDetalii() const{
    Disc::afisareDetalii();
    cout<<"Mint Condition: "<<(mintCondition ? "Da" : "Nu")<<endl<<"Coeficient Raritate: "<<coeficientRaritate<<endl<<"Pret Final: "<<calculPretFinal()<<" RON"<<endl<<endl;
}