#include "inicio.h"
#include "ui_inicio.h"
#include <QDebug>

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
        if(log.value(0).toInt() == usuario && log.value(1).toString() == contra){
            enc = new Encargado;
            enc->show();
        }
    }else {
        qDebug() << "Error en el login";
    }
    conexion.close();
}
