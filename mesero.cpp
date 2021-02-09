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
    getZona.exec("SELECT idZona FROM mesero WHERE idUsuario = 3;");
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
        QString nombre = "Mesa " + QString::number(i+1);
        QPushButton * btnMesa = new QPushButton;
        btnMesa->setObjectName(nombre);
        btnMesa->setText(nombre);
        btnMesa->setStyleSheet("QPushButton{border-radius: 20px; background-color: #D96704; color: white; font: 12pt 'HelvLight'; width: 100px; height: 100px;} QPushButton:Hover{border: 3px solid #D92B04}");
        ui->gridLayout->addWidget(btnMesa, nRow, nCol, Qt::AlignHCenter);
        connect(btnMesa, SIGNAL(clicked()), SLOT(on_btnMesa_clicked()));
        nCol++;
        if(i == 4){
            nRow++;
            nCol = 0;
        }

    }

    ui->stackedWidget->setCurrentIndex(1);

    int nRow2 = 0;
    QSqlQuery platos(dbconexion);
    if(platos.exec("Select idPlatillo, nombre_platillo, precio from elemento_menu WHERE idCategoria = 1;")){
        while (platos.next()) {
            QLabel * nombPla = new QLabel;
            QSpinBox * cant = new QSpinBox;
            nombPla->setText(platos.value(1).toString());
            nombPla->setStyleSheet("QLabel{font: 12pt 'HelvLight';}");
            cant->setObjectName(platos.value(0).toString());
            ui->gridLayout_2->addWidget(nombPla,nRow2, 0);
            ui->gridLayout_2->addWidget(cant, nRow2, 1);
            qDebug() << nRow2;
            nRow2++;
        }
    }else{
        qDebug() << "Query no ejecutado";
    }





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


void Mesero::on_btnSalir_clicked()
{
    this->close();
}

void Mesero::on_btnMesa_clicked(){
    QPushButton * btnMes = dynamic_cast<QPushButton *>(sender());
    if(btnMes){
        QMessageBox msg;
        QString nom = btnMes->objectName();
        msg.setText("Boton conectado " + nom);
        msg.exec();
    }
}
