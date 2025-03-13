#include "Angajat.h"

Angajat::Angajat(int i, string n, string p, string c, tm data): id(i), nume(n), prenume(p), cnp(c), dataAngajare(data){
    if(!validareCNP(cnp)){
        throw invalid_argument("CNP invalid!");
    }

    if(!validareData(dataAngajare)){
        throw invalid_argument("Data angajarii este invalida");
    }

    if(nume.length() < 3 || nume.length() > 30 || prenume.length() < 3 || prenume.length() > 30){
        throw invalid_argument("Nume sau prenume invalid!");
    }
}

void Angajat::schimbareNume(const string& numeNou, const string& prenumeNou){
    if(numeNou.length() < 3 || numeNou.length() > 30 || prenumeNou.length() < 3 || prenumeNou.length() > 30){
        throw invalid_argument("Nume sau prenume invalid!");
    }
    nume = numeNou;
    prenume = prenumeNou;
}

bool Angajat::validareCNP(const string& cnp){
    if(cnp.length() != 13 || !all_of(cnp.begin(), cnp.end(), ::isdigit)){
        return false;
    }

    int control[] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9};
    int suma = 0;
    for(int i = 0; i < 12; i++){
        suma += (cnp[i] - '0') * control[i];
    }
    int cifraControl = suma % 11;
    if(cifraControl == 10){
        cifraControl = 1;
    }
        
    return cifraControl == (cnp[12] - '0');
}

bool Angajat::validareData(const tm& data){
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

int Angajat::getId() const{
    return id;
}

string Angajat::getCNP() const{
    return cnp;
}

string Angajat::getNume() const{
    return nume;
}

string Angajat::getPrenume() const{
    return prenume;
}

void Angajat::setDataAngajare(tm data) {
    dataAngajare = data;
}

void Angajat::setId(int idNou) {
    id = idNou;
}

void Angajat::afisareDetalii() const{
    cout<<"ID: "<<id<<endl<<"Nume: "<<nume<<" "<<prenume<<endl<<"CNP: "<<cnp<<endl<<"Data Angajare: "<<dataAngajare.tm_mday<<"-"<<dataAngajare.tm_mon + 1<<"-"<< dataAngajare.tm_year + 1900<<endl<<"Salariu: "<<calculSalariu()<<endl<<endl;        
}