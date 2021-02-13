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

private:
    Ui::Cajero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
};

#endif // CAJERO_H
