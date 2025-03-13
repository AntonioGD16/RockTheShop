#ifndef MANAGER_H
#define MANAGER_H

#include "Angajat.h"

class Manager: public Angajat{
public:
    Manager() = default;
    Manager(int id, string, string, string, tm);
    double calculSalariu() const override;
};

#endif