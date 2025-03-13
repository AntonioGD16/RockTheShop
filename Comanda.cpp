#include "Comanda.h"

Comanda::Comanda(vector<Produs*> d, vector<Produs*> dv, vector<Produs*> articole, int durata): durataSolutionare(durata){
    dataPrimire = time(nullptr);

    if(d.size() + dv.size() <= 5){
        discuri = d;
        discuriVintage = dv;
    }
    else{
        throw invalid_argument("Comanda trebuie sa contina maxim 5 discuri. Comanda nu este valida!");
    }

    if(articole.size() <= 3){
        articoleVestimentare = articole;
    }
    else{
        throw invalid_argument("Comanda trebuie sa contina maxim 3 articole vestimentare. Comanda nu este valida!");
    }

    for(int i = 0; i < discuri.size(); i++){
        valoareComanda = valoareComanda + discuri[i]->calculPretFinal();
    }

    for(int i = 0; i < discuriVintage.size(); i++){
        valoareComanda = valoareComanda + discuriVintage[i]->calculPretFinal();
    }

    for (int i = 0; i < articoleVestimentare.size(); i++){ 
        valoareComanda = valoareComanda + articoleVestimentare[i]->calculPretFinal();
    }

    if(!esteValida()){
        throw invalid_argument("Valoarea comenzii este de minim 100 RON. Comanda nu este valida!");
    }
}

bool Comanda::esteValida() const{
    return valoareComanda >= 100.0;
}

void Comanda::afisareDetalii() const{
    cout<<"Data primire: "<<ctime(&dataPrimire);
    cout<<"Durata solutionare: "<<durataSolutionare<<" zile"<<endl;
    cout<<"Valoare comanda: "<<valoareComanda<<" lei"<<endl;
    cout<<"Produse in comanda:"<<endl;

    for(Produs* produs : discuri){
        cout<<" - Disc: "<< produs->getDenumire()<<" | Pret: "<<produs->getPretBaza()<<" lei"<<endl;
    }

    for(Produs* produs : articoleVestimentare){
        cout<<" - Articol vestimentar: "<<produs->getDenumire()<<" | Pret: "<< produs->getPretBaza()<<" lei"<<endl;
    }
}

double Comanda::getValoareComanda() const{
    return valoareComanda;
}

int Comanda::getDurataSolutionare() const{
    return durataSolutionare;
}

time_t Comanda::getDataPrimire() const{
    return dataPrimire;
}

vector<Produs*> Comanda::getProduse() const{
    vector<Produs*> toateProdusele = discuri;
    toateProdusele.insert(toateProdusele.end(), discuriVintage.begin(), discuriVintage.end());
    toateProdusele.insert(toateProdusele.end(), articoleVestimentare.begin(), articoleVestimentare.end());
    return toateProdusele;
}
