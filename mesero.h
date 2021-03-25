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
    void entradas();
    void pFuerte();
    void postres();
    void bebidas();

private slots:
    void on_btnSalir_clicked();
    void on_btnMes_clicked();

    void on_btnMesa_clicked();

    void on_btnOrdenar_clicked();

    void agregarElementoMenu(int cantidad);

    void on_btnCobrar_clicked();

    void on_cambiarMesa_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::Mesero *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
    int mesAct;
};

#endif // MESERO_H
