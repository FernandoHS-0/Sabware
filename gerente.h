#ifndef GERENTE_H
#define GERENTE_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <string>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QList>
#include "ingresos.h"
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include "QtCharts/QChartView"
#include "QtCharts/QChartView"
#include "QtCharts/QBarSeries"
#include "QtCharts/QBarSet"
#include "QtCharts/QLegend"
#include "QtCharts/QBarCategoryAxis"
#include "QtCharts/QHorizontalStackedBarSeries"
#include "QtCharts/QLineSeries"
#include "QtCharts/QCategoryAxis"
#include "QtCharts/QPieSeries"
#include "QtCharts/QPieSlice"
#include "QGraphicsLayout"
#include "QScatterSeries"
#include "QGraphicsSceneMouseEvent"
#include "QGraphicsView"
#include <QtPrintSupport/QPrinter>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Gerente;
}

class Gerente : public QWidget
{
    Q_OBJECT

public:
    explicit Gerente(QWidget *parent = nullptr);
    ~Gerente();
public slots:
    void reloj();
    void cargarZona();
    void actualizarZona();
    void on_btnGuardar_clicked();



private slots:
    void on_btnSalir_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Guardar_clicked();

    void on_pushButton_3_clicked();

    void on_btnZona_clicked();

    void on_modificarZona_clicked();


    void on_eliminarZona_clicked();

    void on_agregarZona_clicked();

    void on_btnGuardar_2_clicked();

    void on_btnGestionUsr_2_clicked();

    void on_ingresos_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Gerente *ui;
    QTimer *timer;
    QSqlDatabase dconexion;
    int noZona;
    QList<ingresos> info_ingresos;
    QList<ingresos> ingresos1;
    QVector<QBarSeries *> *series;
    QVector<QBarSet *> *series_set;
    QChartView *chartView;
};

#endif // GERENTE_H
