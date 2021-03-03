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
    ui->contenedorPopup->setVisible(false);
    ui->btnGuardar->setVisible(false);
    ui->agre_Zona->setVisible(false);

    if(dconexion.open()){
        qDebug() << "Conexion establecida";
    }else{
        qDebug() << "Error en la conexion";
    }
    cargarZona();
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

void Gerente::cargarZona(){
    qDebug()<<"CARGANDO ZONA";

    QSqlQuery getMesas(dconexion);
    getMesas.prepare("SELECT count(idZona) FROM zona;");
    getMesas.exec();
    getMesas.next();
    int nRow = 0, nCol = 0;
    int totMes = getMesas.value(0).toInt();
    for (int i = 0; i < totMes; i++) {
        QString nombre = QString::number(i+1);
        QPushButton * btnZona = new QPushButton;
        btnZona->setObjectName(nombre);
        btnZona->setText("Zona " + nombre);
        btnZona->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D92B04; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");


        ui->zonasCont->addWidget(btnZona, nRow, nCol, Qt::AlignHCenter);
        connect(btnZona, SIGNAL(clicked()), SLOT(on_btnZona_clicked()));
        nCol++;
        if(i == 4){
            nRow++;
            nCol = 0;
        }

    }

}

void Gerente::on_btnZona_clicked(){
    QPushButton * btnZon = dynamic_cast<QPushButton *>(sender());
    QSqlQuery obtenerZona(dconexion),obtenerDatos(dconexion),obtenerNombre(dconexion);
    QString zonaActual;

    if(btnZon){
        ui->contenedorPopup->setVisible(true);
        btnZon->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D92B04; color: #ffffff; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->numeroZona->setText(btnZon->text());
        noZona = btnZon->objectName().toInt();
        obtenerZona.prepare("select capacidad from zona where idZona = :idZ;");
        obtenerZona.bindValue(":idZ", noZona);
        obtenerZona.exec();
        obtenerZona.next();
        obtenerNombre.prepare("select nombre from zona where idZona = :idZ;");
        obtenerNombre.bindValue(":idZ", noZona);
        obtenerNombre.exec();
        obtenerNombre.next();
        ui->nombreZona->setText(obtenerNombre.value(0).toString());



        ui->noMesas->setText(obtenerZona.value(0).toString());

        //ui->stackedWidget->setCurrentIndex(1);
    }

}


void Gerente::on_modificarZona_clicked()
{
    ui->noMesas->setReadOnly(false);
    ui->nombreZona->setReadOnly(false);
    ui->noMesas->setStyleSheet("padding-bottom: 2px; padding-top: 0px; padding-left: 0px; padding-right: 0px; border-bottom: 2px solid #D92B04; border-top: none; border-left: none; border-right: none; background-color: #ffff00;  font: 14pt 'HelvLight'; color: black;");
    ui->nombreZona->setStyleSheet("padding-bottom: 2px; padding-top: 0px; padding-left: 0px; padding-right: 0px; border-bottom: 2px solid #D92B04; border-top: none; border-left: none; border-right: none; background-color: #ffff00;  font: 14pt 'HelvLight'; color: black;");

    ui->modificarZona->setVisible(false);
    ui->btnGuardar->setVisible(true);
    ui->eliminarZona->setVisible(false);
}

void Gerente::on_btnGuardar_clicked()
{

    QMessageBox mssg1;
    mssg1.setText("¿Deseas guardar los cambios?");
    mssg1.setIcon(QMessageBox::Warning);
    mssg1.setWindowTitle("Advertencia");
    mssg1.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));;
    QAbstractButton * pButtonYes = mssg1.addButton(tr("Si"), QMessageBox::YesRole);
    QAbstractButton * pButtonNo = mssg1.addButton(tr("No"), QMessageBox::NoRole);
    int cantMesas = ui->noMesas->text().toInt();
    QString nombreZona = ui->nombreZona->text();
    QSqlQuery actualizar(dconexion);
    actualizar.prepare("update zona set capacidad = :cant, nombre =:nom where  idZona = :zona;");
    actualizar.bindValue(":cant", cantMesas);
    qDebug()<<cantMesas;
    actualizar.bindValue(":zona", noZona);
    actualizar.bindValue(":nom",nombreZona);
    qDebug()<<noZona;


    mssg1.exec();
    if(mssg1.clickedButton() == pButtonYes){
        actualizar.exec();
        QMessageBox mssg2;
        mssg2.setText("Los cambios se guardaron satisfactoriamente");
        mssg2.setIcon(QMessageBox::Warning);
        mssg2.setWindowTitle("Cambios Guardados");
        mssg2.addButton("Aceptar", QMessageBox::AcceptRole);
        mssg2.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg2.exec();
        ui->contenedorPopup->setVisible(false);
        ui->btnGuardar->setVisible(false);
        ui->modificarZona->setVisible(true);
        ui->noMesas->setStyleSheet("border: none; background-color: #ffffff;  font: 14pt 'HelvLight'; color: black;");
        ui->nombreZona->setStyleSheet("border: none; background-color: #ffffff;  font: 14pt 'HelvLight'; color: black;");

        ui->eliminarZona->setVisible(true);

    }else{

    }


}

void Gerente::on_eliminarZona_clicked()
{

    QMessageBox mssg1;
    mssg1.setText("¿Eliminar esta zona?");
    mssg1.setIcon(QMessageBox::Warning);
    mssg1.setWindowTitle("Advertencia");
    mssg1.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));;
    QAbstractButton * pButtonYes = mssg1.addButton(tr("Si"), QMessageBox::YesRole);
    QSqlQuery eliminar(dconexion);
    eliminar.prepare("delete from zona where  idZona = :zona;");
    eliminar.bindValue(":zona", noZona);
    qDebug()<<noZona;


    mssg1.exec();
    if(mssg1.clickedButton() == pButtonYes){
        eliminar.exec();
        QMessageBox mssg2;
        mssg2.setText("La zona se elimino satisfactoriamente");
        mssg2.setIcon(QMessageBox::Warning);
        mssg2.setWindowTitle("Cambios Guardados");
        mssg2.addButton("Aceptar", QMessageBox::AcceptRole);
        mssg2.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg2.exec();
        ui->contenedorPopup->setVisible(false);
        ui->btnGuardar->setVisible(false);
        ui->modificarZona->setVisible(true);
        ui->noMesas->setStyleSheet("border: none; background-color: #ffffff;  font: 14pt 'HelvLight'; color: black;");
        ui->eliminarZona->setVisible(true);


    }else{



}
    actualizarZona();
    cargarZona();
}

void Gerente::actualizarZona(){
    QList< QWidget* > children;
        do
        {
           children = ui->gridLayoutWidget_2->findChildren< QWidget* >();
           if ( children.count() == 0 )
               break;
           delete children.at( 0 );
        }
        while ( true );

}

void Gerente::on_agregarZona_clicked()
{
    ui->contenedorPopup->setVisible(false);

    ui->agregarZona->setVisible(false);
    ui->agre_Zona->setVisible(true);
}

void Gerente::on_btnGuardar_2_clicked()
{

    QMessageBox mssg1;
    mssg1.setText("¿Deseas guardar los cambios?");
    mssg1.setIcon(QMessageBox::Warning);
    mssg1.setWindowTitle("Advertencia");
    mssg1.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));;
    QAbstractButton * pButtonYes = mssg1.addButton(tr("Si"), QMessageBox::YesRole);
    QAbstractButton * pButtonNo = mssg1.addButton(tr("No"), QMessageBox::NoRole);
    int cantMesas = ui->lnCantidad->text().toInt();
    QString nombre = ui->lnNombre->text();
    QSqlQuery guardar(dconexion);
    guardar.prepare("INSERT INTO zona(idZona,capacidad,nombre) SELECT MAX(idZona) + 1, :cant, :nom FROM zona;");
    guardar.bindValue(":cant", cantMesas);
    guardar.bindValue(":nom",nombre);
    qDebug()<<cantMesas;



    mssg1.exec();
    if(mssg1.clickedButton() == pButtonYes){
        guardar.exec();
        QMessageBox mssg2;
        mssg2.setText("La zona se guardo satisfactoriamente");
        mssg2.setIcon(QMessageBox::Warning);
        mssg2.setWindowTitle("Cambios Guardados");
        mssg2.addButton("Aceptar", QMessageBox::AcceptRole);
        mssg2.setWindowIcon(QIcon(":/imagenes/img/Logo.png"));
        mssg2.exec();
        ui->agre_Zona->setVisible(false);
        ui->btnGuardar->setVisible(false);
        ui->modificarZona->setVisible(true);
        ui->noMesas->setStyleSheet("border: none; background-color: #ffffff;  font: 14pt 'HelvLight'; color: black;");
        ui->nombreZona->setStyleSheet("border: none; background-color: #ffffff;  font: 14pt 'HelvLight'; color: black;");

        ui->eliminarZona->setVisible(true);
        ui->agregarZona->setVisible(true);

    }else{

    }

    actualizarZona();
    cargarZona();

}

void Gerente::on_btnGestionUsr_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}
