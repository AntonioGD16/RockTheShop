#include "Manager.h"

Manager::Manager(int i, string n, string p, string c, tm data): Angajat(i, n, p, c, data) {
}

double Manager::calculSalariu() const{
    time_t acum = time(nullptr);
    tm* localNow = localtime(&acum);
    int aniVechime;
    
    if(localNow->tm_mday >= dataAngajare.tm_mday && localNow->tm_mon >= dataAngajare.tm_mon){
        aniVechime = localNow->tm_year - dataAngajare.tm_year;
    }
    else
        aniVechime = localNow->tm_year - 1 - dataAngajare.tm_year;
    return (salariuBaza + aniVechime * 100) * 1.25;
}
