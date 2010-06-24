#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <cmath>
#include <QList>
#include <QTextBrowser>
#include <QTextEdit>
#include "checkboxgrid.h"
namespace Ui {
    class MainWindow;
}


using namespace std;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void Calculate();
    void ChangeMatrixSize(int );

private:
    enum MatrixContent{ E_FIRM_EDGE, E_FREE_EDGE, E_FREE_POINT, E_HEAVY_POINT };
    MatrixContent **lookupTable;

    double dX1;
    double dX2;
    double dX14;
    double dX24;
    double dX12X22;
    CheckBoxGrid *gridWidget;
    short iMatrixSize;
    QString printMatrix;

    Ui::MainWindow *ui;

    struct Point{
        Point(short ax,short ay, short amultiple) : x(ax), y(ay), multiple(amultiple){};
        short x;
        short y;
        short multiple;
    };

    void validatePoint( Point* aPoint );
    double* getFormulaResult(short, short);
    short getSymplifiedFormulaPart(short, short, QList<Point *> );
    double** invertMatrix( double** );
    void multipleAndShowMatrix( double **);

};

#endif // MAINWINDOW_H
