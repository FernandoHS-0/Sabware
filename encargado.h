#ifndef ENCARGADO_H
#define ENCARGADO_H

#include <QWidget>
#include <QTimer>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <string>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>

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
    void llenarTabla();
    void llenarCombos();

private slots:
    void on_btnSalir_clicked();

    void on_btnGuardar_clicked();

    void on_btnGestionUsr_clicked();

    void on_btnAsigZ_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btnInven_clicked();

    void on_Actubtn_clicked();

    void on_GuaPrbtn_clicked();

    void on_agregarPbtn_clicked();

    void on_eliminarPbtn_clicked();

    void on_cmbMeseros_currentTextChanged(const QString &arg1);

    void on_cmbZona_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Encargado *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
    int id;
    int fila;
    int cont;
};

#endif // ENCARGADO_H
