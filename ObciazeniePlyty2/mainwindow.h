#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void obliczPunkt(int i, int j);
    double obliczWspolczynnikiA (int i, int j);
    void utworzTablice();
    void usunTablice();
    void punktyPrzegubu();
    void punktyObciazenia();
    void wypiszDane();
    void odwracanieMacierzy();
    void mnozenieMacierzy();


private:
    Ui::MainWindow *ui;
    double deltaX1;
    double deltaX2;
    double wysokosc;
    double nacisk;
    double wartosc_mi;
    int rozmiar_macierzy;
    int W1[3], W2[3], W3[3], W4[3], W5[3], W6[3], W7[3], W8[3], W9[3], W10[3], W11[3], W12[3], W13[3], W14[3], W15[3], W16[3], W17[3], W18[3], W19[3];
    int **wsp_przegubu;
    double *wsp_obciazenia;
    //int wsp_przegubu[100][2];
    double **wspolczynnikiA;
    double **macierzOdw;
    double *macierzWynikowa;
    double **X;
    //float wspolczynnikiA [100][100];
    int ilosc_pkt_przegubu;
    int ilosc_pkt_obciazenia;
    int petla;
    double qd;


public slots:
    void oblicz();
    void wyczysc();

};

#endif // MAINWINDOW_H
