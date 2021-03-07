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
    ui->usuario->setVisible(false);
    ui->totales->setVisible(false);
    ui->caja1->setVisible(false);
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

void Encargado::on_btnGestionUsr_clicked()
{
    //ui->paginas->setCurrentIndex(1);
}

void Encargado::on_btnAsigZ_clicked()
{
    ui->paginas->setCurrentIndex(0);
}

void Encargado::on_pushButton_clicked()
{
    int cajero = ui->comboBox->currentIndex()+1;
    qDebug()<<cajero;
    ui->usuario->setVisible(true);
    ui->caja1->setVisible(true);
    ui->totales->setVisible(true);
    QSqlQuery datos;
    QSqlQuery tabla;
    QSqlQuery totales;

    datos.prepare("SELECT `idUsuario`,`nombre`,`a_materno`,`a_paterno` FROM `usuario` WHERE `idUsuario`='"+QString::number(cajero)+"'");
    datos.exec();
    while (datos.next()) {
        QString nombre, apellido1, apellido2, usuario;
        nombre = datos.value(1).toString();
        apellido1 = datos.value(3).toString();
        apellido2 = datos.value(2).toString();
        usuario = datos.value(0).toString();

        ui->nombre->setText(nombre+" "+apellido1+" "+apellido2);
        ui->zona->setText(usuario);
    }

    ui->caja1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->caja1->setRowCount(0);
    QStringList titulos;
    titulos<<"ID DE LA ORDEN"<<"PAGO TOTAL";
    ui->caja1->setColumnWidth(1,80);
    ui->caja1->setColumnWidth(2,100);
    ui->caja1->setColumnCount(2);
    ui->caja1->setHorizontalHeaderLabels(titulos);
    if(tabla.prepare("SELECT `idOrden`, `total` FROM `orden` WHERE `estadoFiscal`=1 AND `idCajero`='"+QString::number(cajero)+"'")){
        tabla.exec();
        while (tabla.next()) {
            ui->caja1->insertRow(ui->caja1->rowCount());
            int fila2 = ui->caja1->rowCount()-1;
            ui->caja1->setItem(fila2,0,new QTableWidgetItem(tabla.value(0).toString()));
            ui->caja1->setItem(fila2,1,new QTableWidgetItem(tabla.value(1).toString()));
        }
    }

    totales.prepare("SELECT COUNT(`idOrden`), SUM(`total`) FROM `orden` WHERE `estadoFiscal`=1 AND `idCajero`='"+QString::number(cajero)+"'");
    totales.exec();
    while (totales.next()) {
        QString ordenes1, ingresos1;
        ordenes1 = totales.value(0).toString();
        ingresos1 = totales.value(1).toString();

        ui->ordenes->setText(ordenes1);
        ui->ingresos->setText(ingresos1);
    }
}
//SE VAN A HACER CAMBIOS EN LA BASE DE DATOS PARA PODER AL FINAL GENERAR BIEN EL CORTE Y UN REPORTE DEL MISMO
void Encargado::on_pushButton_2_clicked()
{
    QMessageBox guardar;
    guardar.setText("Se han guardado los datos dados.");
    guardar.setIcon(QMessageBox::Information);
    guardar.addButton(tr("Aceptar"),QMessageBox::YesRole);
    guardar.exec();
}
