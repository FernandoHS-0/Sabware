#ifndef ENCARGADO_H
#define ENCARGADO_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Encargado;
}

class Encargado : public QWidget
{
    Q_OBJECT

public:
    explicit Encargado(QWidget *parent = nullptr);
    ~Encargado();
public slots:
    void reloj();

private:
    Ui::Encargado *ui;
    QTimer *timer;
};

#endif // ENCARGADO_H
