#ifndef PLATILLOS_H
#define PLATILLOS_H
#include <QDebug>
#include <QString>

class platillos
{
    QString nombreP;
    QString subtotal;
public:
    platillos();
    void setNombre(QString nom);
    void setTotal(QString tp);
    QString getNombre(){return nombreP;}
    QString getTotal(){return subtotal;}

};

#endif // PLATILLOS_H
