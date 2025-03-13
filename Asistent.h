#ifndef ASISTENT_H
#define ASISTENT_H

#include "Angajat.h"

class Asistent: public Angajat{
public:
    Asistent() = default;
    Asistent(int id, string, string, string, tm);

    double calculSalariu() const override;
};

#endif