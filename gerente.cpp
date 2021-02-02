#include "gerente.h"
#include "ui_gerente.h"
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>

Gerente::Gerente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gerente)
{
    ui->setupUi(this);
    dbconexion.setDatabaseName("sabware_bd");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
    dbconexion.open();
}

Gerente::~Gerente()
{
    delete ui;
}

void Gerente::reloj(){
    QTime hora = QTime::currentTime();
    QString horaTexto = hora.toString("hh:mm");
    ui->relojD->setText(horaTexto);
}

void Gerente::on_btnSalir_clicked()
{
    this->close();
}

void Gerente::on_pushButton_clicked()
{
    int idu = ui->lineEdit_3->text().toInt();
    QSqlQuery mostrar;
    mostrar.exec("SELECT `contrasenia`,`nombre`,`a_materno`,`a_paterno`,`direccion`,`telefono` FROM `usuario` WHERE `idUsuario`='"+QString::number(idu)+"'");
    mostrar.next();
    QString contrasena = mostrar.value("contrasenia").toString();
    QString nombre = mostrar.value("nombre").toString();
    QString amaterno = mostrar.value("a_materno").toString();
    QString apaterno = mostrar.value("a_paterno").toString();
    QString direccion = mostrar.value("direccion").toString();
    QString telefono = mostrar.value("telefono").toString();

    ui->lineEdit->setText(nombre+" "+apaterno+" "+amaterno);
    ui->lineEdit_2->setText(direccion);
    ui->lineEdit_4->setText(telefono);
    ui->lineEdit_5->setText(contrasena);
}

void Gerente::on_pushButton_3_clicked()
{
    QString direccion1, telefono1, contrasena1;

    int idu = ui->lineEdit_3->text().toInt();
    direccion1 = ui->lineEdit_2->text();
    telefono1 = ui->lineEdit_4->text();
    contrasena1 = ui->lineEdit_5->text();

    QSqlQuery modificar;
    modificar.prepare("UPDATE `usuario` SET `contrasenia`='"+contrasena1+"',`direccion`='"+direccion1+"',`telefono`='"+telefono1+"' WHERE idUsuario='"+QString::number(idu)+"'");
    modificar.next();
    if(modificar.exec()){
        QMessageBox mssg;
        mssg.setText("Datos del usuario modificados.");
        mssg.setIcon(QMessageBox::Information);
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
    else {
        QMessageBox mssg;
        mssg.setText("No se pudieron modificar los datos.");
        mssg.setIcon(QMessageBox::Information);
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
}
