#pragma once
#include "Mutex.h"

class SharedTable {
private:
    unsigned char tableau[100];
    Mutex mutex;
    bool protectionActive;

public:
    SharedTable(bool protection);

    void fill(unsigned char valeur);
    bool verify();
    void setProtection(bool protection);
};