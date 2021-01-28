#include "encargado.h"
#include "ui_encargado.h"
#include <QDateTime>

Encargado::Encargado(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Encargado)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
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
