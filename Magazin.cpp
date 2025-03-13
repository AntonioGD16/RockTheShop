#include "Magazin.h"

Magazin::Magazin(vector<Angajat*> a, vector<Produs*> p, vector<Comanda*> c): angajati(a), produse(p), comenzi(c){
}

void Magazin::adaugaAngajat(Angajat* angajat){
    time_t t = time(nullptr);
    tm *dataCurenta = localtime(&t);

    int idNou = 1;
    for(const auto &angajat : angajati){
        if(angajat->getId() >= idNou){
            idNou = angajat->getId() + 1;
        }
    }

    string nume, prenume, cnp, tip;
    cout<<"Introduceti tipul angajatului (Manager/Operator/Asistent): ";
    cin>>tip;
    cout<<"Introduceti numele: ";
    cin>>nume;
    cout<<"Introduceti prenumele: ";
    cin.ignore();
    getline(cin, prenume);
    cout<<"Introduceti CNP-ul: ";
    cin>>cnp;
    if(calculVarsta(cnp) >= 18){
        if(tip == "Manager"){
            try{
                angajat = new Manager(idNou, nume, prenume, cnp, *dataCurenta);
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "Operator"){
            try{
                angajat = new Operator(idNou, nume, prenume, cnp, *dataCurenta);
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else if(tip == "Asistent"){
            try{
                angajat = new Asistent(idNou, nume, prenume, cnp, *dataCurenta);
            }
            catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
            }
        }
        else{
            cout<<"Tip de angajat invalid."<<endl;
            return;
        }

        if(angajat){
            angajati.push_back(angajat);
            cout<<"Angajatul a fost adaugat cu succes. ID-ul alocat este: "<<idNou<<endl;
        }
    }
    else{
        cout<<"Angajatul nu a fost adaugat. Trebuie sa aiba peste 18 ani."<<endl;
    }
}

int Magazin::calculVarsta(const string& cnp){
    if(!Angajat::validareCNP(cnp)){
        throw invalid_argument("CNP invalid!");
    }

    int anNastere = 1900;
    if(cnp[0] == '1' || cnp[0] == '2'){
        anNastere += stoi(cnp.substr(1, 2));
    }
    else if(cnp[0] == '5' || cnp[0] == '6'){
        anNastere = 2000 + stoi(cnp.substr(1, 2));
    }

    int lunaNastere = stoi(cnp.substr(3, 2));
    int ziNastere = stoi(cnp.substr(5, 2));

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int varsta = (now->tm_year + 1900) - anNastere;
    if((now->tm_mon + 1 < lunaNastere) || (now->tm_mon + 1 == lunaNastere && now->tm_mday < ziNastere)){
        varsta--;
    }

    return varsta;
}


void Magazin::stergeAngajat(int id){
    auto it = remove_if(angajati.begin(), angajati.end(), [id](Angajat* angajat){ return angajat->getId() == id;});
    if(it != angajati.end()){
        delete *it;
        angajati.erase(it);
        cout<<"Angajatul cu ID-ul "<<id<< " a fost sters."<<endl;
    }
    else{
        cout<<"Eroare: Angajatul cu ID-ul "<<id<< " nu exista."<<endl;
    }
}

void Magazin::modificaAngajat(int id) {
    auto it = find_if(angajati.begin(), angajati.end(), [id](Angajat* angajat){ return angajat->getId() == id;});
    if(it != angajati.end()){
        Angajat* angajat = *it;
        string nume, prenume;
        cout<<"Introdu noul nume: ";
        cin>>nume;
        cout<<"Introdu noul prenume: ";
        cin.ignore();
        getline(cin, prenume);
        angajat->schimbareNume(nume, prenume);
        cout<<"Angajat modificat cu succes."<<endl;
    }
    else{
        cout<<"Eroare: Angajatul cu ID-ul "<<id<<" nu exista."<<endl;
    }
}

void Magazin::afisareAngajat(int id) const{
    auto it = find_if(angajati.begin(), angajati.end(), [id](Angajat* angajat){ return angajat->getId() == id;});
    if(it != angajati.end()){
        (*it)->afisareDetalii();
    }
    else{
        cout<<"Eroare: Angajatul cu ID-ul "<<id<<" nu exista."<<endl;
    }
}

void Magazin::afisareAngajati() const{
    if(angajati.empty()){
        cout<<"Nu exista angajati in sistem."<<endl;
        return;
    }
    for(auto angajat : angajati){
            angajat->afisareDetalii();
    }
}

void Magazin::adaugaProdus(Produs* produs){
    string tip, denumire;
    int stoc;
    double pretBaza;
    cout<<"Introduceti tipul produsului (Disc/DiscVintage/ArticolVestimentar): ";
    cin>>tip;
    cout<<"Introduceti denumirea: ";
    cin>>denumire;
    cout<< "Introduceti pretul de baza: ";
    cin>>pretBaza;
    cout<<"Introduceti stocul: ";
    cin>>stoc;

    int codNou = 1;
    for(const auto& produs : produse){
        if(produs->getCodUnic() >= codNou){
            codNou = produs->getCodUnic() + 1;
        }
    }

    if(tip == "Disc"){
        string casaDisc, trupa, album;
        tm dataVanzare;
        cout<<"Introduceti casa de discuri: ";
        cin>>casaDisc;
        cout<<"Introduceti trupa: ";
        cin>>trupa;
        cout<<"Introduceti albumul: ";
        cin>>album;
        cout<< "Introduceti data vanzarii (an luna zi): ";
        cin>>dataVanzare.tm_year>>dataVanzare.tm_mon>>dataVanzare.tm_mday;
        dataVanzare.tm_year -= 1900;
        dataVanzare.tm_mon -= 1;
        try{
            produs = new Disc(codNou, denumire, pretBaza, stoc, casaDisc, dataVanzare, trupa, album);
        }
        catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
        }
    }
    else if(tip == "DiscVintage"){
        string casaDisc, trupa, album;
        bool mintCondition;
        int coeficientRaritate;
        tm dataVanzare;
        cout<<"Introduceti casa de discuri: ";
        cin>>casaDisc;
        cout<<"Introduceti trupa: ";
        cin>>trupa;
        cout<<"Introduceti albumul: ";
        cin>>album;
        cout<<"Introduceti data vanzarii (an luna zi): ";
        cin>>dataVanzare.tm_year>>dataVanzare.tm_mon>>dataVanzare.tm_mday;
        dataVanzare.tm_year -= 1900;
        dataVanzare.tm_mon -= 1;
        cout<<"Este mint condition (1/0): ";
        cin>>mintCondition;
        cout<<"Introduceti coeficientul de raritate: ";
        cin>>coeficientRaritate;
        try{
            produs = new DiscVintage(codNou, denumire, pretBaza, stoc, casaDisc, dataVanzare, trupa, album, mintCondition, coeficientRaritate);
        }
        catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
        }
    }
    else if(tip == "ArticolVestimentar"){
        string culoare, marca;
        cout<<"Introduceti culoarea: ";
        cin>>culoare;
        cout<<"Introduceti marca: ";
        cin>>marca;
        try{
            produs = new ArticolVestimentar(codNou, denumire, pretBaza, stoc, culoare, marca);
        }
        catch(const invalid_argument& e){
                cout<<"Eroare: "<<e.what()<<endl;
        }
    }
    else{
        cout<<"Produsul nu a putut fi adugat."<<endl;
        return;
    }
    if(produs){
        produse.push_back(produs);
        cout<<"Produs adaugat cu succes."<<endl;
    }
    else
        cout<<"Produsul nu a putut fi adugat."<<endl;
}

void Magazin::stergeProdus(int codUnic){
    auto it = remove_if(produse.begin(), produse.end(), [codUnic](Produs* produs){ return produs->getCodUnic() == codUnic;});
    if(it != produse.end()){
        delete *it;
        produse.erase(it);
        cout<<"Produsul cu codul "<<codUnic<<" a fost sters."<<endl;
    }
    else{
        cout<<"Eroare: Produsul cu codul "<<codUnic<<" nu exista."<<endl;
    }
}

void Magazin::modificaProdus(int codUnic) {
    auto it = find_if(produse.begin(), produse.end(), [codUnic](Produs* produs){ return produs->getCodUnic() == codUnic;});
    if(it != produse.end()){
        Produs* produs = *it;
        double pretNou;
        int stocNou;
        cout<<"Introdu noul pret: ";
        cin>>pretNou;
        cout<<"Introdu noul stoc: ";
        cin>>stocNou;
        produs->setPretBaza(pretNou);
        produs->setStoc(stocNou);
        cout<<"Produs modificat cu succes."<<endl;
    }
    else{
        cout<<"Eroare: Produsul cu codul "<<codUnic<<" nu exista."<<endl;
    }
}

void Magazin::afisareProdus(int codUnic) const{
    auto it = find_if(produse.begin(), produse.end(), [codUnic](Produs* produs){ return produs->getCodUnic() == codUnic;});
    if(it != produse.end()){
        (*it)->afisareDetalii();
    }
    else{
        cout<<"Eroare: Produsul cu codul "<<codUnic<<" nu exista"<<endl;
    }
}

void Magazin::afisareProduse() const{
    if(produse.empty()){
        cout<<"Nu exista produse in stoc."<<endl;
        return;
    }
    for(auto produs : produse){
        produs->afisareDetalii();
    }
}

void Magazin::finalizeazaComenziInProces(){
    for(Angajat* angajat : angajati){
        Operator* op = dynamic_cast<Operator*>(angajat);
        if(op != nullptr){
            while(!op->getComenziInProces().empty()){
                op->finalizeazaComanda();
            }
        }
    }
}


void Magazin::procesareComenzi() {
    queue<Comanda*> coadaAsteptare;
    int indexOperatorCurent = 0;

    for(int i = 0; i < comenzi.size(); i++){
        if(!comenzi[i]->esteValida()){
            cout<<"Comanda invalida. Nu poate fi procesata."<<endl;
            continue;
        }

        bool areProduseInStoc = true;
        for(Produs* produs : comenzi[i]->getProduse()){
            if(produs->getStoc() <= 0){
                cout<<"Produsul "<<produs->getDenumire()<<" nu mai este in stoc. Comanda nu va fi procesata."<<endl;
                areProduseInStoc = false;
                break;
            }
        }
        if (!areProduseInStoc){
            continue;
        }

        Operator* operatorDisponibil = nullptr;
        int numarAngajati = angajati.size();
        for(int j = 0; j < numarAngajati; j++){
            int index = (indexOperatorCurent + j) % numarAngajati;
            Operator* op = dynamic_cast<Operator*>(angajati[index]);
            if(op != nullptr && op->getNumarComenzi() < 3){
                operatorDisponibil = op;
                indexOperatorCurent = (index + 1) % numarAngajati;
                break;
            }
        }

        if(operatorDisponibil != nullptr){
            operatorDisponibil->asigneazaComanda(comenzi[i]);
        }
        else{
            cout<<"Nu exista operatori disponibili. Comanda va fi plasata in asteptare."<<endl;
            coadaAsteptare.push(comenzi[i]);
        }
    }

    while(!coadaAsteptare.empty()){

        Comanda* comanda = coadaAsteptare.front();
        coadaAsteptare.pop();

        if(verificaStocProduse(comanda)){
            finalizeazaComenziInProces();
        }

        Operator* operatorDisponibil = nullptr;
        int numarAngajati = angajati.size();
        for(int j = 0; j < numarAngajati; j++){
            int index = (indexOperatorCurent + j) % numarAngajati;
            Operator* op = dynamic_cast<Operator*>(angajati[index]);
            if(op != nullptr && op->getNumarComenzi() < 3){
                operatorDisponibil = op;
                indexOperatorCurent = (index + 1) % numarAngajati;
                break;
            }
        }

        if(operatorDisponibil != nullptr){
            operatorDisponibil->asigneazaComanda(comanda);
        }
    }

    bool maiSuntComenziInProces;
    do{
        maiSuntComenziInProces = false;
        for(int i = 0; i < angajati.size(); i++){
            Operator* op = dynamic_cast<Operator*>(angajati[i]);
            if(op != nullptr && op->getNumarComenzi() > 0){
                maiSuntComenziInProces = true;
                break;
            }
        }
        finalizeazaComenziInProces();
    } while(maiSuntComenziInProces);

    cout<<"Toate comenzile au fost procesate cu succes."<<endl;
}

bool Magazin::verificaStocProduse(Comanda* comanda){
    int numarDiscuri = 0, numarDiscuriVintage = 0, numarArticoleVestimentare = 0;
    vector<Produs*> produseComanda = comanda->getProduse();

    for(Produs* produs : produseComanda) {
        if (dynamic_cast<DiscVintage*>(produs)){
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
        if(dynamic_cast<DiscVintage*>(produs)){
            if(produs->getStoc() < numarDiscuriVintage){
                cout << "Stoc insuficient pentru disc vintage: " << produs->getDenumire()<<endl;
                return false;
            }
        }
        else if(dynamic_cast<Disc*>(produs)){
            if(produs->getStoc() < numarDiscuri){
                cout<<"Stoc insuficient pentru disc: "<<produs->getDenumire()<<endl;
                return false;
            }
        }
        else if(dynamic_cast<ArticolVestimentar*>(produs)){
            if(produs->getStoc() < numarArticoleVestimentare){
                cout<<"Stoc insuficient pentru articol vestimentar: "<<produs->getDenumire()<<endl;
                return false;
            }
        }
    }

    return true;
}

bool Magazin::verificaFunctionare() const{
    int nrManageri = 0, nrOperatori = 0, nrAsistenti = 0;
    for(const auto& angajat : angajati){
        if (dynamic_cast<Manager*>(angajat)){
            nrManageri++;
        }
        else if(dynamic_cast<Operator*>(angajat)){
            nrOperatori++;
        }
        else if(dynamic_cast<Asistent*>(angajat)){
            nrAsistenti++;
        }
    }

    if(nrManageri < 1){
        cout<<"Magazinul nu poate functiona: magazinul trebuie sa aiba cel putin un manager."<<endl;
        return false;
    }
    if(nrOperatori < 3){
        cout<<"Magazinul nu poate functiona: numarul de operatori este insuficient (minim 3)."<<endl;
        return false;
    }
    if(nrAsistenti < 1){
        cout<<"Magazinul nu poate functiona: magazinul trebuie sa aiba cel putin un asistent."<<endl;
        return false;
    }

    int nrDisc = 0, nrDiscVintage = 0, nrArticoleVestimentare = 0;
    for (const auto& produs : produse) {
        if(dynamic_cast<Disc*>(produs) && !dynamic_cast<DiscVintage*>(produs)){
            nrDisc++;
        }
        else if(dynamic_cast<DiscVintage*>(produs)){
            nrDiscVintage++;
        }
        else if(dynamic_cast<ArticolVestimentar*>(produs)){
            nrArticoleVestimentare++;
        }
    }

    if(nrDisc < 2){
        cout<<"Magazinul nu poate functiona: nu sunt suficienti discuri (minim 2)."<<endl;
        return false;
    }
    if(nrDiscVintage < 2){
        cout<<"Magazinul nu poate functiona: nu sunt suficiente discuri vintage (minim 2)."<<endl;
        return false;
    }
    if(nrArticoleVestimentare < 2){
        cout<<"Magazinul nu poate functiona: nu sunt suficiente articole vestimentare (minim 2)."<<endl;
        return false;
    }

    cout<<"Magazinul poate functiona corect."<<endl;
    return true;
}

void Magazin::genereazaRaportAngajatMaxComenzi(const string& numeFisier) const{
    if(angajati.empty()){
        cerr<<"Nu exista angajati in magazin."<<endl;
        return;
    }

    Angajat* topAngajat = nullptr;
    int maxComenzi = 0;

    for(const auto& angajat : angajati){
        auto* op = dynamic_cast<Operator*>(angajat);
        if(op){
            int comenziProcesate = op->getNumarComenziProcesate();
            if(comenziProcesate > maxComenzi){
                maxComenzi = comenziProcesate;
                topAngajat = angajat;
            }
        }
    }

    if(topAngajat){
        ofstream fisier(numeFisier);
        if(!fisier.is_open()){
            cerr<<"Eroare la deschiderea fisierului "<<numeFisier<<endl;
            return;
        }

        fisier<<"ID,Nume,Prenume,Comenzi Procesate"<<endl;
        fisier<<topAngajat->getId()<<","<<topAngajat->getNume()<<","<<topAngajat->getPrenume()<<","<<maxComenzi<<endl;
        fisier.close();
    }
}

void Magazin::genereazaRaportTop3AngajatiValoare(const string& numeFisier) const{
    if(angajati.empty()){
        cerr<<"Nu exista angajati in magazin."<<endl;
        return;
    }

    vector<pair<Angajat*, double>> angajatiValoare;

    for(const auto& angajat : angajati){
        auto* op = dynamic_cast<Operator*>(angajat);
        if(op){
            double valoareTotala = op->getValoareTotalaComenziProcesate();
            angajatiValoare.emplace_back(angajat, valoareTotala);
        }
    }

    sort(angajatiValoare.begin(), angajatiValoare.end(), [](const auto& a, const auto& b){ return a.second > b.second;});

    ofstream fisier(numeFisier);
    if(!fisier.is_open()){
        cerr<<"Eroare la deschiderea fisierului "<<numeFisier<<endl;
        return;
    }

    fisier<<"ID,Nume,Prenume,Valoare Comenzi"<<endl;
    for(int i = 0; i < 3 && i < angajatiValoare.size(); i++){
        fisier<<angajatiValoare[i].first->getId()<<","<<angajatiValoare[i].first->getNume()<< ","<<angajatiValoare[i].first->getPrenume()<<","<<angajatiValoare[i].second<<endl;
    }

    fisier.close();
}

void Magazin::genereazaRaportTop3AngajatiSalariu(const string& numeFisier) const{
    if(angajati.empty()){
        cerr<<"Nu exista angajati in magazin."<<endl;
        return;
    }

    vector<Angajat*> angajatiSortati = angajati;

    sort(angajatiSortati.begin(), angajatiSortati.end(), [](const Angajat* a, const Angajat* b){
        if (a->calculSalariu() == b->calculSalariu()) {
            return a->getNume() < b->getNume();
        }
        return a->calculSalariu() > b->calculSalariu();
    });

    ofstream fisier(numeFisier);
    if(!fisier.is_open()){
        cerr<<"Eroare la deschiderea fisierului "<<numeFisier<<endl;
        return;
    }

    fisier<<"ID,Nume,Prenume,Salariu Lunar"<<endl;
    for(int i = 0; i < 3 && i < angajatiSortati.size(); i++){
        fisier<<angajatiSortati[i]->getId()<<","<<angajatiSortati[i]->getNume()<<","<<angajatiSortati[i]->getPrenume()<<","<<angajatiSortati[i]->calculSalariu()<<endl;
    }

    fisier.close();
}


Magazin::~Magazin(){
    for(int i = 0; i < angajati.size(); i++){
        delete angajati[i];
    }
    for(int i = 0; i < produse.size(); i++){
        delete produse[i];
    }
    for(int i = 0; i < comenzi.size(); i++){
        delete comenzi[i];
    }
}
