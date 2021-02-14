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
private:
    Ui::Cajero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
    int noMesa;
};

#endif // CAJERO_H
