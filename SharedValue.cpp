#include "SharedValue.h"


    SharedValue::SharedValue()  {

        valeur = 0.0f;
    }


    void SharedValue::write(float nouvelleValeur) {
        mutex.take();
        valeur = nouvelleValeur;
        mutex.release();
    }

    float SharedValue::read() {
        mutex.take();
        float copie = valeur;
        mutex.release();
        return copie;
    }