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
    dconexion = QSqlDatabase::addDatabase("QODBC","sabware_bd");
    dconexion.setHostName("root");
    dconexion.setDatabaseName("sabware_bd");
    if(dconexion.open()){
        qDebug() << "Conexion establecida";
    }else{
        qDebug() << "Error en la conexion";
    }
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
    QSqlQuery mostrar(dconexion);
    mostrar.exec("SELECT `contrasenia`,`nombre`,`a_materno`,`a_paterno`,`direccion`,`telefono` FROM `usuario` WHERE `idUsuario`='"+QString::number(idu)+"'");
    mostrar.next();
    QString contrasena = mostrar.value(0).toString();
    QString nombre = mostrar.value(1).toString();
    QString amaterno = mostrar.value(2).toString();
    QString apaterno = mostrar.value(3).toString();
    QString direccion = mostrar.value(4).toString();
    QString telefono = mostrar.value(5).toString();

    ui->lineEdit->setText(nombre+" "+apaterno+" "+amaterno);
    ui->lineEdit_2->setText(direccion);
    ui->lineEdit_4->setText(telefono);
    ui->lineEdit_5->setText(contrasena);
}


void Gerente::on_pushButton_2_clicked()
{
    QMessageBox mssg1;
    mssg1.setText("¿Esta seguro de eliminar este usuario?");
    mssg1.setIcon(QMessageBox::Warning);
    mssg1.setWindowTitle("Advertencia");
    mssg1.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));;
    QAbstractButton * pButtonYes = mssg1.addButton(tr("Si"), QMessageBox::YesRole);
    QAbstractButton * pButtonNo = mssg1.addButton(tr("No"), QMessageBox::NoRole);
    int idu = ui->lineEdit_3->text().toInt();
    QSqlQuery Eliminar(dconexion);
    Eliminar.prepare("DELETE FROM Usuario WHERE idUsuario = :idU;");
    Eliminar.bindValue(":idU", idu);
    mssg1.exec();
    if(mssg1.clickedButton() == pButtonYes){
        Eliminar.exec();
        QMessageBox mssg2;
        mssg2.setText("El usuario ha sido eliminado");
        mssg2.setIcon(QMessageBox::Warning);
        mssg2.setWindowTitle("Usuario eliminado");
        mssg2.addButton("Aceptar", QMessageBox::AcceptRole);
        mssg2.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg2.exec();

    }
}

void Gerente::on_Guardar_clicked()
{
    QString n = ui->Nombre->text();
    QString ap = ui->ApellidoP->text();
    QString am = ui->ApellidoM->text();
    QString direccion = ui->Direccion->text();
    QString telefono = ui->Telefono->text();
    QString contrasenia = "password";
    QString usuario = "206";
    QMessageBox msg;

    msg.setText("¿Los datos del usuario son correctos?");
    QAbstractButton * pButtonYes = msg.addButton(tr("Si"),QMessageBox::YesRole);
    msg.addButton(tr("No"),QMessageBox::NoRole);
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
    msg1.setIcon(QMessageBox::Information);
    msg1.setText("El usuario ha sido registrado");
    msg1.setWindowTitle("Usuario registrado");
    msg1.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
    msg1.addButton(tr("Aceptar"),QMessageBox::YesRole);
    msg1.exec();
   }
}

void Gerente::on_pushButton_3_clicked()
{
    QString direccion1, telefono1, contrasena1;

    int idu = ui->lineEdit_3->text().toInt();
    direccion1 = ui->lineEdit_2->text();
    telefono1 = ui->lineEdit_4->text();
    contrasena1 = ui->lineEdit_5->text();

    QSqlQuery modificar(dconexion);
    modificar.prepare("UPDATE `usuario` SET `contrasenia`='"+contrasena1+"',`direccion`='"+direccion1+"',`telefono`='"+telefono1+"' WHERE idUsuario='"+QString::number(idu)+"'");
    modificar.next();
    if(modificar.exec()){
        QMessageBox mssg;
        mssg.setText("Datos del usuario modificados.");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Advertencia");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
    else {
        QMessageBox mssg;
        mssg.setText("No se pudieron modificar los datos.");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Advertencia");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
}
