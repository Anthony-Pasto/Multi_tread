#pragma once
#include "Mutex.h"


class SharedValue
{
private:
    Mutex mutex;
    float valeur;
public:
    SharedValue();
    void write(float nouvelleValeur);
       
    float read() ;


};