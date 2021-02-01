#include "gerente.h"
#include "ui_gerente.h"
#include <QDateTime>
#include <QTimer>

Gerente::Gerente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gerente)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reloj()));
    timer->start(1000);
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
