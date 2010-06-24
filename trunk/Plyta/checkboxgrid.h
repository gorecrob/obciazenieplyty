#ifndef CHECKBOXGRID_H
#define CHECKBOXGRID_H

#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QDebug>

class CheckBoxGrid : public QWidget
{
Q_OBJECT
public:
    explicit CheckBoxGrid(short matrixSize , QWidget *parent = 0);
    ~CheckBoxGrid();

    bool isChecked(short, short );

signals:

public slots:

private:
     QCheckBox **iCheckBoxes;
     QGridLayout *iGridLayout;
     short iMatrixSize;

};

#endif // CHECKBOXGRID_H
