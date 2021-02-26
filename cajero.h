#ifndef CAJERO_H
#define CAJERO_H

#include <QWidget>
#include <QTimer>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include "platillos.h"

namespace Ui {
class Cajero;
}

class Cajero : public QWidget
{
    Q_OBJECT

public:
    explicit Cajero(QWidget *parent = nullptr);
    ~Cajero();
public slots:
    void reloj();

private slots:
    void verOrdenes();
    void cobrarOrdenes();
    void on_btnSalir_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Cajero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
    int noMesa;
    QList<platillos> noPlatos;
};

#endif // CAJERO_H
