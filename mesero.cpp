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
    QSqlQuery getMesas(dbconexion);
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
        btnMesa->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D96704; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
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
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu()));
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
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu()));

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
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu()));
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
            connect(cant,SIGNAL(valueChanged(int)),SLOT(agregarElementoMenu()));
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
    QSqlQuery insertOrder(dbconexion);
    QSqlQuery estadoMesa(dbconexion);
    QString mesaactual;

    if(btnMes){
        ui->lblNoMesa->setText(btnMes->text());
        ui->stackedWidget->setCurrentIndex(1);
        mesAct = btnMes->objectName().toInt();
        mesaactual = mesAct;

        insertOrder.prepare("insert into orden(fecha,idMesero,idMesa)values(curdate(),3,"+mesaactual+");");
        insertOrder.exec();
        qDebug()<<mesaactual;//Ejecutar query para añadir orden y de ahi obtener el idorden
        //Ya se inserto en la tabla orden
    }
}

void Mesero::on_btnOrdenar_clicked()
{
    mesAct = 0;
    ui->stackedWidget->setCurrentIndex(0);
}

void Mesero::agregarElementoMenu(const int &cantidad){
    QSpinBox *nombre = dynamic_cast<QSpinBox*>(sender());
    qDebug()<<"ENTRO A LA SEÑAL";
    if(nombre){
        QString mesa,ordenAct,obtenerOrden,existe;
        mesa = mesAct;
        qDebug()<<nombre->objectName();
        qDebug()<<nombre->value();
        QSqlQuery obtenerId(dbconexion),agregarPlato(dbconexion),verificarPlato(dbconexion),aniadir(dbconexion),actualizarTabla(dbconexion);
        obtenerId.prepare("select idCajero,idOrden from orden where idMesa="+mesa+"");
        obtenerId.exec();
        obtenerId.next();
        ordenAct = obtenerId.value(0).toString();
        obtenerOrden = obtenerId.value(1).toString();

        qDebug()<<ordenAct;
        if(ordenAct==nullptr){

        verificarPlato.prepare( " SELECT idOrden, IF (' " + nombre->objectName() + " ' = idPlatillo, 'TRUE', 'FALSE') AS ESTADO FROM detalleorden WHERE idOrden = ' " + obtenerOrden + " ' ");
        verificarPlato.exec();
        while(verificarPlato.next()){
            existe = verificarPlato.value(1).toString();
        }
        if(existe == " TRUE "){
            aniadir.prepare("update detalleorden set cantidad = cantidad + "+nombre->objectName()+" where idOrden"+obtenerOrden+" and idPlatillo ="+nombre->objectName()+"");
            aniadir.exec();
            actualizarTabla.prepare("select elemento_menu.nombre_platillo,detalleorden.cantidad,detalleorden.subtotal from detalleorden   inner join elemento_menu ON 	elemento_menu.idPlatillo = detalleorden.idPlatillo where detalleorden.idOrden = "+obtenerOrden+"; ");
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
        }else{
            agregarPlato.prepare("insert into detalleorden(idPlatillo,idOrden,cantidad,subtotal)select "+nombre->objectName()+","+obtenerOrden+","+nombre->value()+",precio*"+nombre->value()+" FROM elemento_menu where idPlatillo="+nombre->objectName()+";");
            agregarPlato.exec();
            actualizarTabla.prepare("select elemento_menu.nombre_platillo,detalleorden.cantidad,detalleorden.subtotal from detalleorden   inner join elemento_menu ON 	elemento_menu.idPlatillo = detalleorden.idPlatillo where detalleorden.idOrden = "+obtenerOrden+"; ");
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

}
