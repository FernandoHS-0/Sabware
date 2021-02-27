#include "inicio.h"
#include "ui_inicio.h"
#include <QDebug>
#include <QMessageBox>

Inicio::Inicio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Inicio)
{
    ui->setupUi(this);
    conexion = QSqlDatabase::addDatabase("QODBC");
    conexion.setHostName("root");
    conexion.setDatabaseName("sabware_bd");
}

Inicio::~Inicio()
{
    delete ui;
}

void Inicio::on_pushButton_2_clicked()
{
    conexion.open();
    int usuario = ui->txtUsuairo->text().toInt(); QString contra = ui->txtPass->text();
    QSqlQuery log;

    log.prepare("SELECT idUsuario, contrasenia FROM usuario WHERE idUsuario = :idU AND contrasenia = '"+contra+"';");
    log.bindValue(":idU", usuario);
    if(log.exec()){
        log.next();
        QString id = log.value(0).toString();
        QString resultadoGere;
        QString resultadoEncar;
        QString resultadoCajero;
        QString resultadoMesero;
        QMessageBox msg;
        QSqlQuery prueba;
        QString conexion;

        prueba.prepare("SELECT idGerente, IF('"+id+"'=idGerente ,'TRUE','FALSE') AS ESTADO FROM gerente WHERE idGerente='"+id+"'");
        prueba.exec();

        while(prueba.next())
        {
          resultadoGere=prueba.value(1).toString();
        }

        if(resultadoGere=="TRUE")
        {
            gere = new Gerente;
            gere->show();
            conexion=1;
        }
        prueba.prepare("SELECT idEncargado, IF('"+id+"'=idEncargado ,'TRUE','FALSE') AS ESTADO FROM encargado WHERE idEncargado='"+id+"'");
        prueba.exec();
        while(prueba.next())
        {
          resultadoEncar=prueba.value(1).toString();
        }
        qDebug()<<resultadoEncar;

        if(resultadoEncar=="TRUE")
        {

            enc = new Encargado;
            enc->show();
            conexion=1;
        }
        prueba.prepare("SELECT idCajero, IF('"+id+"'=idCajero ,'TRUE','FALSE') AS ESTADO FROM cajero WHERE idCajero='"+id+"'");
        prueba.exec();
        while(prueba.next())
        {
          resultadoCajero=prueba.value(1).toString();
        }
        if(resultadoCajero=="TRUE")
        {
            caj = new Cajero;
            caj->show();
            conexion=1;
        }
        prueba.prepare("SELECT idMesero, IF('"+id+"'=idMesero ,'TRUE','FALSE') AS ESTADO FROM mesero WHERE idMesero='"+id+"'");
        prueba.exec();
        while(prueba.next())
        {
          resultadoMesero=prueba.value(1).toString();
        }
        if(resultadoMesero=="TRUE")
        {
            mes = new Mesero;
            mes->show();
            conexion=1;
        }
        if(conexion!=1)
        {
            msg.setWindowTitle("Falló el inicio de sesión");
            msg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText("Usuario o contraseña invalida");
            msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
            msg.exec();
        }

    }else {
        qDebug() << "Error en el login";
    }
}
