#ifndef MESERO_H
#define MESERO_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Mesero;
}

class Mesero : public QWidget
{
    Q_OBJECT

public:
    explicit Mesero(QWidget *parent = nullptr);
    ~Mesero();
public slots:
    void reloj();

private slots:
    void on_btnSalir_clicked();

    void on_btnMesa_clicked();

private:
    Ui::Mesero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
};

#endif // MESERO_H
