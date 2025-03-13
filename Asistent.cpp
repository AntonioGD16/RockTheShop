#include "Asistent.h"

Asistent::Asistent(int i, string n, string p, string c, tm data): Angajat(i, n, p, c, data){
}

double Asistent::calculSalariu() const{
    time_t acum = time(nullptr);
    tm* localNow = localtime(&acum);
    int aniVechime;
    
    if(localNow->tm_mday >= dataAngajare.tm_mday && localNow->tm_mon >= dataAngajare.tm_mon){
        aniVechime = localNow->tm_year - dataAngajare.tm_year;
    }
    else
        aniVechime = localNow->tm_year - 1 - dataAngajare.tm_year;
    if(localNow->tm_mday == dataAngajare.tm_mday && localNow->tm_mon == dataAngajare.tm_mon){
        return (((salariuBaza + aniVechime * 100) + 100) * 0.75);
    }
    else
        return ((salariuBaza + aniVechime * 100) * 0.75);
}