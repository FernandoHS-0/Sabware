#ifndef ENCARGADO_H
#define ENCARGADO_H

#include <QWidget>
#include <QTimer>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Encargado;
}

class Encargado : public QWidget
{
    Q_OBJECT

public:
    explicit Encargado(QWidget *parent = nullptr);
    ~Encargado();
public slots:
    void reloj();

private slots:
    void on_btnSalir_clicked();

    void on_btnGuardar_clicked();

private:
    Ui::Encargado *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
};

#endif // ENCARGADO_H
