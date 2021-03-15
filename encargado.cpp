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

void Encargado::on_btnInven_clicked()
{
     ui->paginas->setCurrentIndex(2);
     QSqlQuery *produc=new QSqlQuery;
     ui->invetario_tableWidget->clear();
     ui->invetario_tableWidget->setRowCount(0);
     QStringList titulos;
     titulos<<"IDProducto"<<"Nombre"<<"Descripcion"<<"Cantidad";
     ui->invetario_tableWidget->setColumnCount(4);
     ui->invetario_tableWidget->setHorizontalHeaderLabels(titulos);
     if(produc->prepare("SELECT idProducto,nombre_pr,descripcion_pr,cantidad  FROM inventario"))
     {
         produc->exec();
         int fila;
         while(produc->next()){
             ui->invetario_tableWidget->insertRow(ui->invetario_tableWidget->rowCount());
             fila = ui->invetario_tableWidget->rowCount()-1;
             ui->invetario_tableWidget->setItem(fila,0,new QTableWidgetItem(produc->value(0).toString()));
             ui->invetario_tableWidget->setItem(fila,1,new QTableWidgetItem(produc->value(1).toString()));
             ui->invetario_tableWidget->setItem(fila,2,new QTableWidgetItem(produc->value(2).toString()));
             ui->invetario_tableWidget->setItem(fila,3,new QTableWidgetItem(produc->value(3).toString()));

         }
     }

}



void Encargado::on_Actubtn_clicked()
{
    fila = ui->invetario_tableWidget->currentRow();
    id = ui->invetario_tableWidget->item(fila,0)->text().toInt();
    QString nom,descripcion;
    QSqlQuery actualizar(dbconexion);
    int canti;

    actualizar.prepare("SELECT nombre_pr,descripcion_pr,cantidad  FROM inventario where idProducto ='"+QString::number(id)+"'");
    if(actualizar.exec())
    {
        actualizar.next();
        nom=actualizar.value(0).toString();
        descripcion=actualizar.value(1).toString();
        canti=actualizar.value(2).toInt();

        ui->nombre_2->setText(nom);
        ui->descripcion->setText(descripcion);
        ui->cantidad->setText(QString::number(canti));
    }
    cont=1;
    ui->paginas->setCurrentIndex(3);

}

void Encargado::on_GuaPrbtn_clicked()
{
    int ncantidad;
    QSqlQuery actualizarCan(dbconexion);
    ncantidad=ui->cantidad->text().toInt();
    actualizarCan.prepare("UPDATE inventario SET cantidad='"+ QString::number(ncantidad) +"' WHERE idProducto='"+QString::number(id)+"';");

    if(cont==1)
    {
        if(actualizarCan.exec())
        {
            QMessageBox info;
            info.setWindowTitle("Datos de Producto");
            info.setText("Se ha actualizado el producto.");
            info.setStandardButtons(QMessageBox::Ok);
            info.setButtonText(QMessageBox::Ok,"Aceptar");
            info.exec();

            ui->paginas->setCurrentIndex(2);
                    QSqlQuery *produc=new QSqlQuery;
                    ui->invetario_tableWidget->clear();
                    ui->invetario_tableWidget->setRowCount(0);
                    QStringList titulos;
                    titulos<<"IDProducto"<<"Nombre"<<"Descripcion"<<"Cantidad";
                    ui->invetario_tableWidget->setColumnCount(4);
                    ui->invetario_tableWidget->setHorizontalHeaderLabels(titulos);
                    if(produc->prepare("SELECT idProducto,nombre_pr,descripcion_pr,cantidad  FROM inventario"))
                    {
                        produc->exec();
                        int fila;
                        while(produc->next()){
                            ui->invetario_tableWidget->insertRow(ui->invetario_tableWidget->rowCount());
                            fila = ui->invetario_tableWidget->rowCount()-1;
                            ui->invetario_tableWidget->setItem(fila,0,new QTableWidgetItem(produc->value(0).toString()));
                            ui->invetario_tableWidget->setItem(fila,1,new QTableWidgetItem(produc->value(1).toString()));
                            ui->invetario_tableWidget->setItem(fila,2,new QTableWidgetItem(produc->value(2).toString()));
                            ui->invetario_tableWidget->setItem(fila,3,new QTableWidgetItem(produc->value(3).toString()));

                    }

                }
                   ui->nombre_2->clear();
                   ui->descripcion->clear();
                   ui->cantidad->clear();
                   fila=0;
                   id=0;
                   ui->paginas->setCurrentIndex(2);
        }
    }
    else
    {
        QSqlQuery agregarP(dbconexion);
            QString nomp;
            QString descripcion;
            int canti;

            nomp=ui->nombre_2->text();
            descripcion=ui->descripcion->text();
            canti=ui->cantidad->text().toInt();

            agregarP.prepare("INSERT INTO inventario(nombre_pr,descripcion_pr,cantidad)""values('"+nomp+"','"+descripcion+"','"+QString::number(canti)+"');");
            if(agregarP.exec())
            {
                QMessageBox info;
                info.setWindowTitle("Datos de Producto");
                info.setText("El producto ha sido agregado.");
                info.setStandardButtons(QMessageBox::Ok);
                info.setButtonText(QMessageBox::Ok,"Aceptar");
                info.exec();
                ui->paginas->setCurrentIndex(2);
                QSqlQuery *produc=new QSqlQuery;
                ui->invetario_tableWidget->clear();
                ui->invetario_tableWidget->setRowCount(0);
                QStringList titulos;
                titulos<<"IDProducto"<<"Nombre"<<"Descripcion"<<"Cantidad";
                ui->invetario_tableWidget->setColumnCount(4);
                ui->invetario_tableWidget->setHorizontalHeaderLabels(titulos);
                if(produc->prepare("SELECT idProducto,nombre_pr,descripcion_pr,cantidad  FROM inventario"))
                {
                    produc->exec();
                    int fila;
                    while(produc->next()){
                        ui->invetario_tableWidget->insertRow(ui->invetario_tableWidget->rowCount());
                        fila = ui->invetario_tableWidget->rowCount()-1;
                        ui->invetario_tableWidget->setItem(fila,0,new QTableWidgetItem(produc->value(0).toString()));
                        ui->invetario_tableWidget->setItem(fila,1,new QTableWidgetItem(produc->value(1).toString()));
                        ui->invetario_tableWidget->setItem(fila,2,new QTableWidgetItem(produc->value(2).toString()));
                        ui->invetario_tableWidget->setItem(fila,3,new QTableWidgetItem(produc->value(3).toString()));

                }
            }
            else{
                qDebug()<<"no inserto";

            }
    }

}
}

void Encargado::on_agregarPbtn_clicked()
{
    ui->paginas->setCurrentIndex(3);
    cont=2;

}

void Encargado::on_eliminarPbtn_clicked()
{
    fila = ui->invetario_tableWidget->currentRow();
    id = ui->invetario_tableWidget->item(fila,0)->text().toInt();
    QSqlQuery eliminar(dbconexion);

    QMessageBox ask;
    ask.setWindowTitle("\t\tAdvertencia");
    ask.setText("El producto se va a eliminar");
    ask.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    ask.setDefaultButton(QMessageBox::Yes);
    ask.setButtonText(QMessageBox::Yes,"Aceptar");
    ask.setButtonText(QMessageBox::No,"Cancelar");

    if(ask.exec()==QMessageBox::Yes){

        if(eliminar.exec("DELETE FROM inventario WHERE idProducto = "+QString::number(id)+";")){

            QMessageBox info;
            info.setWindowTitle("Datos de Prodcuto");
            info.setText("Su producti ha sido eliminado de forma exitosa.");
            info.setStandardButtons(QMessageBox::Ok);
            info.setButtonText(QMessageBox::Ok,"Aceptar");
            info.exec();
            QSqlQuery *produc=new QSqlQuery;
            ui->invetario_tableWidget->clear();
            ui->invetario_tableWidget->setRowCount(0);
            QStringList titulos;
            titulos<<"IDProducto"<<"Nombre"<<"Descripcion"<<"Cantidad";
            ui->invetario_tableWidget->setColumnCount(4);
            ui->invetario_tableWidget->setHorizontalHeaderLabels(titulos);
            if(produc->prepare("SELECT idProducto,nombre_pr,descripcion_pr,cantidad  FROM inventario"))
            {
                produc->exec();
                int fila;
                while(produc->next()){
                    ui->invetario_tableWidget->insertRow(ui->invetario_tableWidget->rowCount());
                    fila = ui->invetario_tableWidget->rowCount()-1;
                    ui->invetario_tableWidget->setItem(fila,0,new QTableWidgetItem(produc->value(0).toString()));
                    ui->invetario_tableWidget->setItem(fila,1,new QTableWidgetItem(produc->value(1).toString()));
                    ui->invetario_tableWidget->setItem(fila,2,new QTableWidgetItem(produc->value(2).toString()));
                    ui->invetario_tableWidget->setItem(fila,3,new QTableWidgetItem(produc->value(3).toString()));

            }
        }
        else{
            qDebug()<<"NO se eliminó nada";
        }
    }
  }
}
