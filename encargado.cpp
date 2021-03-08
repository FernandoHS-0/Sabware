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
    llenarZonas();
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

void Encargado::llenarZonas(){

    ui->cmbZona->addItem("");
    ui->cmbMeseros->addItem("");

    QSqlQuery meseros(dbconexion);
    meseros.exec("SELECT idMesero FROM mesero;");
    while(meseros.next()){
        ui->cmbMeseros->addItem(meseros.value(0).toString());
    }

    QSqlQuery zonas(dbconexion);
    zonas.exec("SELECT idZona FROM zona;");
    while(zonas.next()){
        ui->cmbZona->addItem(zonas.value(0).toString());
    }
}

void Encargado::on_btnSalir_clicked()
{
    this->close();
}

void Encargado::on_btnGuardar_clicked()
{
    QSqlQuery actZona(dbconexion);
    actZona.prepare("UPDATE mesero SET idZona = " + ui->cmbZona->currentText() + " WHERE idMesero = " + ui->cmbMeseros->currentText() + ";");

    if(actZona.exec()){
        QMessageBox succ;
        succ.setText("La zona ha sido actualizado correctamente");
        succ.setIcon(QMessageBox::Information);
        succ.setWindowTitle("Zona asignada");
        succ.addButton("Aceptar", QMessageBox::AcceptRole);
        succ.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        succ.exec();
    }
}

void Encargado::on_btnGestionUsr_clicked()
{
    ui->paginas->setCurrentIndex(1);
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

void Encargado::on_cmbMeseros_currentTextChanged(const QString &arg1)
{
    QSqlQuery nombreM(dbconexion);
    nombreM.exec("SELECT u.nombre, u.a_materno, u.a_paterno FROM usuario AS u INNER JOIN mesero AS m on u.idUsuario = m.idMesero WHERE m.idMesero = " + arg1 + ";");
    nombreM.next();
    ui->nombreM->setText(nombreM.value(0).toString() + " " + nombreM.value(1).toString() + " " + nombreM.value(2).toString());
}

void Encargado::on_cmbZona_currentTextChanged(const QString &arg1)
{
    QSqlQuery nombreZ(dbconexion);
    nombreZ.exec("SELECT nombre FROM zona WHERE idZona = " + arg1 + ";");
    nombreZ.next();
    ui->nombreZ->setText(nombreZ.value(0).toString());
}
