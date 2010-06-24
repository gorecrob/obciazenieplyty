#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gridWidget = new CheckBoxGrid(3);
    ui->gridLayout_2->addWidget(gridWidget,1,1,2,2);
    iMatrixSize = ui->spinBox->value();
    lookupTable = new MatrixContent*[iMatrixSize+2];
    for(int i = 0 ; i < iMatrixSize+2 ; i++ )
        lookupTable[i] = new MatrixContent[iMatrixSize];

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Calculate()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(ChangeMatrixSize(int)));
}

MainWindow::~MainWindow()
{
    ui->gridLayout_2->removeWidget(gridWidget);
    delete gridWidget;
    for( int i = 0; i < iMatrixSize + 2 ; i++ )
            delete [] lookupTable[i];
    delete [] lookupTable;
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

void MainWindow::ChangeMatrixSize( int newSize )
{
    ui->gridLayout_2->removeWidget(gridWidget);
    delete gridWidget;
    gridWidget = new CheckBoxGrid((short)newSize);

    ui->gridLayout_2->addWidget(gridWidget,1,1,2,2);

   /* for( int i = 0; i < iMatrixSize + 2 ; i++ )
            delete [] lookupTable[i];
    delete [] lookupTable;*/

    iMatrixSize = newSize;
    lookupTable = new MatrixContent*[iMatrixSize+2];
    for(int i = 0 ; i < iMatrixSize + 2 ; i++ )
        lookupTable[i] = new MatrixContent[iMatrixSize+2];
}

void MainWindow::Calculate()
{
    //Sprawdzanie czy punkt jest przegubem
    if( ui->border_top->isChecked() )
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[0][i] = E_FIRM_EDGE;//utwierdzenie
    else
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[0][i] = E_FREE_EDGE;//przegub

    if( ui->border_right->isChecked() )
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[i][iMatrixSize+1] = E_FIRM_EDGE;
    else
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[i][iMatrixSize+1] = E_FREE_EDGE;

    if( ui->border_bottom->isChecked() )
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[iMatrixSize+1][i] = E_FIRM_EDGE;
    else
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[iMatrixSize+1][i] = E_FREE_EDGE;

    if( ui->border_left->isChecked() )
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[i][0] = E_FIRM_EDGE;
    else
        for(int i = 0 ; i < iMatrixSize + 2 ; i ++)
            lookupTable[i][0] = E_FREE_EDGE;

    //Sprawdzenie w ktorym punkcie jest obciazenie
    for( int i = 1 ; i < iMatrixSize + 1 ; i++ )
        for( int j = 1 ; j < iMatrixSize + 1; j++ )
            lookupTable[i][j] = gridWidget->isChecked(i-1,j-1)?E_HEAVY_POINT:E_FREE_POINT;//obciazenie:bez obciazenia

    //obliczanie delt (rozpietosci)
    dX1 = ui->line_A->text().toDouble() / (double)(iMatrixSize+1);
    dX2 = ui->line_B->text().toDouble() / (double)(iMatrixSize+1);
    dX14 = pow( dX1, 4.0 );
    dX24 = pow( dX2, 4.0 );
    dX12X22 = pow( dX1, 2.0 ) * pow( dX2, 2.0 );

    //Alokowanie pamieci na tablice wspolcyznnikow A
    double **resultMatrix =  new double*[iMatrixSize*iMatrixSize];
    short counter=0;

    for( short i = 1; i <= iMatrixSize  ; i++ )
    {
        for( short j = 1; j <= iMatrixSize  ; j++ )
        {
            //getFormulaResult wraca caly wiersz macierzy wspolczynnikow A
            resultMatrix[counter++] = getFormulaResult(j,i);
        }
    }

    //Wydrukowanie macierzy wspolczynnikow A
    for (int i=0; i<(iMatrixSize*iMatrixSize); i++)
    {
        for (int j=0; j<(iMatrixSize*iMatrixSize); j++)
        {
            printMatrix.append(QString::number(resultMatrix[i][j]));
            printMatrix.append("\t");
        }
        printMatrix.append("\n");
    }

    //invertMatrix odwracanie macierzy
    //multipleAndShowMatrix mnozenie macierzy odwroconej przez wektor obciazenia
    //i wydrukowanie wynikow
    multipleAndShowMatrix(invertMatrix(resultMatrix));

}

void MainWindow::validatePoint(Point *aPoint)
{
    //Sprawdzanie czy  na krawedzi
    if( aPoint->x == 0 || aPoint->y == 0  || aPoint->x == iMatrixSize + 1  || aPoint->y == iMatrixSize + 1 )
    {
        //Jezeli na krawedzi zeruj
        aPoint->multiple = 0;
        return;
    }
    if( aPoint->x < 0 )
    {
        aPoint->x = 1;
        if( lookupTable[0][aPoint->y] == E_FREE_EDGE )
            aPoint->multiple *= -1;//Jezeli od strony przegubu zmien znak
    }

    if( aPoint->y == iMatrixSize + 2 )
    {
        aPoint->y -= 2;
        if( lookupTable[aPoint->x][iMatrixSize+1] == E_FREE_EDGE )
            aPoint->multiple *= -1;
    }

    if( aPoint->x == iMatrixSize + 2)
    {
        aPoint->x -= 2;
        if( lookupTable[iMatrixSize + 1][aPoint->y] == E_FREE_EDGE )
            aPoint->multiple *= -1;
    }

    if( aPoint->y == -1 )
    {
        aPoint->y *= -1;
        if( lookupTable[aPoint->x][0] == E_FREE_EDGE )
            aPoint->multiple *= -1;
    }
}

double* MainWindow::getFormulaResult(short x, short y)
{
    Point *p;
    QList<Point *> pointsF1;
    QList<Point *> pointsF2;
    QList<Point *> pointsF3
            ;
    p = new Point(x,y+2,1);
    validatePoint(p);
    pointsF1.append(p);
    p = new Point(x,y+1,-4);
    validatePoint(p);
    pointsF1.append(p);
    p = new Point(x,y,6);
    validatePoint(p);
    pointsF1.append(p);
    p = new Point(x,y-1,-4);
    validatePoint(p);
    pointsF1.append(p);
    p = new Point(x,y-2,1);
    validatePoint(p);
    pointsF1.append(p);

    p = new Point(x+1,y+1,1);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x+1,y,-2);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x+1,y-1,1);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x,y+1,-2);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x,y,4);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x,y-1,-2);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x-1,y+1,1);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x-1,y,-2);
    validatePoint(p);
    pointsF2.append(p);
    p = new Point(x-1,y-1,1);
    validatePoint(p);
    pointsF2.append(p);

    p = new Point(x+2,y,1);
    validatePoint(p);
    pointsF3.append(p);
    p = new Point(x+1,y,-4);
    validatePoint(p);
    pointsF3.append(p);
    p = new Point(x,y,6);
    validatePoint(p);
    pointsF3.append(p);
    p = new Point(x-1,y,-4);
    validatePoint(p);
    pointsF3.append(p);
    p = new Point(x-2,y,1);
    validatePoint(p);
    pointsF3.append(p);

    short counter = 0;
    double *result = new double[iMatrixSize * iMatrixSize];
    for(short j = 1; j <= iMatrixSize ; j++)
    {
        for(short i = 1; i <= iMatrixSize ; i++ )
        {
            result[counter++] = ((double)getSymplifiedFormulaPart(i,j,pointsF1) / dX14) + 2* ( (short)getSymplifiedFormulaPart(i,j,pointsF2) / dX12X22 ) + (double)getSymplifiedFormulaPart(i,j,pointsF3)/dX24 ;
        }
    }

    return result;
}

short MainWindow::getSymplifiedFormulaPart(short x, short y, QList<Point *> aPoints )
{
    short result = 0;
    for(int i = 0 ; i < aPoints.count() ; i++ )
    {
        if( aPoints.at(i)->x == x && aPoints.at(i)->y == y)
            result += aPoints.at(i)->multiple;
    }
    return result;
}

double** MainWindow::invertMatrix( double **Matrix)
{
    int i, j, k, n;
    double wsp_1;
    double tempor2;
    double** resultMatrix;
    n = (int)pow(iMatrixSize, 2.0);
    resultMatrix = new double *[n];
    for (int q=0;q<n;q++)
    {
       *(resultMatrix+q)=new double[n];
    }

    double X[n][2*n];

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            X[i][j] = Matrix[i][j];
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
                       return 0;
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
                    resultMatrix[i][j] = X[i][n+j];

    return resultMatrix;
}

void MainWindow::multipleAndShowMatrix( double** aMatrix)
{

    int n = iMatrixSize * iMatrixSize;
    double resultMatrix[n];
    double multiplers[n];
    int counter = 0;
    double line_E_vlue = ui->line_E->text().toDouble();
    line_E_vlue = line_E_vlue * 1000000;

    double k = ui->line_q->text().toDouble() / ((pow( ui->line_h->text().toDouble(), 3 ) * line_E_vlue ) / ( 12.0 * ( 1.0 - pow( ui->line_v->text().toDouble(), 2 ) ) ));

    for( int i = 1 ; i < iMatrixSize + 1 ; i++ )
        for( int j = 1 ; j < iMatrixSize + 1; j++ )
            multiplers[counter++] = lookupTable[j][i]==E_HEAVY_POINT?k:0;//tworzony wektor obciazenia

    //algorytm mnozenia macierzy przez wektor
    for (int i = 0; i < n; i++)
    {
         for (int j = 0; j < 1; j++)
        {
            resultMatrix[i] = 0;
            for (int k = 0; k < n; k++)
            {
                resultMatrix[i] += aMatrix[i][k] * multiplers[k];//resultMatrix zawiera wyniki
            }
        }
     }

    //wydruk wynikow
    QWidget *a = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(a);
    QTextBrowser *area = new QTextBrowser();
    area->setLineWrapMode(QTextEdit::NoWrap);
    layout->addWidget(area);
    area->append("Macierz wspolczynnikow A: \n");
    QVariant *var = new QVariant();
    int matrixQuater = iMatrixSize*iMatrixSize;
    area->append(printMatrix);

    area->append("\n Macierz odwrocona A: \n");
    QString printAMatrix;
    for (int i = 0; i<matrixQuater; i++)
    {
        for (int j = 0; j<matrixQuater; j++)
        {
            QString tonum;
            tonum = tonum.setNum(aMatrix[i][j]);
            printAMatrix.append(tonum);
            printAMatrix.append(" \t");
        }

        printAMatrix.append("\n");
    }
    area->append(printAMatrix);

    area->append("Wektor: \n");
    printAMatrix = "";
    for (int i=0; i<matrixQuater; i++)
    {
        QString tonum;
        tonum = tonum.setNum(multiplers[i]);
        printAMatrix.append(tonum);
        printAMatrix.append(" \n");
    }
    area->append(printAMatrix);

    area->append("Wynik: \n");
    for(int i = 0 ; i < n ; i++ )
    {
        resultMatrix[i] *= -1;
        *var = resultMatrix[i];
        area->append(var->toString()+" [m]");
    }
    a->setGeometry(150,150,800,450);
    a->show();
    for(int i = 0; i < (iMatrixSize * iMatrixSize) ; i++ )
        delete [] aMatrix[i];

   delete [] aMatrix;
}
