#include "cajero.h"
#include "ui_cajero.h"
#include <QDateTime>
#include "QMessageBox"
#include <QDebug>

Cajero::Cajero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cajero)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);
    dbconexion.setDatabaseName("sabware_bd");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
    dbconexion = QSqlDatabase::addDatabase("QODBC","sabware_bd");
    dbconexion.setHostName("root");
    dbconexion.setDatabaseName("sabware_bd");
    if(dbconexion.open()){
        qDebug() << "Conexion establecida";
    }else{
        qDebug() << "Error en la conexion";
    }

    QSqlQuery ordenes(dbconexion);
    ordenes.prepare("SELECT COUNT(`idOrden`) FROM `orden` WHERE `idCajero`=4");
    ordenes.exec();
    ordenes.next();
    int col=0, fila=0;
    int filasO = ordenes.value(0).toInt();
    for (int i=0; i<filasO; i++) {
        QString numO = QString::number(i+1);
        QPushButton * orden = new QPushButton;
        orden->setObjectName(numO);
        orden->setText("Mesa "+numO);
        orden->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D96704; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->gridLayout_2->addWidget(orden,fila,col,Qt::AlignCenter);
        connect(orden, SIGNAL(clicked()), SLOT(verOrdenes()));
        col++;
        if(i==2){
            fila++;
            col = 0;
        }
    }
}

Cajero::~Cajero()
{
    delete ui;
}

void Cajero::verOrdenes(){
    qDebug() << "entro";
    ui->groupBox->setVisible(true);
    ui->groupBox->setStyleSheet("QGroupBox{border: 3px solid #D92B04; font: 13pt 'HelvLight';}");
    QPushButton *mesaO = dynamic_cast<QPushButton*>(sender());
    QSqlQuery mesa(dbconexion);
    QSqlQuery detalleO(dbconexion);
    QSqlQuery total(dbconexion);
    if(mesaO){
        ui->label_3->setText(mesaO->text());
        noMesa = mesaO->objectName().toInt();
        detalleO.prepare("SELECT elemento_menu.idPlatillo,elemento_menu.nombre_platillo,orden.idMesa,orden.idOrden,detalleorden.cantidad FROM `detalleorden` INNER JOIN orden ON detalleorden.idOrden=orden.idOrden INNER JOIN elemento_menu ON detalleorden.idPlatillo=elemento_menu.idPlatillo WHERE orden.idMesa='"+QString::number(noMesa)+"'");
        detalleO.exec();
        while (detalleO.next()) {
            QString nombre = detalleO.value(1).toString();
            QString porcion = detalleO.value(4).toString();
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            QTableWidgetItem *plato = new QTableWidgetItem(nombre);
            QTableWidgetItem *por = new QTableWidgetItem(porcion);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,plato);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,por);
            ui->tableWidget->setColumnCount(2);
            ui->tableWidget->setColumnWidth(0,240);
            ui->tableWidget->setColumnWidth(1,65);
        }
        total.exec("SELECT orden.idMesa,SUM(`subtotal`) FROM `detalleorden` INNER JOIN orden ON orden.idOrden=detalleorden.idOrden WHERE orden.idMesa='"+QString::number(noMesa)+"'");
        total.next();
        QString precio = total.value(1).toString();
        ui->label_5->setText("$"+precio);
    }
}

void Cajero::reloj(){
    QTime hora = QTime::currentTime();
    QString horaTexto = hora.toString("hh:mm");
    ui->relojD->setText(horaTexto);
}

void Cajero::on_btnSalir_clicked()
{
    this->close();
}
