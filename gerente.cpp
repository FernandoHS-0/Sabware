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
    QSqlQuery Eliminar;
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
