#ifndef CAJERO_H
#define CAJERO_H

#include <QWidget>
#include <QTimer>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    void on_btnSalir_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Cajero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
    int noMesa;
};

#endif // CAJERO_H
