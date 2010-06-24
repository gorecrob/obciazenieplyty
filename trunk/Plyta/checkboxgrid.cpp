#include "checkboxgrid.h"

CheckBoxGrid::CheckBoxGrid( short matrixSize, QWidget *parent ) :
    QWidget(parent), iMatrixSize(matrixSize)
{
    iGridLayout = new QGridLayout(this);
    iCheckBoxes = new QCheckBox*[matrixSize]();
    for(int i = 0 ; i < matrixSize ; i++ )
    {
        iCheckBoxes[i] = new QCheckBox[matrixSize]();
        for(int j = 0; j < matrixSize ; j++ )
        {
            iCheckBoxes[i][j].setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            iGridLayout->addWidget(&iCheckBoxes[i][j],i,j);
        }
    }
}

CheckBoxGrid::~CheckBoxGrid()
{
    for( int i = 0; i < iMatrixSize ; i++ )
        for( int j = 0; j < iMatrixSize ; j++ )
            iGridLayout->removeWidget(&iCheckBoxes[i][j]);
    for( int i = 0; i < iMatrixSize ; i++ )
            delete [] iCheckBoxes[i];
    delete [] iCheckBoxes;

}

bool CheckBoxGrid::isChecked(short i, short j)
{
    return iCheckBoxes[i][j].isChecked();
}
