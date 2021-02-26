#include "cajero.h"
#include "ui_cajero.h"
#include <QDateTime>
#include "QMessageBox"
#include <QDebug>
#include <QSqlError>

Cajero::Cajero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cajero)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);
    ui->groupBox_2->setVisible(false);
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
    ordenes.prepare("SELECT COUNT(`idOrden`) FROM `orden` WHERE `idCajero` is null and estadoFisico = 0");
    ordenes.exec();
    ordenes.next();
    int col=0, fila=0;
    int filasO = ordenes.value(0).toInt();
    for (int i=0; i<filasO; i++) {
        QString numO = QString::number(i+1);
        QPushButton * orden = new QPushButton;
        orden->setObjectName(numO);
        orden->setText("Mesa "+numO);
        orden->setStyleSheet("QPushButton{border-radius: 20px; background-color: #f8e44b; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->gridLayout_2->addWidget(orden,fila,col,Qt::AlignCenter);
        connect(orden, SIGNAL(clicked()), SLOT(verOrdenes()));
        col++;
        if(i==2){
            fila++;
            col = 0;
        }
    }

    QSqlQuery ordenesC(dbconexion);
    ordenes.prepare("SELECT COUNT(`idOrden`) FROM `orden` WHERE `idCajero`=4 and estadoFiscal = 0");
    ordenes.exec();
    ordenes.next();
    int col1=0, fila1=0;
    int filasO1 = ordenes.value(0).toInt();
    for (int i=0; i<filasO1; i++) {
        QString numO1 = QString::number(i+1);
        QPushButton * orden1 = new QPushButton;
        orden1->setObjectName(numO1);
        orden1->setText("Mesa "+numO1);
        orden1->setStyleSheet("QPushButton{border-radius: 20px; background-color: #f8e44b; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->gridLayout_4->addWidget(orden1,fila1,col1,Qt::AlignCenter);
        connect(orden1, SIGNAL(clicked()), SLOT(cobrarOrdenes()));
        col1++;
        if(i==2){
            fila1++;
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
    ui->tableWidget->clearContents();
    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());
    if(mesaO){
        ui->label_3->setText(mesaO->text());
        noMesa = mesaO->objectName().toInt();
        detalleO.prepare("SELECT elemento_menu.idPlatillo,elemento_menu.nombre_platillo,orden.idMesa,orden.idOrden,detalleorden.cantidad FROM `detalleorden` INNER JOIN orden ON detalleorden.idOrden=orden.idOrden INNER JOIN elemento_menu ON detalleorden.idPlatillo=elemento_menu.idPlatillo WHERE orden.idMesa='"+QString::number(noMesa)+"'and orden.idCajero is null");
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

void Cajero::on_pushButton_3_clicked()
{

    QMessageBox conf;
    conf.setText("Confirmar orden");
    QAbstractButton * btnAcp = conf.addButton("Aceptar", QMessageBox::AcceptRole);
    conf.addButton("Cancelar", QMessageBox::AcceptRole);
    conf.setIcon(QMessageBox::Information);
    conf.setWindowTitle("Confirmar orden");
    conf.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
    conf.exec();
    if(conf.clickedButton() == btnAcp){
        QSqlQuery marcarLista(dbconexion),obtenenerOrden(dbconexion);
        obtenenerOrden.prepare("select idOrden from orden where idMesa=:mes and idCajero is null and estadoFisico = 0;");
        obtenenerOrden.bindValue(":mes",noMesa);
        obtenenerOrden.exec();
        obtenenerOrden.next();
        QString orden;
        orden = obtenenerOrden.value(0).toString();
        qDebug()<<"la orden es"+orden+"";
        marcarLista.prepare("update orden set estadoFisico = 1 where idOrden ="+orden+";");
        marcarLista.exec();
        //ui->gridLayoutWidget_2->setVisible(false);
        ui->tableWidget->clearContents();
        ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());


}
}

void Cajero::cobrarOrdenes(){
    qDebug() << "entro";
    ui->groupBox_2->setVisible(true);
    ui->groupBox_2->setStyleSheet("QGroupBox{border: 3px solid #D92B04; font: 13pt 'HelvLight';}");
    QPushButton *mesaO = dynamic_cast<QPushButton*>(sender());
    noMesa = mesaO->objectName().toInt();
    qDebug()<<noMesa;
    QSqlQuery mesa1(dbconexion);
    QSqlQuery detalleO1(dbconexion);
    QSqlQuery total1(dbconexion);

    platillos numP;
    QSqlQuery *qplato = new QSqlQuery();
    if(qplato->exec("SELECT elemento_menu.nombre_platillo, detalleorden.subtotal FROM `detalleorden` INNER JOIN elemento_menu ON elemento_menu.idPlatillo=detalleorden.idPlatillo WHERE detalleorden.idOrden="+QString::number(noMesa)+";")){
        while (qplato->next()) {
            numP.setNombre(qplato->value(0).toString());
            numP.setTotal(qplato->value(1).toString());
            noPlatos << numP;
        }
    }
    else{
        qDebug() << " Error de llenado de reservaciones pagadas :( ";
        qDebug() << qplato->lastError();
    }
    delete qplato;
    int numplatos1 = noPlatos.size();
    QDate fecha = QDate::currentDate();
    QString FechaActual = fecha.toString("yyyy-MM-dd");
    ui->label_11->setText(FechaActual);
    if(mesaO){
        detalleO1.prepare("SELECT `idMesa` FROM `orden` WHERE `idOrden`='"+QString::number(noMesa)+"'");
        detalleO1.exec();
        while (detalleO1.next()) {
            QString mesa1 = detalleO1.value(0).toString();
            ui->label_13->setText(mesa1);

            QString texto1 = "";
            for (int p=0; p<numplatos1; p++) {
                texto1 = texto1+"      "+noPlatos[p].getNombre()+"    $"+noPlatos[p].getTotal()+"\n";
            }
            ui->textBrowser->setText(texto1);
        }
        total1.exec("SELECT SUM(`subtotal`) FROM `detalleorden` WHERE `idOrden`='"+QString::number(noMesa)+"'");
        total1.next();
        QString totalp = total1.value(0).toString();
        ui->label_16->setText(totalp);
    }
}

void Cajero::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Cajero::on_radioButton_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void Cajero::on_radioButton_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void Cajero::on_pushButton_2_clicked()
{
    QPushButton *mesaO = dynamic_cast<QPushButton*>(sender());
    noMesa = mesaO->objectName().toInt();
    QSqlQuery modificar;
    modificar.prepare("UPDATE `orden` SET `total`=234,`estadoFiscal`=1 WHERE `idOrden`='"+QString::number(noMesa)+"'");
    modificar.next();
    if(modificar.exec()){
        QMessageBox mssg;
        mssg.setText("Se ha efectuado correctamente el pago.");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Pago exitoso");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
    else {
        QMessageBox mssg;
        mssg.setText("No se ha podido completar el pago");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Advertencia");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
}

void Cajero::on_pushButton_6_clicked()
{
    QPushButton *mesaO = dynamic_cast<QPushButton*>(sender());
    noMesa = mesaO->objectName().toInt();
    QSqlQuery modificar;
    modificar.prepare("UPDATE `orden` SET `total`=234,`estadoFiscal`=1 WHERE `idOrden`='"+QString::number(noMesa)+"'");
    modificar.next();
    if(modificar.exec()){
        QMessageBox mssg;
        mssg.setText("Se ha efectuado correctamente el pago.");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Pago exitoso");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
    else {
        QMessageBox mssg;
        mssg.setText("No se ha podido completar el pago");
        mssg.setIcon(QMessageBox::Information);
        mssg.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg.setWindowTitle("Advertencia");
        mssg.addButton(tr("Aceptar"),QMessageBox::YesRole);
        mssg.exec();
    }
}

void Cajero::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
