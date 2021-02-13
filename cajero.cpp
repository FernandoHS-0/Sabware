#include "cajero.h"
#include "ui_cajero.h"
#include <QDateTime>

Cajero::Cajero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cajero)
{
    ui->setupUi(this);
    dbconexion.setDatabaseName("sabware_bd");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
}

Cajero::~Cajero()
{
    delete ui;
}

void Cajero::reloj(){
    QTime hora = QTime::currentTime();
    QString horaTexto = hora.toString("hh:mm");
    ui->relojD->setText(horaTexto);
}
