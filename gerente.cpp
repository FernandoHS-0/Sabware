#include "gerente.h"
#include "ui_gerente.h"
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>

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

void Gerente::on_pushButton_clicked()
{
    int id;
    id=ui->id_usuario->text().toInt();

    QSqlQuery *eliminarUsuario = new QSqlQuery();

    QMessageBox elimC;
    elimC.setWindowTitle("\t\tAdvertencia");
    elimC.setText("¿Esta seguro de eliminar su cuenta de forma permanente?");
    elimC.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    elimC.setDefaultButton(QMessageBox::Yes);
    elimC.setButtonText(QMessageBox::Yes,"Aceptar");
    elimC.setButtonText(QMessageBox::No,"Cancelar");

    if(elimC.exec()==QMessageBox::Yes){

        (eliminarUsuario->exec("DELETE FROM usuario WHERE idUsuario = "+ QString::number(id) +";"));
    }

}
