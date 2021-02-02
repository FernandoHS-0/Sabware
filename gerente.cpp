#include "gerente.h"
#include "ui_gerente.h"
#include <QDateTime>
#include <QTimer>
#include "QMessageBox"
#include <QDialog>
#include <QDebug>



Gerente::Gerente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gerente)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);

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

}


void Gerente::on_pushButton_2_clicked()
{
    QMessageBox msg;


    msg.setText("¿SEGURO DE AGREGAR A COMO NUEVO USUARIO?");
    qDebug()<<"AQUI ESTA";
}

void Gerente::on_Guardar_clicked()
{
    qDebug()<<"AQUI ESTA1";
    QString n = ui->Nombre->text();
    QString ap = ui->ApellidoP->text();
    QString am = ui->ApellidoM->text();
    QString direccion = ui->Direccion->text();
    QString telefono = ui->Telefono->text();
    QString contrasenia = "password";
    QString usuario = "206";
    QMessageBox msg;


    msg.setText("¿SEGURO DE AGREGAR A '"+n+" "+ap+" "+am+"' COMO NUEVO USUARIO?");
    qDebug()<<"AQUI ESTA";
    QAbstractButton * pButtonYes = msg.addButton(tr("SI"),QMessageBox::YesRole);
    msg.addButton(tr("NO"),QMessageBox::NoRole);
    msg.exec();
    if(msg.clickedButton()==pButtonYes){
        QString tipousuario = ui->comboBox->currentText();

QSqlQuery query1(dconexion);
QSqlQuery query2(dconexion);

if(tipousuario == "Mesero"){

    query1.prepare("call AgregarUsuarioMesero('"+usuario+"','"+n+"','"+contrasenia+"','"+ap+"','"+am+"','"+direccion+"','"+telefono+"')");
    query1.exec();
}
if(tipousuario == "Cajero"){
    query2.prepare("call AgregarUsuarioCajero('"+usuario+"','"+n+"','"+contrasenia+"','"+ap+"','"+am+"','"+direccion+"','"+telefono+"')");
    query2.exec();
}
if(tipousuario == "Encargado"){
    query2.prepare("call AgregarUsuarioEncargado('"+usuario+"','"+n+"','"+contrasenia+"','"+ap+"','"+am+"','"+direccion+"','"+telefono+"')");
    query2.exec();
}
if(tipousuario == "Gerente"){
    query2.prepare("call AgregarUsuarioGerente('"+usuario+"','"+n+"','"+contrasenia+"','"+ap+"','"+am+"','"+direccion+"','"+telefono+"')");
    query2.exec();
}
    QMessageBox msg1;
    msg.setWindowTitle("Exito");
       msg1.setIcon(QMessageBox::Information);
       msg1.setText("El usuario ha sido registrado");
       msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
       msg1.exec();
       close();
         }
}
