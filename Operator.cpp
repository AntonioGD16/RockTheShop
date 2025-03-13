#include "Operator.h"

Operator::Operator(int i, string n, string p, string c, tm data): Angajat(i, n, p, c, data){
}

double Operator::calculSalariu() const{
    time_t acum = time(nullptr);
    tm* localNow = localtime(&acum);
    int aniVechime;

    if(localNow->tm_mday >= dataAngajare.tm_mday && localNow->tm_mon >= dataAngajare.tm_mon){
        aniVechime = localNow->tm_year - dataAngajare.tm_year;
    }
    else
        aniVechime = localNow->tm_year - 1 - dataAngajare.tm_year;
    
    if(localNow->tm_mday == dataAngajare.tm_mday && localNow->tm_mon == dataAngajare.tm_mon){
        return (salariuBaza + aniVechime * 100) + bonusComenzi + 100;
    }
    else
        return (salariuBaza + aniVechime * 100) + bonusComenzi;
}

int Operator::getNumarComenzi() const{ 
    return numarComenzi;
}

int Operator::getNumarComenziProcesate() const{
    return numarComenziProcesate;
}

void Operator::asigneazaComanda(Comanda* comanda) {
    if (comanda && comanda->esteValida()) {
        numarComenzi++;
        bonusComenzi += comanda->getValoareComanda() * 0.005;
        comenziInProces.push(comanda);
        cout << "Comanda a fost asignata operatorului: " << nume << " " << prenume << endl;
    } else {
        cout << "Comanda nu este valida sau este null." << endl;
    }
}



string Operator::getNumeComplet() const{
    return nume + " " + prenume;
}

double Operator::getValoareTotalaComenziProcesate() const{
    return valoareTotalaComenziProcesate;
}

queue<Comanda*> Operator::getComenziInProces() const{
    return comenziInProces;
}

void Operator::finalizeazaComanda() {
    if (!comenziInProces.empty()) {
        int numarDiscuri = 0, numarDiscuriVintage = 0, numarArticoleVestimentare = 0;
        bool procesat = true;
        Comanda* comanda = comenziInProces.front();
        comenziInProces.pop();
        numarComenzi--;
        numarComenziProcesate++;

        const vector<Produs*> produseComanda = comanda->getProduse();

        for (Produs* produs : produseComanda) {
            if(dynamic_cast<DiscVintage*>(produs)){
                numarDiscuriVintage++;
            }
            else if(dynamic_cast<Disc*>(produs)){
                numarDiscuri++;
            }
            else if(dynamic_cast<ArticolVestimentar*>(produs)){
                numarArticoleVestimentare++;
            }
        }

        for(Produs* produs : produseComanda){
            if(numarDiscuri > 0 && dynamic_cast<Disc*>(produs)){
                if(produs->getStoc() >= numarDiscuri){
                    produs->setStoc(produs->getStoc() - 1);
                    numarDiscuri--;
                    cout<<"Operatorul "<<getNumeComplet()<<" a procesat disc: "<<produs->getDenumire()<<endl;
                }
                else{
                    cout << "Eroare: Stoc insuficient pentru disc1: "<<produs->getDenumire()<<" (Operator: "<<getNumeComplet()<<")"<<endl;
                         procesat = false;
                         numarComenziProcesate--;
                         break;
                }
            }
            else if(numarDiscuriVintage > 0 && dynamic_cast<DiscVintage*>(produs)){
                if (produs->getStoc() >= numarDiscuriVintage){
                    produs->setStoc(produs->getStoc() - 1);
                    numarDiscuriVintage--;
                    cout<<"Operatorul "<<getNumeComplet()<<" a procesat disc vintage: "<<produs->getDenumire()<<endl;
                }
                else{
                    cout<<"Eroare: Stoc insuficient pentru disc vintage: "<<produs->getDenumire()<<" (Operator: "<<getNumeComplet()<<")"<<endl;
                         procesat = false;
                         numarComenziProcesate--;
                         break;
                }
            }
            else if(numarArticoleVestimentare > 0 && dynamic_cast<ArticolVestimentar*>(produs)){
                if(produs->getStoc() >= numarArticoleVestimentare){
                    produs->setStoc(produs->getStoc() - 1);
                    numarArticoleVestimentare--;
                    cout<<"Operatorul "<<getNumeComplet()<<" a procesat articol vestimentar: "<<produs->getDenumire()<<endl;
                }
                else{
                    cout<<"Eroare: Stoc insuficient pentru articol vestimentar: "<<produs->getDenumire()<<" (Operator: "<<getNumeComplet()<<")"<<endl;
                         procesat = false;
                         numarComenziProcesate--;
                         break;
                }
            }
        }

        if(procesat){
            cout<<"Operatorul "<<getNumeComplet()<<" a finalizat comanda cu valoarea de "<<comanda->getValoareComanda()<<" RON."<<endl;
                valoareTotalaComenziProcesate += comanda->getValoareComanda();
        }

    }
    else{
        cout<<"Operatorul "<<getNumeComplet()<<" nu are comenzi de finalizat."<<endl;
    }
}
