#include "encargado.h"
#include "ui_encargado.h"
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

Encargado::Encargado(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Encargado)
{
    ui->setupUi(this);
    //dbconexion = QSqlDatabase::addDatabase("QODBC");
    dbconexion.setDatabaseName("sabware_bd");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
}

Encargado::~Encargado()
{
    delete ui;
}

void Encargado::reloj(){
    QTime hora = QTime::currentTime();
    QString horaTexto = hora.toString("hh:mm");
    ui->relojD->setText(horaTexto);
}

void Encargado::on_btnSalir_clicked()
{
    this->close();
}

void Encargado::on_btnGuardar_clicked()
{
    /*dbconexion.open();
    QSqlQuery zona;
    zona.prepare("UPDATE mesero SET idZona = :idZ WHERE idMesero = 1");
    zona.bindValue(":idZ", ui->zonaF1->currentIndex());
    if(zona.exec()){*/
        QMessageBox mssg;
        mssg.setText("Zonas actualizadas");
        mssg.setIcon(QMessageBox::Information);
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    /*}else {
        qDebug() << "Error en el query";
    }
    dbconexion.close();*/
}
