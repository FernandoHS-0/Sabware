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
    ui->stackedWidget->setCurrentIndex(2);

}

void Gerente::on_ingresos_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Gerente::on_pushButton_4_clicked()
{
    info_ingresos.clear();
    ingresos aux;
    QSqlQuery cantidad;
    QSqlQuery ingresosG;
    QString ing;
    int eleccion = ui->comboBox_2->currentIndex();
    switch (eleccion) {
    qDebug() << "switch";
        case 1:{
            qDebug() << "caso1";
           if(cantidad.prepare("SELECT COUNT(`idOrden`) AS ordenes,usuario.nombre FROM `orden` INNER JOIN usuario ON orden.idCajero=usuario.idUsuario WHERE `fecha`='2021-03-14' GROUP BY `idCajero`")){
               cantidad.exec();
               qDebug() << "query";
               while (cantidad.next()) {
                   qDebug() << "querywhile";
                   aux.setOrden(cantidad.value(0).toInt());
                   aux.setCajero(cantidad.value(1).toString());
                   info_ingresos.append(aux);
               }
           }
           ingresosG.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE `fecha`='2021-03-14'");
           ingresosG.next();
           ing = ingresosG.value(0).toString();
           ui->label_18->setText("$"+ing);
           break;
        }
        case 2:{
            qDebug() << "caso2";
            if(cantidad.prepare("SELECT COUNT(`idOrden`) AS ordenes, usuario.nombre FROM `orden` INNER JOIN usuario ON orden.idCajero=usuario.idUsuario WHERE `fecha` BETWEEN '20210215' AND '20210220' GROUP BY `idCajero`")){
                cantidad.exec();
                qDebug() << "query2";
                while (cantidad.next()) {
                    qDebug() << "querywhile2";
                    aux.setOrden(cantidad.value(0).toInt());
                    aux.setCajero(cantidad.value(1).toString());
                    info_ingresos.append(aux);
                }
            }
            ingresosG.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE `fecha` BETWEEN '20210215' AND '20210220'");
            ingresosG.next();
            ing = ingresosG.value(0).toString();
            ui->label_18->setText("$"+ing);
            break;
        }
        case 3:{
            qDebug() << "caso3";
            if(cantidad.prepare("SELECT COUNT(`idOrden`) AS ordenes, usuario.nombre FROM `orden` INNER JOIN usuario ON orden.idCajero=usuario.idUsuario WHERE MONTH(fecha)=02 GROUP BY `idCajero`")){
                cantidad.exec();
                qDebug() << "query3";
                while (cantidad.next()) {
                    qDebug() << "querywhile3";
                    aux.setOrden(cantidad.value(0).toInt());
                    aux.setCajero(cantidad.value(1).toString());
                    info_ingresos.append(aux);
                }
            }
            ingresosG.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE MONTH(`fecha`)=02");
            ingresosG.next();
            ing = ingresosG.value(0).toString();
            ui->label_18->setText("$"+ing);
        }
        case 0:{
            break;
        }
    }

    //GRAFICA
    ingresos1 = info_ingresos;
    series = new QVector<QBarSeries*>(ingresos1.size(),0);
    for(int itrSerie=0;itrSerie<series->count();itrSerie++){
        qDebug() << "for1";
        series->operator[](itrSerie) = new QBarSeries();
    }

    //INICIALIZA LOS QBARSET
    series_set = new QVector<QBarSet*>(ingresos1.size(),0);
    for(int itrSerie=0;itrSerie<series_set->count();itrSerie++){
        qDebug() << "for2";
        series_set->operator[](itrSerie) = new QBarSet(ingresos1[itrSerie].getCajero());
    }

    for(int i = 0; i < ingresos1.size(); i++){
        qDebug() << "for3";
       series_set->at(i)->append(ingresos1[i].getOrden());
    }


    //INSERTA VALORES DE CADA QBARSET
    for(int i = 0; i < ingresos1.size(); i++){
        qDebug() << "for4";
       series->at(i)->append(series_set->at(i));
    }

    //INICIALIZA EL QCHART
    QChart *chart = new QChart();

    //INSERTA CADA QBARSERIES AL QCHART
    for(int itrSerie=0;itrSerie<series->count();itrSerie++)
        chart->addSeries(series->at(itrSerie));

    QStringList Encabezados;
    for(int i = 0; i < ingresos1.size(); i++)
        Encabezados << ingresos1[i].getCajero();

    //INICIALIZA EJE X CON SUS RESPECTIVOS CAMPOS
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(Encabezados);
    chart->addAxis(axisX, Qt::AlignBottom);

    //INICIALIZA EJE Y CON SUS RESPECTIVOS CAMPOS
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->setRange(0,26);
    axisY->setTickCount(8);
    axisY->setLabelFormat("%.0f");

    //RECORRE EL VECTOR QBARSERIES PARA VINCULARLO CON EL EJE Y
    for(int itrSerie=0;itrSerie<series->count();itrSerie++)
        series->at(itrSerie)->attachAxis(axisY);

    //PREPARA CONFIGURACION DE VISUALIZACION DEL QCHART
    chart->setTitle("PROYECCIONES POR CAJERO");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //INICIALIZA LA VISTA DEL QCHARTVIEW COLOCANDO EL QCHART COMO PADRE
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //SE INSERTA EL QCHARTVIEW AL LAYOUT
    ui->gridLayout->addWidget(chartView);
    QString Diccionario = "";
    for(int i = 0; i < ingresos1.size(); i++)
    Diccionario += QString::number(i) + "- " + ingresos1[i].getOrden() + " -> " + ingresos1[i].getCajero() + "\n\n";
}

void Gerente::on_pushButton_5_clicked()
{
    QString format = ".pdf";
    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre", QDir::homePath(),"*.pdf");

    filename.remove(format);
    filename+=format;
    ui->lineEdit_6->setText(filename);
    //ui->ruta_lineEdit->setText(filename);
    QString ing2;
    int eleccion1 = ui->comboBox_2->currentIndex();
    switch (eleccion1) {
    case 1: ing2 = " POR DÍA"; break;
    case 2: ing2 = " POR SEMANA"; break;
    case 3: ing2 = " POR MES"; break;
    }

    QString nom;
    if(ui->lineEdit_6->text() != ""){
       nom = ui->lineEdit_6->text();
       QDate aux = QDate::currentDate();
       QString aux_fecha = aux.toString("yyyy/MM/dd");
       QString ruta_img = ":/imagenes/img/Logo.png";
       QString html = "<img src="+ ruta_img +" width=10px; opacity=0.4; filter=alpha(opacity=40))>"
                      "<div align=right> <h4>"+ aux_fecha+" </h4></div>"
                      "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>"
                      "<p align=center>Direccion: Av San claudio #2354</p>"
                       "<p align=center>Direccion: Codigo postal: 76640 Ciudad: Puebla de Zaragoza</p>"
                      "<p align=center>Telefono: 2224563267</p>"
                     "<h1 align=left style='color:blue;'>REGISTRO DE INGRESOS"+ing2+"</h1> "
                     "<div align=left>";
       QString html_cuerpo = "";
       for(int u = 0; u < ingresos1.size(); u++){
          html_cuerpo = html_cuerpo + "<p>Nombre del cajero : " + ingresos1[u].getCajero()+"</p><hr>";
       }
       QSqlQuery ingresoF; QString ing3;
       switch (eleccion1) {
       case 1:{
           ingresoF.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE `fecha`='2021-03-14'");
           ingresoF.next();
           ing3 = ingresoF.value(0).toString();
           break;
       }
       case 2:{
           ingresoF.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE `fecha` BETWEEN '20210215' AND '20210220'");
           ingresoF.next();
           ing3 = ingresoF.value(0).toString();
           break;
       }
       case 3: {
           ingresoF.exec("SELECT SUM(`total`) AS ingresos FROM `orden` WHERE MONTH(fecha)=02 ");
           ingresoF.next();
           ing3 = ingresoF.value(0).toString();
           break;
       }
       }
       QString html_final = "Total: $" +ing3+" <br>"+
                        "DERECHOS RESERVADOS POR TRABAJADORES Y SOCIOS DE SYSTEM COMPANY";

       QString html_completo = html + html_cuerpo + html_final;
            QTextDocument document;
            document.setHtml(html_completo);

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(nom);
            printer.setPageMargins(QMarginsF(15, 15, 15, 15));

            document.print(&printer);

           ui->lineEdit->clear();

            QMessageBox::information(this,"Reporte","Reporte generado","Aceptar");
    }else{
          QMessageBox::information(this,"Factura","Debe elejir una carpeta de almacenamiento","Acpetar");
         }
}
