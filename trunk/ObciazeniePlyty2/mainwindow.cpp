#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //testowe wartosc
    ui->rozmiarMacierzy->setText("3");
    ui->dlugoscA->setText("6");
    ui->dlogoscB->setText("8");
    ui->wartosc_mi->setText("0.15");
    ui->wysokoscH->setText("0.25");
    ui->watroscQ->setText("10");
    ui->nacisk_E->setText("30000000");
    ui->punktyPrzegubu->setText("0,0;0,1;0,2;0,3;0,4");
    ui->punktyObciazenia->setText("3;4;5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::wyczysc()
{
    ui->dlogoscB->clear();
    ui->dlugoscA->clear();
    ui->wartosc_mi->clear();
    ui->wysokoscH->clear();
    ui->nacisk_E->clear();
    ui->textBrowser->clear();
    ui->rozmiarMacierzy->clear();
    ui->punktyPrzegubu->clear();
    ui->punktyObciazenia->clear();
    ui->watroscQ->clear();

}

void MainWindow::oblicz()
{


//Pobieranie danych z okna i konwersja na double
QString rozmiar_macierzyString = ui->rozmiarMacierzy->text();
rozmiar_macierzy = rozmiar_macierzyString.toInt();
QString deltaX1string = ui->dlugoscA->text();
deltaX1 = deltaX1string.toDouble();
deltaX1 = deltaX1/(rozmiar_macierzy+1);
QString deltaX2string = ui->dlogoscB->text();
deltaX2 = deltaX2string.toDouble();
deltaX2 = deltaX2/(rozmiar_macierzy+1);
QString wysokoscstring = ui->wysokoscH->text();
wysokosc = wysokoscstring.toDouble();
QString wartosc_mistring = ui->wartosc_mi->text();
wartosc_mi = wartosc_mistring.toDouble();
QString wartosc_qstring = ui->watroscQ->text();
double warosc_Q = wartosc_qstring.toDouble();
//wartosc_mi = wartosc_mistring.toDouble();
QString wartosc_Estring = ui->nacisk_E->text();
double warosc_E = wartosc_Estring.toDouble();



double wartoscD = (warosc_E*(wysokosc*wysokosc*wysokosc))/(12*(1-(wartosc_mi*wartosc_mi)));
qd = warosc_Q/wartoscD;



utworzTablice();
punktyPrzegubu();
punktyObciazenia();

petla = 0;
wspolczynnikiA = new double *[(rozmiar_macierzy*rozmiar_macierzy)];
for (int i=0;i<(rozmiar_macierzy*rozmiar_macierzy);i++)
{
   *(wspolczynnikiA+i)=new double[(rozmiar_macierzy*rozmiar_macierzy)];
}

for (int m=1; m<=rozmiar_macierzy; m++)
{
    for (int n=1; n<=rozmiar_macierzy; n++)
    {
    obliczPunkt(n,m );
    petla++;
    }

}
odwracanieMacierzy();
mnozenieMacierzy();
wypiszDane();
usunTablice();

}


void MainWindow::utworzTablice()
{
    //utworz tablice wspolczynnikow A
    wspolczynnikiA = new double *[(rozmiar_macierzy*rozmiar_macierzy)];
    for (int i=0;i<(rozmiar_macierzy*rozmiar_macierzy);i++)
    {
       *(wspolczynnikiA+i)=new double[(rozmiar_macierzy*rozmiar_macierzy)];
    }

    wsp_przegubu = new int *[ilosc_pkt_przegubu];
    for (int i=0;i<(ilosc_pkt_przegubu);i++)
    {
       *(wsp_przegubu+i)=new int[2];
    }

}

void MainWindow::usunTablice()
{

    //usun tablice wspolczynnikow A
    for (int y = 0; y < (rozmiar_macierzy*rozmiar_macierzy); y++)
    {
        delete [] wspolczynnikiA[y];
    }
    delete [] wspolczynnikiA;

    //usun tablice macierzy odwroconej
    for (int y = 0; y < (rozmiar_macierzy*rozmiar_macierzy); y++)
    {
        delete [] macierzOdw[y];
    }
    delete [] macierzOdw;
    delete [] macierzWynikowa;
    delete [] wsp_obciazenia;
}


void MainWindow::odwracanieMacierzy()
{
    int i, j, k, n;
    double wsp_1;
    double tempor2;
    n = rozmiar_macierzy*rozmiar_macierzy;
    macierzOdw = new double *[n];
    for (int q = 0 ; q<n; q++)
    {
       *(macierzOdw+q)=new double[n];
    }

    //double X[n][2*n];
    X = new double *[n];
    for (int q = 0; q<n; q++)
    {
       *(X+q) = new double [2*n];
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            X[i][j] = wspolczynnikiA[i][j];
        }
    }
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (i == j)
            {
                X[i][n+j] = 1.0;
            }
            else
            {
                X[i][n+j] = 0.0;
            }
        }
    }
    for (i = 0; i < n; ++i)
    {
            if (X[i][i] == 0)
            {
                    j = i+1;
                    while ( X[j][i] == 0 && j < n) ++j;
                    if (j < n && X[j][i] != 0)
                            for (k = 0; k < n+n; ++k)
                            {
                                     tempor2 = X[j][k];
                                     X[j][k] = X[i][k];
                                     X[i][k] = tempor2;
                            }
                     if (X[i][i] == 0)
                      {
                       ui->textBrowser->setText("Macierzy nie mozna odwrocic.\n");
                       break;
                       //return 0;
                      }
             }
             for (k = n+n-1; k >= 0; --k) X[i][k] /= X[i][i];
             for (j = 0; j < n; ++j)
             {
                     wsp_1 = -X[j][i];
                     for (k = i; k < n+n; ++k)
                            if (j != i)
                                    X[j][k] += wsp_1 * X[i][k];
             }
    }
    for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                    macierzOdw[i][j] = X[i][n+j];



for (int y = 0; y < n; y++)
{
    delete [] X[y];
}
delete [] X;


}


void MainWindow::mnozenieMacierzy()
{
 //int w,k,i,j,x,y,z;
macierzWynikowa = new double [rozmiar_macierzy*rozmiar_macierzy];
 for (int i = 0; i < (rozmiar_macierzy*rozmiar_macierzy); i++)
 {
      for (int j = 0; j < 1; j++)
     {
         macierzWynikowa[i] = 0;
         for (int k = 0; k < (rozmiar_macierzy*rozmiar_macierzy); k++)
         {
             macierzWynikowa[i] += macierzOdw[i][k] * wsp_obciazenia[k];
         }
     }
  }


}

void MainWindow::obliczPunkt(int i, int j)
{
int a,b,c;

//a - pierwszy element tablicy (znak)
a=0;
//b - drugi element tablicy
b=1;
//c - trzeci element tablicy
c=2;
W1[a]= 1;
W1[b]= i;
W1[c]= j+2;
if ( W1[b] == rozmiar_macierzy+1  ||
     W1[b] == 0 ||
     W1[c] == rozmiar_macierzy+1 ||
     W1[c] == 0
     )
{
    W1[a]=0;
}
else
{
    if ( (W1[b] > 0 && W1[b] < rozmiar_macierzy+1) &&
         (W1[c] > 0 && W1[c] < rozmiar_macierzy+1)
         )
        {
            W1[a]=1;
        }
    else
        {
        if (W1[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W1[b]+1) && wsp_przegubu[k][l] == (W1[c]))
                        {
                            W1[a]=-1;
                        }
                    }
                }
            }
            W1[b]= abs(W1[b]);
        }
            else if (W1[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W1[b]-1) && wsp_przegubu[k][l] == (W1[c]))
                        {
                            W1[a]=-1;
                        }
                    }
                }
            }
            W1[b]=W1[b]-2;
        }
            else if (W1[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W1[b]) && wsp_przegubu[k][l] == (W1[c]+1))
                        {
                            W1[a]=-1;
                        }
                    }
                }
            }
            W1[c]= abs(W1[c]);
        }
            else if (W1[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W1[b]) && wsp_przegubu[k][l] == (W1[c]-1))
                        {
                            W1[a]=-1;
                        }
                    }
                }
            }
            W1[c]=W1[c]-2;
        }
    }
}

W2[a]= 1;
W2[b]= i;
W2[c]= j+1;
if ( W2[b] == rozmiar_macierzy+1  ||
     W2[b] == 0 ||
     W2[c] == rozmiar_macierzy+1 ||
     W2[c] == 0
     )
{
    W2[a]=0;
}
else
{
    if ( (W2[b] > 0 && W2[b] < rozmiar_macierzy+1) &&
         (W2[c] > 0 && W2[c] < rozmiar_macierzy+1)
         )
        {
            W2[a]=1;
        }
    else
        {
        if (W2[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W2[b]+1) && wsp_przegubu[k][l] == (W2[c]))
                        {
                            W2[a]=-1;
                        }
                    }
                }
            }
            W2[b]= abs(W2[b]);
        }
            else if (W2[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W2[b]-1) && wsp_przegubu[k][l] == (W2[c]))
                        {
                            W2[a]=-1;
                        }
                    }
                }
            }
         W2[b]=W2[b]-2;
        }
            else if (W2[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W2[b]) && wsp_przegubu[k][l] == (W2[c]+1))
                        {
                            W2[a]=-1;
                        }
                    }
                }
            }
            W2[c]= abs(W2[c]);
        }
            else if (W2[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W2[b]) && wsp_przegubu[k][l] == (W2[c]-1))
                        {
                            W2[a]=-1;
                        }
                    }
                }
            }
        W2[c]=W2[c]-2;
        }
    }
}
W3[a]= 1;
W3[b]= i;
W3[c]= j;
if ( W3[b] == rozmiar_macierzy+1  ||
     W3[b] == 0 ||
     W3[c] == rozmiar_macierzy+1 ||
     W3[c] == 0
     )
{
    W3[a]=0;
}
else
{
    if ( (W3[b] > 0 && W3[b] < rozmiar_macierzy+1) &&
         (W3[c] > 0 && W3[c] < rozmiar_macierzy+1)
         )
        {
            W3[a]=1;
        }
    else
        {
        if (W3[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W3[b]+1) && wsp_przegubu[k][l] == (W3[c]))
                        {
                            W3[a]=-1;
                        }
                    }
                }
            }
            W3[b]= abs(W3[b]);
        }
            else if (W3[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W3[b]-1) && wsp_przegubu[k][l] == (W3[c]))
                        {
                            W3[a]=-1;
                        }
                    }
                }
            }
            W3[b]=W3[b]-2;
        }
            else if (W3[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W3[b]) && wsp_przegubu[k][l] == (W3[c]+1))
                        {
                            W3[a]=-1;
                        }
                    }
                }
            }
            W3[c]= abs(W3[c]);
        }
            else if (W3[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W3[b]) && wsp_przegubu[k][l] == (W3[c]-1))
                        {
                            W3[a]=-1;
                        }
                    }
                }
            }
            W3[c]=W3[c]-2;
        }
    }
}


W4[a]= 1;
W4[b]= i;
W4[c]= j-1;
if ( W4[b] == rozmiar_macierzy+1  ||
     W4[b] == 0 ||
     W4[c] == rozmiar_macierzy+1 ||
     W4[c] == 0
     )
{
    W4[a]=0;
}
else
{
    if ( (W4[b] > 0 && W4[b] < rozmiar_macierzy+1) &&
         (W4[c] > 0 && W4[c] < rozmiar_macierzy+1)
         )
        {
            W4[a]=1;
        }
    else
        {
        if (W4[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W4[b]+1) && wsp_przegubu[k][l] == (W4[c]))
                        {
                            W4[a]=-1;
                        }
                    }
                }
            }
            W4[b]= abs(W4[b]);
        }
            else if (W4[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W4[b]-1) && wsp_przegubu[k][l] == (W4[c]))
                        {
                            W4[a]=-1;
                        }
                    }
                }
            }
            W4[b]=W4[b]-2;
        }
            else if (W3[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W4[b]) && wsp_przegubu[k][l] == (W4[c]+1))
                        {
                            W4[a]=-1;
                        }
                    }
                }
            }
            W4[c]= abs(W4[c]);
        }
            else if (W4[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W4[b]) && wsp_przegubu[k][l] == (W4[c]-1))
                        {
                            W4[a]=-1;
                        }
                    }
                }
            }
            W4[c]=W4[c]-2;
        }
    }
}
W5[a]= 1;
W5[b]= i;
W5[c]= j-2;
if ( W5[b] == rozmiar_macierzy+1  ||
     W5[b] == 0 ||
     W5[c] == rozmiar_macierzy+1 ||
     W5[c] == 0
     )
{
    W5[a]=0;
}
else
{
    if ( (W5[b] > 0 && W5[b] < rozmiar_macierzy+1) &&
         (W5[c] > 0 && W5[c] < rozmiar_macierzy+1)
         )
        {
            W5[a]=1;
        }
    else
        {
        if (W5[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W5[b]+1) && wsp_przegubu[k][l] == (W5[c]))
                        {
                            W5[a]=-1;
                        }
                    }
                }
            }
            W5[b]= abs(W5[b]);
        }
            else if (W5[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W5[b]-1) && wsp_przegubu[k][l] == (W5[c]))
                        {
                            W5[a]=-1;
                        }
                    }
                }
            }
            W5[b]=W5[b]-2;
        }
            else if (W5[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l == 1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W5[b]) && wsp_przegubu[k][l] == (W5[c]+1))
                        {
                            W5[a]=-1;
                        }
                    }
                }
            }
            W5[c]= abs(W5[c]);
        }
            else if (W5[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W5[b]) && wsp_przegubu[k][l] == (W5[c]-1))
                        {
                            W5[a]=-1;
                        }
                    }
                }
            }
            W5[c]=W5[c]-2;
        }
    }
}
W6[a]= 1;
W6[b]= i+1;
W6[c]= j+1;
if ( W6[b] == rozmiar_macierzy+1  ||
     W6[b] == 0 ||
     W6[c] == rozmiar_macierzy+1 ||
     W6[c] == 0
     )
{
    W6[a]=0;
}
else
{
    if ( (W6[b] > 0 && W6[b] < rozmiar_macierzy+1) &&
         (W6[c] > 0 && W6[c] < rozmiar_macierzy+1)
         )
        {
            W6[a]=1;
        }
    else
        {
        if (W6[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W6[b]+1) && wsp_przegubu[k][l] == (W6[c]))
                        {
                            W6[a]=-1;
                        }
                    }

                }
            }
            W6[b]= abs(W6[b]);
        }
            else if (W6[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W6[b]-1) && wsp_przegubu[k][l] == (W6[c]))
                        {
                            W6[a]=-1;
                        }
                    }
                }
            }
            W6[b]=W6[b]-2;
        }
            else if (W6[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W6[b]) && wsp_przegubu[k][l] == (W6[c]+1))
                        {
                            W6[a]=-1;
                        }
                    }
                }
            }
            W6[c]= abs(W6[c]);
        }
            else if (W6[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W6[b]) && wsp_przegubu[k][l] == (W6[c]-1))
                        {
                            W6[a]=-1;
                        }
                    }
                }
            }
            W6[c]=W6[c]-2;
        }
    }
}
W7[a]= 1;
W7[b]= i+1;
W7[c]= j;
if ( W7[b] == rozmiar_macierzy+1  ||
     W7[b] == 0 ||
     W7[c] == rozmiar_macierzy+1 ||
     W7[c] == 0
     )
{
    W7[a]=0;
}
else
{
    if ( (W7[b] > 0 && W7[b] < rozmiar_macierzy+1) &&
         (W7[c] > 0 && W7[c] < rozmiar_macierzy+1)
         )
        {
            W7[a]=1;
        }
    else
        {
        if (W7[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W7[b]+1) && wsp_przegubu[k][l] == (W7[c]))
                        {
                            W7[a]=-1;
                        }
                    }
                }
            }
            W7[b]= abs(W7[b]);
        }
            else if (W7[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W7[b]-1) && wsp_przegubu[k][l] == (W7[c]))
                        {
                            W7[a]=-1;
                        }
                    }
                }
            }
            W7[b]=W7[b]-2;
        }
            else if (W7[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W7[b]) && wsp_przegubu[k][l] == (W7[c]+1))
                        {
                            W7[a]=-1;
                        }
                    }
                }
            }
            W7[c]= abs(W7[c]);
        }
            else if (W7[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W7[b]) && wsp_przegubu[k][l] == (W7[c]-1))
                        {
                            W7[a]=-1;
                        }
                    }
                }
            }
            W7[c]=W7[c]-2;
        }
    }
}
W8[a]= 1;
W8[b]= i+1;
W8[c]= j-1;
if ( W8[b] == rozmiar_macierzy+1  ||
     W8[b] == 0 ||
     W8[c] == rozmiar_macierzy+1 ||
     W8[c] == 0
     )
{
    W8[a]=0;
}
else
{
    if ( (W8[b] > 0 && W8[b] < rozmiar_macierzy+1) &&
         (W8[c] > 0 && W8[c] < rozmiar_macierzy+1)
         )
        {
            W8[a]=1;
        }
    else
        {
        if (W8[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W8[b]+1) && wsp_przegubu[k][l] == (W8[c]))
                        {
                            W8[a]=-1;
                        }
                    }
                }
            }
            W8[b]= abs(W8[b]);
        }
            else if (W8[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W8[b]-1) && wsp_przegubu[k][l] == (W8[c]))
                        {
                             W8[a]=-1;
                        }
                    }
                }
            }
            W8[b]=W8[b]-2;
        }
            else if (W8[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W8[b]) && wsp_przegubu[k][l] == (W8[c]+1))
                        {
                            W8[a]=-1;
                        }
                    }
                }
            }
            W8[c]= abs(W8[c]);
        }
            else if (W8[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W8[b]) && wsp_przegubu[k][l] == (W8[c]-1))
                        {
                            W8[a]=-1;
                        }
                    }
                }
            }
            W8[c]=W8[c]-2;
        }
    }
}
W9[a]= 1;
W9[b]= i;
W9[c]= j+1;
if ( W9[b] == rozmiar_macierzy+1  ||
     W9[b] == 0 ||
     W9[c] == rozmiar_macierzy+1 ||
     W9[c] == 0
     )
{
    W9[a]=0;
}
else
{
    if ( (W9[b] > 0 && W9[b] < rozmiar_macierzy+1) &&
         (W9[c] > 0 && W9[c] < rozmiar_macierzy+1)
         )
        {
            W9[a]=1;
        }
    else
        {
        if (W9[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W9[b]+1) && wsp_przegubu[k][l] == (W9[c]))
                        {
                            W9[a]=-1;
                        }
                    }
                }
            }
            W9[b]= abs(W9[b]);
        }
            else if (W9[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W9[b]-1) && wsp_przegubu[k][l] == (W9[c]))
                        {
                             W9[a]=-1;
                        }
                    }
                }
            }
            W9[b]=W9[b]-2;
        }
            else if (W9[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W9[b]) && wsp_przegubu[k][l] == (W9[c]+1))
                        {
                            W9[a]=-1;
                        }
                    }
                }
            }
            W9[c]= abs(W9[c]);
        }
            else if (W9[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W9[b]) && wsp_przegubu[k][l] == (W9[c]-1))
                        {
                            W9[a]=-1;
                        }
                    }
                }
            }
            W9[c]=W9[c]-2;
        }
    }
}
W10[a]= 1;
W10[b]= i;
W10[c]= j;
if ( W10[b] == rozmiar_macierzy+1  ||
     W10[b] == 0 ||
     W10[c] == rozmiar_macierzy+1 ||
     W10[c] == 0
     )
{
    W10[a]=0;
}
else
{
    if ( (W10[b] > 0 && W10[b] < rozmiar_macierzy+1) &&
         (W10[c] > 0 && W10[c] < rozmiar_macierzy+1)
         )
        {
            W10[a]=1;
        }
    else
        {
        if (W10[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W10[b]+1) && wsp_przegubu[k][l] == (W10[c]))
                        {
                            W10[a]=-1;
                        }
                    }
                }
            }
            W10[b]= abs(W10[b]);
        }
            else if (W10[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W10[b]-1) && wsp_przegubu[k][l] == (W10[c]))
                        {
                            W10[a]=-1;
                        }
                    }
                }
            }
            W10[b]=W10[b]-2;
        }
            else if (W10[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W10[b]) && wsp_przegubu[k][l] == (W10[c]+1))
                        {
                            W10[a]=-1;
                        }
                    }
                }
            }
            W10[c]= abs(W10[c]);
        }
            else if (W10[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W10[b]) && wsp_przegubu[k][l] == (W10[c]-1))
                        {
                            W10[a]=-1;
                        }
                    }
                }
            }
            W10[c]=W10[c]-2;
        }
    }
}
W11[a]= 1;
W11[b]= i;
W11[c]= j-1;
if ( W11[b] == rozmiar_macierzy+1  ||
     W11[b] == 0 ||
     W11[c] == rozmiar_macierzy+1 ||
     W11[c] == 0
     )
{
    W11[a]=0;
}
else
{
    if ( (W11[b] > 0 && W11[b] < rozmiar_macierzy+1) &&
         (W11[c] > 0 && W11[c] < rozmiar_macierzy+1)
         )
        {
            W11[a]=1;
        }
    else
        {
        if (W11[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W11[b]+1) && wsp_przegubu[k][l] == (W11[c]))
                        {
                            W11[a]=-1;
                        }
                    }
                }
            }
            W11[b]= abs(W11[b]);
        }
            else if (W11[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                         if ( wsp_przegubu[k][l-1] == (W11[b]-1) && wsp_przegubu[k][l] == (W11[c]))
                        {
                            W11[a]=-1;
                        }
                     }
                }
            }
            W11[b]=W11[b]-2;
        }
            else if (W11[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W11[b]) && wsp_przegubu[k][l] == (W11[c]+1))
                        {
                            W11[a]=-1;
                        }
                    }
                }
            }
            W11[c]= abs(W11[c]);
        }
            else if (W11[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W11[b]) && wsp_przegubu[k][l] == (W11[c]-1))
                        {
                            W11[a]=-1;
                        }
                    }
                }
            }
            W11[c]=W11[c]-2;
        }
    }
}
W12[a]= 1;
W12[b]= i-1;
W12[c]= j+1;
if ( W12[b] == rozmiar_macierzy+1  ||
     W12[b] == 0 ||
     W12[c] == rozmiar_macierzy+1 ||
     W12[c] == 0
     )
{
    W12[a]=0;
}
else
{
    if ( (W12[b] > 0 && W12[b] < rozmiar_macierzy+1) &&
         (W12[c] > 0 && W12[c] < rozmiar_macierzy+1)
         )
        {
            W12[a]=1;
        }
    else
        {
        if (W12[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W12[b]+1) && wsp_przegubu[k][l] == (W12[c]))
                        {
                            W12[a]=-1;
                        }
                    }
                }
            }
            W12[b]= abs(W12[b]);
        }
            else if (W12[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W12[b]-1) && wsp_przegubu[k][l] == (W12[c]))
                        {
                            W12[a]=-1;
                        }
                    }
                }
            }
            W12[b]=W12[b]-2;
        }
            else if (W12[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W12[b]) && wsp_przegubu[k][l] == (W12[c]+1))
                        {
                             W12[a]=-1;
                        }
                    }
                }
            }
            W12[c]= abs(W12[c]);
        }
            else if (W12[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W12[b]) && wsp_przegubu[k][l] == (W12[c]-1))
                        {
                            W12[a]=-1;
                        }
                    }
                }
            }
            W12[c]=W12[c]-2;
        }
    }
}
W13[a]= 1;
W13[b]= i-1;
W13[c]= j;
if ( W13[b] == rozmiar_macierzy+1  ||
     W13[b] == 0 ||
     W13[c] == rozmiar_macierzy+1 ||
     W13[c] == 0
     )
{
    W13[a]=0;
}
else
{
    if ( (W13[b] > 0 && W13[b] < rozmiar_macierzy+1) &&
         (W13[c] > 0 && W13[c] < rozmiar_macierzy+1)
         )
        {
            W13[a]=1;
        }
    else
        {
        if (W13[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W13[b]+1) && wsp_przegubu[k][l] == (W13[c]))
                        {
                            W13[a]=-1;
                        }
                    }
                }
            }
            W13[b]= abs(W13[b]);
        }
            else if (W13[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W13[b]-1) && wsp_przegubu[k][l] == (W13[c]))
                        {
                             W13[a]=-1;
                        }
                    }
                }
            }
            W13[b]=W13[b]-2;
        }
            else if (W13[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W13[b]) && wsp_przegubu[k][l] == (W13[c]+1))
                        {
                            W13[a]=-1;
                        }
                    }
                }
            }
            W13[c]= abs(W13[c]);
        }
            else if (W13[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W13[b]) && wsp_przegubu[k][l] == (W13[c]-1))
                        {
                            W13[a]=-1;
                        }
                    }
                }
            }
            W13[c]=W13[c]-2;
        }
    }
}
W14[a]= 1;
W14[b]= i-1;
W14[c]= j-1;
if ( W14[b] == rozmiar_macierzy+1  ||
     W14[b] == 0 ||
     W14[c] == rozmiar_macierzy+1 ||
     W14[c] == 0
     )
{
    W14[a]=0;
}
else
{
    if ( (W14[b] > 0 && W14[b] < rozmiar_macierzy+1) &&
         (W14[c] > 0 && W14[c] < rozmiar_macierzy+1)
         )
        {
            W14[a]=1;
        }
    else
        {
        if (W14[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W14[b]+1) && wsp_przegubu[k][l] == (W14[c]))
                        {
                            W14[a]=-1;
                        }
                    }
                }
            }
            W14[b]= abs(W14[b]);
        }
            else if (W14[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W14[b]-1) && wsp_przegubu[k][l] == (W14[c]))
                        {
                            W14[a]=-1;
                        }
                    }
                }
            }
            W14[b]=W14[b]-2;
        }
            else if (W3[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W14[b]) && wsp_przegubu[k][l] == (W14[c]+1))
                        {
                            W14[a]=-1;
                        }
                    }
                }
            }
            W14[c]= abs(W14[c]);
        }
            else if (W14[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W14[b]) && wsp_przegubu[k][l] == (W14[c]-1))
                        {
                            W14[a]=-1;
                        }
                    }
                }
            }
            W14[c]=W14[c]-2;
        }
    }
}
W15[a]= 1;
W15[b]= i+2;
W15[c]= j;
if ( W15[b] == rozmiar_macierzy+1  ||
     W15[b] == 0 ||
     W15[c] == rozmiar_macierzy+1 ||
     W15[c] == 0
     )
{
    W15[a]=0;
}
else
{
    if ( (W15[b] > 0 && W15[b] < rozmiar_macierzy+1) &&
         (W15[c] > 0 && W15[c] < rozmiar_macierzy+1)
         )
        {
            W15[a]=1;
        }
    else
        {
        if (W15[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W15[b]+1) && wsp_przegubu[k][l] == (W15[c]))
                        {
                            W15[a]=-1;
                        }
                    }
                }
            }
            W15[b]= abs(W15[b]);
        }
            else if (W15[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W15[b]-1) && wsp_przegubu[k][l] == (W15[c]))
                        {
                            W15[a]=-1;
                        }
                    }
                }
            }
            W15[b]=W15[b]-2;
        }
            else if (W15[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W15[b]) && wsp_przegubu[k][l] == (W15[c]+1))
                        {
                             W15[a]=-1;
                        }
                    }
                }
            }
            W15[c]= abs(W15[c]);
        }
            else if (W15[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W15[b]) && wsp_przegubu[k][l] == (W15[c]-1))
                        {
                            W15[a]=-1;
                        }
                    }
                }
            }
            W15[c]=W15[c]-2;
        }
    }
}
W16[a]= 1;
W16[b]= i+1;
W16[c]= j;
if ( W16[b] == rozmiar_macierzy+1  ||
     W16[b] == 0 ||
     W16[c] == rozmiar_macierzy+1 ||
     W16[c] == 0
     )
{
    W16[a]=0;
}
else
{
    if ( (W16[b] > 0 && W16[b] < rozmiar_macierzy+1) &&
         (W16[c] > 0 && W16[c] < rozmiar_macierzy+1)
         )
        {
            W16[a]=1;
        }
    else
        {
        if (W16[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W16[b]+1) && wsp_przegubu[k][l] == (W16[c]))
                        {
                            W16[a]=-1;
                        }
                    }
                }
            }
            W16[b]= abs(W16[b]);
        }
            else if (W16[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W16[b]-1) && wsp_przegubu[k][l] == (W16[c]))
                        {
                            W16[a]=-1;
                        }
                    }
                }
            }
            W16[b]=W16[b]-2;
        }
            else if (W3[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W16[b]) && wsp_przegubu[k][l] == (W16[c]+1))
                        {
                            W16[a]=-1;
                        }
                    }
                }
            }
            W16[c]= abs(W16[c]);
        }
            else if (W16[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W16[b]) && wsp_przegubu[k][l] == (W16[c]-1))
                        {
                            W16[a]=-1;
                        }
                    }
                }
            }
            W16[c]=W16[c]-2;
        }
    }
}
W17[a]= 1;
W17[b]= i;
W17[c]= j;
if ( W17[b] == rozmiar_macierzy+1  ||
     W17[b] == 0 ||
     W17[c] == rozmiar_macierzy+1 ||
     W17[c] == 0
     )
{
    W17[a]=0;
}
else
{
    if ( (W17[b] > 0 && W17[b] < rozmiar_macierzy+1) &&
         (W17[c] > 0 && W17[c] < rozmiar_macierzy+1)
         )
        {
            W17[a]=1;
        }
    else
        {
        if (W17[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W17[b]+1) && wsp_przegubu[k][l] == (W17[c]))
                        {
                            W17[a]=-1;
                        }
                    }
                }
            }
            W17[b]= abs(W17[b]);
        }
            else if (W17[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W17[b]-1) && wsp_przegubu[k][l] == (W17[c]))
                        {
                            W17[a]=-1;
                        }
                    }
                }
            }
            W17[b]=W17[b]-2;
        }
            else if (W17[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W17[b]) && wsp_przegubu[k][l] == (W17[c]+1))
                        {
                            W17[a]=-1;
                        }
                    }
                }
            }
            W17[c]= abs(W17[c]);
        }
            else if (W17[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W17[b]) && wsp_przegubu[k][l] == (W17[c]-1))
                        {
                            W17[a]=-1;
                        }
                    }
                }
            }
            W17[c]=W17[c]-2;
        }
    }
}
W18[a]= 1;
W18[b]= i-1;
W18[c]= j;
if ( W18[b] == rozmiar_macierzy+1  ||
     W18[b] == 0 ||
     W18[c] == rozmiar_macierzy+1 ||
     W18[c] == 0
     )
{
    W18[a]=0;
}
else
{
    if ( (W18[b] > 0 && W18[b] < rozmiar_macierzy+1) &&
         (W18[c] > 0 && W18[c] < rozmiar_macierzy+1)
         )
        {
            W18[a]=1;
        }
    else
        {
        if (W18[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W18[b]+1) && wsp_przegubu[k][l] == (W18[c]))
                        {
                            W18[a]=-1;
                        }
                    }
                }
            }
            W18[b]= abs(W18[b]);
        }
            else if (W18[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W18[b]-1) && wsp_przegubu[k][l] == (W18[c]))
                        {
                            W18[a]=-1;
                        }
                    }
                }
            }
            W18[b]=W18[b]-2;
        }
            else if (W18[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W18[b]) && wsp_przegubu[k][l] == (W18[c]+1))
                        {
                            W18[a]=-1;
                        }
                    }
                }
            }
            W18[c]= abs(W18[c]);
        }
            else if (W18[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W18[b]) && wsp_przegubu[k][l] == (W18[c]-1))
                        {
                            W18[a]=-1;
                        }
                    }
                }
            }
            W18[c]=W18[c]-2;
        }
    }
}
W19[a]= 1;
W19[b]= i-2;
W19[c]= j;
if ( W19[b] == rozmiar_macierzy+1  ||
     W19[b] == 0 ||
     W19[c] == rozmiar_macierzy+1 ||
     W19[c] == 0
     )
{
    W19[a]=0;
}
else
{
    if ( (W19[b] > 0 && W19[b] < rozmiar_macierzy+1) &&
         (W19[c] > 0 && W19[c] < rozmiar_macierzy+1)
         )
        {
            W19[a]=1;
        }
    else
        {
        if (W19[b] < 0)
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W19[b]+1) && wsp_przegubu[k][l] == (W19[c]))
                        {
                            W19[a]=-1;
                        }
                    }
                }
            }
            W19[b]= abs(W19[b]);
        }
            else if (W19[b]>rozmiar_macierzy+1 )
        {
            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W19[b]-1) && wsp_przegubu[k][l] == (W19[c]))
                        {
                            W19[a]=-1;
                        }
                    }
                }
            }
            W19[b]=W19[b]-2;
        }
            else if (W19[c]<0 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W19[b]) && wsp_przegubu[k][l] == (W19[c]+1))
                        {
                            W19[a]=-1;
                        }
                    }
                }
            }
            W19[c]= abs(W19[c]);
        }
            else if (W19[c]>rozmiar_macierzy+1 )
        {

            for (int k=0; k<ilosc_pkt_przegubu; k++)
            {
                for (int l=0; l<2; l++)
                {
                    if ( l==1 )
                    {
                        if ( wsp_przegubu[k][l-1] == (W19[b]) && wsp_przegubu[k][l] == (W19[c]-1))
                        {
                            W19[a]=-1;
                        }
                    }
                }
            }
            W19[c]=W19[c]-2;
        }
    }
}
//obliczanie wspolczynnikow A
int w = 0;

for (int m=1; m<=rozmiar_macierzy; m++)
{
    for (int n=1; n<=rozmiar_macierzy; n++)
    {
    double z =  obliczWspolczynnikiA(n,m );

    wspolczynnikiA[petla][w] = z;
    w++;
    }

}

}


double MainWindow::obliczWspolczynnikiA(int i, int j)
{

int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0, a10 = 0, a11 = 0, a12 =0 , a13 = 0, a14 = 0, a15 = 0 , a16 = 0, a17 = 0, a18 = 0, a19 = 0;

if ( W1[1]==i && W1[2]==j )
{
    a1 = 1* W1[0];
}
if ( W2[1]==i && W2[2]==j )
{
    a2 = 1* W2[0];
}
if ( W3[1]==i && W3[2]==j )
{
    a3 = 1* W3[0];
}
if ( W4[1]==i && W4[2]==j )
{
    a4 = 1* W4[0];
}
if ( W5[1]==i && W5[2]==j )
{
    a5 = 1* W5[0];
}
if ( W6[1]==i && W6[2]==j )
{
    a6 = 1* W6[0];
}
if ( W7[1]==i && W7[2]==j )
{
    a7 = 1* W7[0];
}
if ( W8[1]==i && W8[2]==j )
{
    a8 = 1* W8[0];
}
if ( W9[1]==i && W9[2]==j )
{
    a9 = 1* W9[0];
}
if ( W10[1]==i && W10[2]==j )
{
    a10 = 1* W10[0];
}
if ( W11[1]==i && W11[2]==j )
{
    a11 = 1* W11[0];
}
if ( W12[1]==i && W12[2]==j )
{
    a12 = 1* W12[0];
}
if ( W13[1]==i && W13[2]==j )
{
    a13 = 1* W13[0];
}
if ( W14[1]==i && W14[2]==j )
{
    a14 = 1* W14[0];
}
if ( W15[1]==i && W15[2]==j )
{
    a15 = 1* W15[0];
}
if ( W16[1]==i && W16[2]==j )
{
    a16 = 1* W16[0];
}
if ( W17[1]==i && W17[2]==j )
{
    a17 = 1* W17[0];
}
if ( W18[1]==i && W18[2]==j )
{
    a18 = 1* W18[0];
}
if ( W19[1]==i && W19[2]==j )
{
    a19 = 1* W19[0];
}

double part1 = (1*a1 - 2*a2 + 6*a3 - 2*a4 + 1*a5)/(deltaX1*deltaX1*deltaX1*deltaX1);
double part2 = 2*( (1*a6 - 2*a7 + 1*a8 - 2*a9 + 4*a10 - 2*a11 + 1*a12 - 2*a13 +1*a14)/((deltaX1*deltaX1)*(deltaX2*deltaX2))  );
double part3 = (1*a15 - 2*a16 + 6*a17 - 2*a18 + 1*a19)/(deltaX2*deltaX2*deltaX2*deltaX2);
double wynik = part1 + part2 + part3;

return wynik;
}

void MainWindow::punktyPrzegubu()
{
QString punktyPrzegubuString = ui->punktyPrzegubu->text();
QStringList list1 = punktyPrzegubuString.split(";",QString::SkipEmptyParts );
ilosc_pkt_przegubu = list1.count();
    for (int i=0; i<ilosc_pkt_przegubu; i++)
    {
        QStringList list2 = list1[i].split(",",QString::SkipEmptyParts);
        for (int j=0; j<2; j++)
        {
            wsp_przegubu[i][j]= list2[j].toInt();
        }
    }
}

void MainWindow::punktyObciazenia()
{
QString punktyObciazeniaString = ui->punktyObciazenia->text();
QStringList list1 = punktyObciazeniaString.split(";",QString::SkipEmptyParts );
ilosc_pkt_obciazenia = list1.count();

wsp_obciazenia = new double [(rozmiar_macierzy*rozmiar_macierzy)];

for (int i = 0; i<(rozmiar_macierzy*rozmiar_macierzy); i++)
{
    wsp_obciazenia[i] = 0;
}

for (int i = 0; i< ilosc_pkt_obciazenia; i++ )
{
    int ws = list1[i].toInt();
    wsp_obciazenia[ws]= qd;
}

}

void MainWindow::wypiszDane()
{
QString wyptext;
ui->textBrowser->clear();
wyptext.append("Macierz wspólczynników A:\n\n");
for(int i=0; i<(rozmiar_macierzy*rozmiar_macierzy);i++)
{
    for(int j=0;j<(rozmiar_macierzy*rozmiar_macierzy);j++)
    {
    QString tonum;
    tonum = tonum.setNum(wspolczynnikiA[i][j]);
    wyptext.append(tonum);
    wyptext.append(" \t");
    }
    wyptext.append(" \n");
}
ui->textBrowser->setText(wyptext);
ui->textBrowser->append("Macierz odwrócona A': \n\n");

QString wypMacOd;

for(int r=0; r<(rozmiar_macierzy*rozmiar_macierzy);r++)
{
    for(int t=0;t<(rozmiar_macierzy*rozmiar_macierzy);t++)
    {
    QString tonum;
    tonum = tonum.setNum(macierzOdw[r][t]);
    wypMacOd.append(tonum);
    wypMacOd.append(" \t");
    }
    wypMacOd.append(" \n");
}
ui->textBrowser->append(wypMacOd);

ui->textBrowser->append("Wektor: \n\n");
QString wypiszWektor;
for (int i = 0; i<(rozmiar_macierzy*rozmiar_macierzy); i++)
{

        QString tonum;
        tonum = tonum.setNum(wsp_obciazenia[i]);
        wypiszWektor.append(tonum);
        wypiszWektor.append(" \n");
}
ui->textBrowser->append(wypiszWektor);


ui->textBrowser->append("Wynik: \n\n");
QString wypiszWynik;
for (int i = 0; i<(rozmiar_macierzy*rozmiar_macierzy); i++)
{

        QString tonum;
        tonum = tonum.setNum(macierzWynikowa[i]);
        wypiszWynik.append(tonum);
        wypiszWynik.append(" [m] \n");
}
ui->textBrowser->append(wypiszWynik);

}
