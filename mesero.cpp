#include "mesero.h"
#include "ui_mesero.h"
#include <QDateTime>
#include <QTimer>
#include "QMessageBox"
#include <QDebug>
#include <QSpinBox>

Mesero::Mesero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mesero)
{
    ui->setupUi(this);
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

    QSqlQuery getZona(dbconexion);
    getZona.exec("SELECT idZona FROM mesero WHERE idMesero = 3;");
    getZona.next();
    int zonaAct = getZona.value(0).toInt();
    qDebug() << "Zona: " << zonaAct;
    QSqlQuery getMesas(dbconexion), getEstado(dbconexion);
    getEstado.prepare("SELECT estado FROM mesa where idMesa = :noM;");
    getMesas.prepare("SELECT count(idMesa) FROM mesa WHERE idZona = :idZ;");
    getMesas.bindValue(":idZ", zonaAct);
    getMesas.exec();
    getMesas.next();
    int nRow = 0, nCol = 0;
    int totMes = getMesas.value(0).toInt();
    for (int i = 0; i < totMes; i++) {
        QString nombre = QString::number(i+1);
        QPushButton * btnMesa = new QPushButton;
        btnMesa->setObjectName(nombre);
        btnMesa->setText("Mesa " + nombre);
        getEstado.bindValue(":noM", i+1);
        getEstado.exec();
        getEstado.next();
        QString est = getEstado.value(0).toString();
        if(est == "libre"){
            btnMesa->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D96704; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        }else{
            btnMesa->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D92B04; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        }
        ui->gridLayout->addWidget(btnMesa, nRow, nCol, Qt::AlignHCenter);
        connect(btnMesa, SIGNAL(clicked()), SLOT(on_btnMesa_clicked()));
        nCol++;
        if(i == 4){
            nRow++;
            nCol = 0;
        }

    }

    ui->stackedWidget->setCurrentIndex(0);

    entradas();
    pFuerte();
    postres();
    bebidas();
}

Mesero::~Mesero()
{
    delete ui;
}

void Mesero::reloj(){
    QTime hora = QTime::currentTime();
    QString horaTexto = hora.toString("hh:mm");
    ui->relojD->setText(horaTexto);
}

void Mesero::entradas(){
    int nRow2 = 0;
    QSqlQuery platos(dbconexion);
    if(platos.exec("Select idPlatillo, nombre_platillo, precio from elemento_menu WHERE idCategoria = 1;")){
        while (platos.next()) {
            QLabel * nombPla = new QLabel;
            QSpinBox * cant = new QSpinBox;
            nombPla->setText(platos.value(1).toString());
            nombPla->setStyleSheet("QLabel{font: 12pt 'HelvLight';}");
            cant->setObjectName(platos.value(0).toString());
            cant->setMinimum(0);
            cant->resize(70, 30);
            cant->setStyleSheet("QSpinBox{font: 12pt 'HelvLight';} QSpinBox::down-button{backgrpund-color; white;} QSpinBox::up-button{backgrpund-color; white;}");
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu(int)));
            ui->gridLayout_2->addWidget(nombPla,nRow2, 0);
            ui->gridLayout_2->addWidget(cant, nRow2, 1);
            nRow2++;
        }
    }else{
        qDebug() << "Query no ejecutado";
    }
}

void Mesero::pFuerte(){
    int nRow2 = 0;
    QSqlQuery platos(dbconexion);
    if(platos.exec("Select idPlatillo, nombre_platillo, precio from elemento_menu WHERE idCategoria = 2;")){
        while (platos.next()) {
            QLabel * nombPla = new QLabel;
            QSpinBox * cant = new QSpinBox;
            nombPla->setText(platos.value(1).toString());
            nombPla->setStyleSheet("QLabel{font: 12pt 'HelvLight';}");
            cant->setObjectName(platos.value(0).toString());
            cant->setMinimum(0);
            cant->resize(70, 30);
            cant->setStyleSheet("QSpinBox{font: 12pt 'HelvLight';} QSpinBox::down-button{backgrpund-color; white;} QSpinBox::up-button{backgrpund-color; white;}");
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu(int)));

            ui->gridPFuerte->addWidget(nombPla,nRow2, 0);
            ui->gridPFuerte->addWidget(cant, nRow2, 1);
            nRow2++;
        }
    }else{
        qDebug() << "Query no ejecutado";
    }
}

void Mesero::postres(){
    int nRow2 = 0;
    QSqlQuery platos(dbconexion);
    if(platos.exec("Select idPlatillo, nombre_platillo, precio from elemento_menu WHERE idCategoria = 3;")){
        while (platos.next()) {
            QLabel * nombPla = new QLabel;
            QSpinBox * cant = new QSpinBox;
            nombPla->setText(platos.value(1).toString());
            nombPla->setStyleSheet("QLabel{font: 12pt 'HelvLight';}");
            cant->setObjectName(platos.value(0).toString());
            cant->setMinimum(0);
            cant->resize(70, 30);
            cant->setStyleSheet("QSpinBox{font: 12pt 'HelvLight';} QSpinBox::down-button{backgrpund-color; white;} QSpinBox::up-button{backgrpund-color; white;}");
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu(int)));
            ui->gridPostre->addWidget(nombPla,nRow2, 0);
            ui->gridPostre->addWidget(cant, nRow2, 1);
            nRow2++;
        }
    }else{
        qDebug() << "Query no ejecutado";
    }
}

void Mesero::bebidas(){
    int nRow2 = 0;
    QSqlQuery platos(dbconexion);
    if(platos.exec("Select idPlatillo, nombre_platillo, precio from elemento_menu WHERE idCategoria = 4;")){
        while (platos.next()) {
            QLabel * nombPla = new QLabel;
            QSpinBox * cant = new QSpinBox;
            nombPla->setText(platos.value(1).toString());
            nombPla->setStyleSheet("QLabel{font: 12pt 'HelvLight';}");
            cant->setObjectName(platos.value(0).toString());
            cant->setMinimum(0);
            cant->resize(70, 30);
            cant->setStyleSheet("QSpinBox{font: 12pt 'HelvLight';} QSpinBox::down-button{backgrpund-color; white;} QSpinBox::up-button{backgrpund-color; white;}");
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu(int)));
            ui->gridBebidas->addWidget(nombPla,nRow2, 0);
            ui->gridBebidas->addWidget(cant, nRow2, 1);
            nRow2++;
        }
    }else{
        qDebug() << "Query no ejecutado";
    }
}


void Mesero::on_btnSalir_clicked()
{
    this->close();
}

void Mesero::on_btnMesa_clicked(){
    QPushButton * btnMes = dynamic_cast<QPushButton *>(sender());
    QSqlQuery insertOrder(dbconexion), actEstado(dbconexion);
    QSqlQuery estadoMesa(dbconexion),estadoMesa1(dbconexion);
    QString mesaactual;

    if(btnMes){
        actEstado.exec("UPDATE mesa SET estado = 'ocupado' WHERE idMesa = "+mesaactual+";");
        btnMes->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D92B04; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->lblNoMesa->setText(btnMes->text());
        mesAct = btnMes->objectName().toInt();
        estadoMesa.prepare("SELECT IF(idCajero = null, 'FALSE', 'TRUE') FROM orden WHERE idMesa = :idM");
        estadoMesa.bindValue(":idM", mesAct);
        estadoMesa.exec();
        estadoMesa.next();
        qDebug()<<"select idCajero";
        if(estadoMesa.value(0).toBool()){
            qDebug()<<estadoMesa.value(0).toBool();
            QSqlQuery tabla(dbconexion);
            tabla.prepare("SELECT do.cantidad, do.subtotal, m.nombre_platillo FROM detalleorden as do INNER JOIN orden AS o ON do.idOrden = o.idOrden INNER JOIN elemento_menu AS m on do.idPlatillo = m.idPlatillo WHERE o.idMesa = :idMes and o.idCajero is null;");
            tabla.bindValue(":idMes", mesAct);
            tabla.exec();
            while (tabla.next()) {
                QString nombre = tabla.value(2).toString();
                QString cantidad = tabla.value(0).toString();
                QString subtotal = tabla.value(1).toString();
                ui->tablaOrden->setRowCount(ui->tablaOrden->rowCount()+1);

                QTableWidgetItem *nom = new QTableWidgetItem(nombre);
                QTableWidgetItem *cant = new QTableWidgetItem(cantidad);
                QTableWidgetItem *sub = new QTableWidgetItem(subtotal);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,0,nom);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,1,cant);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,2,sub);

                ui->tablaOrden->setColumnCount(3);
                ui->tablaOrden->setColumnWidth(0, 240);
                ui->tablaOrden->setColumnWidth(1, 65);
                ui->tablaOrden->setColumnWidth(2, 65);
            }
        }else
        {
            insertOrder.prepare("insert into orden(fecha,idMesero,idMesa)values(curdate(),3,:mesa);");
            insertOrder.bindValue(":mesa",mesAct);
            insertOrder.exec();
            qDebug()<<"insert orden";

        }

        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Mesero::on_btnOrdenar_clicked()
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
        mesAct = 0;
        ui->stackedWidget->setCurrentIndex(0);
        ui->tablaOrden->clearContents();
        ui->tablaOrden->model()->removeRows(0, ui->tablaOrden->rowCount());
    }

}

void Mesero::agregarElementoMenu(int cantidad){
    QSpinBox *nombre = dynamic_cast<QSpinBox*>(sender());
    qDebug()<<"ENTRO A LA SEÑAL";
    if(nombre){
        ui->tablaOrden->clearContents();
        ui->tablaOrden->model()->removeRows(0, ui->tablaOrden->rowCount());
        QString ordenAct,obtenerOrden;
        bool existe = false;
        qDebug()<<nombre->objectName();
        qDebug()<<nombre->value();
        QSqlQuery obtenerId(dbconexion),agregarPlato(dbconexion),verificarPlato(dbconexion),aniadir(dbconexion),actualizarTabla(dbconexion);
        QSqlQuery precio(dbconexion);
        obtenerId.prepare("select idOrden from orden where idMesa=:mes and idCajero is null;");
        obtenerId.bindValue(":mes",mesAct);
        obtenerId.exec();
        obtenerId.next();

        ordenAct = obtenerId.value(0).toString();
        qDebug()<<"idOrden es igual a "+ordenAct+"";
        precio.prepare("select precio from elemento_menu where idPlatillo = :pre");
        precio.bindValue(":pre",nombre->objectName());
        precio.exec();
        precio.next();
        qDebug()<<"Precio del platillo";
        int precioPlatillo =precio.value(0).toInt();

        verificarPlato.prepare( "SELECT idOrden, IF ( " + nombre->objectName() + "  = idPlatillo, 'TRUE', 'FALSE') AS ESTADO FROM detalleorden WHERE idOrden = " + ordenAct + ";");
        verificarPlato.exec();
        while(verificarPlato.next()){
            if(verificarPlato.value(1).toBool()){
                existe = true;
                break;
            }
}


        if(existe){
            qDebug()<<"entro y entonces existe";

            aniadir.prepare("update detalleorden set cantidad = cantidad + 1,subtotal = subtotal + :preci where idOrden="+ordenAct+" and idPlatillo ="+nombre->objectName()+";");
            aniadir.bindValue(":preci",precioPlatillo);
            aniadir.exec();

            actualizarTabla.prepare("select elemento_menu.nombre_platillo,detalleorden.cantidad,detalleorden.subtotal from detalleorden   inner join elemento_menu ON 	elemento_menu.idPlatillo = detalleorden.idPlatillo where detalleorden.idOrden = "+ordenAct+"; ");
            actualizarTabla.exec();
            while(actualizarTabla.next()){
                QString nombre = actualizarTabla.value(0).toString();
                QString cantidad = actualizarTabla.value(1).toString();
                QString subtotal = actualizarTabla.value(2).toString();
                ui->tablaOrden->setRowCount(ui->tablaOrden->rowCount()+1);

                QTableWidgetItem *nom = new QTableWidgetItem(nombre);
                QTableWidgetItem *cant = new QTableWidgetItem(cantidad);
                QTableWidgetItem *sub = new QTableWidgetItem(subtotal);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,0,nom);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,1,cant);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,2,sub);



            }
        }
        if(!existe){
            qDebug()<<"Entro al insertar";
            agregarPlato.prepare("insert into detalleorden(idPlatillo,idOrden,cantidad,subtotal) values("+nombre->objectName()+","+ordenAct+",1,:pre);");
            agregarPlato.bindValue(":pre",precioPlatillo);
            agregarPlato.exec();
            qDebug()<<"insertor";

            actualizarTabla.prepare("select elemento_menu.nombre_platillo,detalleorden.cantidad,detalleorden.subtotal from detalleorden   inner join elemento_menu ON 	elemento_menu.idPlatillo = detalleorden.idPlatillo where detalleorden.idOrden = "+ordenAct+"; ");
            actualizarTabla.exec();
            while(actualizarTabla.next()){
                QString nombre = actualizarTabla.value(0).toString();
                QString cantidad = actualizarTabla.value(1).toString();
                QString subtotal = actualizarTabla.value(2).toString();
                ui->tablaOrden->setRowCount(ui->tablaOrden->rowCount()+1);

                QTableWidgetItem *nom = new QTableWidgetItem(nombre);
                QTableWidgetItem *cant = new QTableWidgetItem(cantidad);
                QTableWidgetItem *sub = new QTableWidgetItem(subtotal);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,0,nom);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,1,cant);
                ui->tablaOrden->setItem(ui->tablaOrden->rowCount()-1,2,sub);



            }

        }

//NOS QUEDAMOS EN LA INSERCCION AL DETALLE DE LA ORDEN QUEDA PENDIENTE OBTENER LA INFORMACION DE LA TABLA PARA VISUALIZARLA
        //QUEDA CHECAR COMO REACCIONA EL SPINBOX EN BASE A LAS CANTIDADES
        }


        //Este es la mesa actual mesAct
//Para obtener el idOrden select idOrden where idMesa=mesAct;
//insert into detalleOrden
        //funcion para mostrar en la tabla
        //ACTULIZAR AUTOMATICAMENTE.
        //meter idCajero como 0 si no se ah finalizado
        //mientras idCajero==0 se puede agregar mas a la orden


    }



void Mesero::on_btnCobrar_clicked()
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
        QSqlQuery cobrar(dbconexion),obtenenerOrden(dbconexion);
        obtenenerOrden.prepare("select idOrden from orden where idMesa=:mes and idCajero is null;");
        obtenenerOrden.bindValue(":mes",mesAct);
        obtenenerOrden.exec();
        obtenenerOrden.next();
        QString orden;
        orden = obtenenerOrden.value(0).toString();
        qDebug()<<"la orden es"+orden+"";
        cobrar.prepare("update orden set idCajero = 4 where idOrden ="+orden+";");
        cobrar.exec();
        mesAct = 0;
        ui->stackedWidget->setCurrentIndex(0);
        ui->tablaOrden->clearContents();
        ui->tablaOrden->model()->removeRows(0, ui->tablaOrden->rowCount());

        QSqlQuery actEstado(dbconexion);
        actEstado.prepare("UPDATE mesa SET estado = 'libre' WHERE idMesa = :idMes;");
        actEstado.bindValue(":idMes", mesAct);
        actEstado.exec();
        this->update();

    }
}
