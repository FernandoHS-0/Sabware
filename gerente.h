#ifndef GERENTE_H
#define GERENTE_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Gerente;
}

class Gerente : public QWidget
{
    Q_OBJECT

public:
    explicit Gerente(QWidget *parent = nullptr);
    ~Gerente();
public slots:
    void reloj();
    void cargarZona();
    void actualizarZona();
    void on_btnGuardar_clicked();



private slots:
    void on_btnSalir_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Guardar_clicked();

    void on_pushButton_3_clicked();

    void on_btnZona_clicked();

    void on_modificarZona_clicked();


    void on_eliminarZona_clicked();

    void on_agregarZona_clicked();

    void on_btnGuardar_2_clicked();

    void on_btnGestionUsr_2_clicked();

    void on_btnGestionUsr_clicked();

private:
    Ui::Gerente *ui;
    QTimer *timer;
    QSqlDatabase dconexion;
    int noZona;


};

#endif // GERENTE_H
