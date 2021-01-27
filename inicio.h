#ifndef INICIO_H
#define INICIO_H

#include <QMainWindow>

namespace Ui {
class Inicio;
}

class Inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Inicio(QWidget *parent = nullptr);
    ~Inicio();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Inicio *ui;
};

#endif // INICIO_H
