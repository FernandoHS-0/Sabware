#ifndef INICIO_H
#define INICIO_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include "encargado.h"
#include "gerente.h"
//#include "cajero.h"
//"include "mesero.h"

namespace Ui {
class Inicio;
}

class Inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Inicio(QWidget *parent = nullptr);
    ~Inicio();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Inicio *ui;
    QSqlDatabase conexion;
    Encargado *enc;
    Gerente *gere;
    //Cajero *caj;
    //Mesero *mes;
};

#endif // INICIO_H
