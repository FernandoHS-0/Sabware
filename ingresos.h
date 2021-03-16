#ifndef INGRESOS_H
#define INGRESOS_H
#include <QString>

class ingresos
{
public:
    int ordenesC;
    QString cajero;
    int ingreso;
public:
    ingresos();
    void setOrden(int oc){ordenesC=oc;}
    void setCajero(QString c){cajero=c;}
    void setIngreso(int in){ingreso=in;}
    int getOrden(){return ordenesC;}
    QString getCajero(){return cajero;}
    int getIngreso(){return ingreso;}
};

#endif // INGRESOS_H
