#include "SharedTable.h"

SharedTable::SharedTable(bool protection)
    : protectionActive(protection) {
    for (int i = 0; i < 100; i++) {
        tableau[i] = 0;
    }
}

void SharedTable::fill(unsigned char valeur) {
    if (protectionActive) {
        mutex.take();
    }

    unsigned char somme = 0;

    for (int i = 0; i < 99; i++) {
        tableau[i] = valeur;
        somme += valeur;
    }

    tableau[99] = somme;

    if (protectionActive) {
        mutex.release();
    }
}

bool SharedTable::verify() {
    if (protectionActive) {
        mutex.take();
    }

    unsigned char somme = 0;

    for (int i = 0; i < 99; i++) {
        somme += tableau[i];
    }

    bool valide = (somme == tableau[99]);

    if (protectionActive) {
        mutex.release();
    }

    return valide;
}

void SharedTable::setProtection(bool protection) {
    protectionActive = protection;
}