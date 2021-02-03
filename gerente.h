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

private slots:
    void on_btnSalir_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Gerente *ui;
    QTimer *timer;
    QSqlDatabase dbconexion;
};

#endif // GERENTE_H
