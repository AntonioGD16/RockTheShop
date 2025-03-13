#include "Produs.h"
#include "Disc.h"
#include "DiscVintage.h"
#include "ArticolVestimentar.h"
#include "Comanda.h"
#include "Angajat.h"
#include "Manager.h"
#include "Operator.h"
#include "Asistent.h"
#include "Magazin.h"

vector<Angajat*> citesteAngajatiDinFisier(const string& numeFisier){
    ifstream fisier(numeFisier);
    vector<Angajat*> angajati;

    if(!fisier.is_open()){
        cerr<<"Eroare la deschiderea fișierului"<<numeFisier<<endl;
        exit(1);
    }

    string tip, nume, prenume, cnp;
    int id;
    tm dataAngajare = {};
    while(fisier>>tip>>id>>nume>>prenume>>cnp>>dataAngajare.tm_year>>dataAngajare.tm_mon>>dataAngajare.tm_mday){
        dataAngajare.tm_year -= 1900;
        dataAngajare.tm_mon -= 1;

        if(tip == "Manager"){
            try{
                angajati.push_back(new Manager(id, nume, prenume, cnp, dataAngajare));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "Operator"){
            try{
                angajati.push_back(new Operator(id, nume, prenume, cnp, dataAngajare));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "Asistent"){
            try{
                angajati.push_back(new Asistent(id, nume, prenume, cnp, dataAngajare));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
    }

    fisier.close();
    return angajati;
}

vector<Produs*> citesteProduseDinFisier(const string& numeFisier){
    ifstream fisier(numeFisier);
    vector<Produs*> produse;

    if(!fisier.is_open()){
        cerr<<"Eroare la deschiderea fișierului"<<numeFisier<<endl;
        exit(1);
    }

    string tip, denumire, casaDisc, trupa, album, culoare, marca;
    int codUnic, stoc, coeficientRaritate;
    double pretBaza;
    bool mintCondition;
    tm dataVanzare = {};

    while(fisier>>tip>>codUnic>>denumire>>pretBaza>>stoc){
        if(tip == "Disc"){
            fisier>>casaDisc>>dataVanzare.tm_year>>dataVanzare.tm_mon>>dataVanzare.tm_mday>>trupa>>album;
            dataVanzare.tm_year -= 1900;
            dataVanzare.tm_mon -= 1;
            try{
                produse.push_back(new Disc(codUnic, denumire, pretBaza, stoc, casaDisc, dataVanzare, trupa, album));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "DiscVintage"){
            fisier>>casaDisc>>dataVanzare.tm_year>>dataVanzare.tm_mon>>dataVanzare.tm_mday>>trupa>>album>>mintCondition>>coeficientRaritate;
            dataVanzare.tm_year -= 1900;
            dataVanzare.tm_mon -= 1;
            try{
                produse.push_back(new DiscVintage(codUnic, denumire, pretBaza, stoc, casaDisc, dataVanzare, trupa, album, mintCondition, coeficientRaritate));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "ArticolVestimentar"){
            fisier>>culoare>>marca;
            try{
                produse.push_back(new ArticolVestimentar(codUnic, denumire, pretBaza, stoc, culoare, marca));
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
    }

    fisier.close();
    return produse;
}

vector<Comanda*> citesteComenziDinFisier(const string& numeFisier, const vector<Produs*>& produse){
    ifstream fisier(numeFisier);
    vector<Comanda*> comenzi;

    if(!fisier.is_open()){
        cerr<<"Eroare la deschiderea fisierului"<<numeFisier<<endl;
        exit(1);
    }

    int durataSolutionare, numarDiscuri, numarDiscuriVintage, numarArticole, codUnic;
    while(fisier>>durataSolutionare>>numarDiscuri>>numarDiscuriVintage>>numarArticole){
        vector<Produs*> discuri;
        vector<Produs*> discuriVintage;
        vector<Produs*> articole;
        bool discGasit = true;
        bool discVintageGasit = true;
        bool articolGasit = true;

        if(numarArticole <= 0 && numarDiscuri <= 0 && numarDiscuriVintage){
            cout<<"Comanda invalida!"<<endl;
            continue;
        }

        for(int i = 0; i < numarDiscuri; i++){
            fisier>>codUnic;
            auto it = find_if(produse.begin(), produse.end(), [codUnic](Produs* produs) { return produs->getCodUnic() == codUnic;});
            if(it != produse.end()){
                discuri.push_back(*it);
            }
            else{
                cout<<"Produsul nu a fost gasit!"<<endl;
                discGasit = false;
                break;
            }
        }

        if(!discGasit){
            cout<<"Comanda ignorata"<<endl;
            continue;
        }

        for(int i = 0; i < numarDiscuriVintage; i++){
            fisier>>codUnic;
            auto it = find_if(produse.begin(), produse.end(), [codUnic](Produs* produs) { return produs->getCodUnic() == codUnic;});
            if(it != produse.end()){
                discuri.push_back(*it);
            }
            else{
                cout<<"Produsul nu a fost gasit!"<<endl;
                discVintageGasit = false;
                break;
            }
        }

        if(!discVintageGasit){
            cout<<"Comanda ignorata"<<endl;
            continue;
        }

        for(int i = 0; i < numarArticole; i++){
            fisier>>codUnic;
            auto it = find_if(produse.begin(), produse.end(), [codUnic](Produs* produs) { return produs->getCodUnic() == codUnic;});
            if(it != produse.end()){
                articole.push_back(*it);
            }
            else{
                cout<<"Produsul nu a fost gasit!"<<endl;
                articolGasit = false;
                break;
            }
        }

        if(!articolGasit){
            cout<<"Comanda ignorata"<<endl;
            continue;
        }

        try{
            comenzi.push_back(new Comanda(discuri, discuriVintage, articole, durataSolutionare));
        }
        catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
        }
    }

    fisier.close();
    return comenzi;
}

int main(){
    vector<Angajat*> angajati = citesteAngajatiDinFisier("Teste/Angajati_Test5.txt");
    vector<Produs*> produse = citesteProduseDinFisier("Teste/Produse_Test1.txt");
    vector<Comanda*> comenzi = citesteComenziDinFisier("Teste/Comenzi_Test1.txt", produse);

    Magazin magazin(angajati, produse, comenzi);

    bool dejaProcesate = false;

    if(!magazin.verificaFunctionare()){
        cout<<"Corectati problemele identificate pentru ca magazinul sa poata functiona."<<endl;
        return 1;
    }

    int optiune;
    do{
        cout<<endl<<"Meniu:"<<endl;
        cout<<"1. Gestiune Angajati"<<endl;
        cout<<"2. Gestiune Stoc"<<endl;
        cout<<"3. Procesare Comenzi"<<endl;
        cout<<"4. Raportare"<<endl;
        cout<<"0. Iesire"<<endl;
        cout<<"Optiunea dvs.: ";
        cin>>optiune;
        cout<<endl;

        switch (optiune){
        case 1:{
            int optAngajati;
            cout<<"1. Adăugare angajat"<<endl;
            cout<<"2. Ștergere angajat"<<endl;
            cout<<"3. Modificare angajat"<<endl;
            cout<<"4. Afișare angajat"<<endl;
            cout<<"5. Afișare toți angajații"<<endl;
            cout<<"0. Iesire"<<endl;
            cout<<"Optiunea dvs.: ";
            cin>>optAngajati;
            cout<<endl;

            switch (optAngajati){
            case 1:{
                Angajat* angajat = nullptr;
                magazin.adaugaAngajat(angajat);
                break;
            }
            case 2:{
                int id;
                cout<<"Introduceti ID-ul angajatului de sters: ";
                cin>>id;
                cout<<endl;
                magazin.stergeAngajat(id);
                break;
            }
            case 3:{
                int id;
                cout<<"Introduceti ID-ul angajatului de modificat: ";
                cin>>id;
                cout<<endl;
                magazin.modificaAngajat(id);
                break;
            }
            case 4:{
                int id;
                cout<<"Introduceti ID-ul angajatului de afisat: ";
                cin>>id;
                cout<<endl;
                magazin.afisareAngajat(id);
                break;
            }
            case 5:
                magazin.afisareAngajati();
                break;
            case 0:
                break;
            default:
                cout<<"Optiune invalida."<<endl;
            }
            break;
        }
        case 2:{
            int optProduse;
            cout<<"1. Adăugare produs"<<endl;
            cout<<"2. Ștergere produs"<<endl;
            cout<<"3. Modificare produs"<<endl;
            cout<<"4. Afișare produs"<<endl;
            cout<<"5. Afișare toate produsele"<<endl;
            cout<<"0. Iesire"<<endl;
            cout<<"Optiunea dvs.: ";
            cin>>optProduse;
            cout<<endl;

            switch (optProduse){
            case 1:{
                Produs* produs = nullptr;
                magazin.adaugaProdus(produs);
                break;
            }
            case 2:{
                int codUnic;
                cout<<"Introduceti codul unic al produsului de sters: ";
                cin>>codUnic;
                cout<<endl;
                magazin.stergeProdus(codUnic);
                break;
            }
            case 3:{
                int codUnic;
                cout<<"Introduceti codul unic al produsului de modificat: ";
                cin>>codUnic;
                cout<<endl;
                magazin.modificaProdus(codUnic);
                break;
            }
            case 4:{
                int codUnic;
                cout<<"Introduceti codul unic al produsului de afisat: ";
                cin>>codUnic;
                cout<<endl;
                magazin.afisareProdus(codUnic);
                break;
            }
            case 5:
                magazin.afisareProduse();
                break;
            case 0:
                break;
            default:
                cout<<"Optiune invalida."<<endl;
            }
            break;
        }
        case 3:
            if(!dejaProcesate){
                magazin.procesareComenzi();
                dejaProcesate = true;
            }
            else{
                cout<<"Comenzile au fost deja procesate"<<endl;
            }
            break;
        case 4:{
            int optRaportare;
            cout<<"1. Angajatul cu cele mai multe comenzi procesate"<<endl;
            cout<<"2. Top 3 angajati care au gestionat cele mai valoroase comenzi"<<endl;
            cout<<"3. Top 3 angajati cu cel mai mare salariu in luna curenta"<<endl;
            cout<<"0. Iesire"<<endl;
            cout<<"Optiunea dvs.: ";
            cin>>optRaportare;
            cout<<endl;

            switch (optRaportare){
            case 1:
                magazin.genereazaRaportAngajatMaxComenzi("angajat_max_comenzi.csv");
                cout<<"Raportul pentru angajatul cu cele mai multe comenzi procesate a fost generat in 'angajat_max_comenzi.csv'."<<endl;
                break;
            case 2:
                magazin.genereazaRaportTop3AngajatiValoare("top3_valoare_comenzi.csv");
                cout<<"Raportul pentru top 3 angajati cu cele mai valoroase comenzi a fost generat in 'top3_valoare_comenzi.csv'."<<endl;
                break;
            case 3:
                magazin.genereazaRaportTop3AngajatiSalariu("top3_salariu.csv");
                cout<<"Raportul pentru top 3 angajati cu cel mai mare salariu a fost generat in 'top3_salariu.csv'."<<endl;
                break;
            case 0:
                break;
            default:
                cout<<"Optiune invalida."<<endl;
            }
            break;
        }

        case 0:
            cout<<"La revedere!"<<endl;
            break;
        default:
            cout<<"Optiune invalida."<<endl;
        }
    }while(optiune != 0);

    return 0;
}
