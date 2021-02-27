#include "platillos.h"

platillos::platillos()
{
    nombreP="";
    subtotal="";
}

void platillos::setNombre(QString nom){
    nombreP=nom;
}
void platillos::setTotal(QString tp){
    subtotal = tp;
}
