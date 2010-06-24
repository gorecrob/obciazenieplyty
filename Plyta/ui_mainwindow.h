/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 21. Jun 19:04:33 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *line_A;
    QLabel *label_2;
    QLineEdit *line_B;
    QLabel *label_3;
    QLineEdit *line_E;
    QLabel *label_4;
    QLineEdit *line_v;
    QPushButton *pushButton;
    QWidget *widget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QToolButton *border_top;
    QToolButton *border_left;
    QToolButton *border_bottom;
    QToolButton *border_right;
    QSpinBox *spinBox;
    QLabel *label_5;
    QLineEdit *line_h;
    QLabel *label_6;
    QLineEdit *line_q;
    QLabel *label_7;
    QLabel *label_8;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(707, 439);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        line_A = new QLineEdit(centralWidget);
        line_A->setObjectName(QString::fromUtf8("line_A"));

        gridLayout->addWidget(line_A, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        line_B = new QLineEdit(centralWidget);
        line_B->setObjectName(QString::fromUtf8("line_B"));

        gridLayout->addWidget(line_B, 2, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        line_E = new QLineEdit(centralWidget);
        line_E->setObjectName(QString::fromUtf8("line_E"));

        gridLayout->addWidget(line_E, 3, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        line_v = new QLineEdit(centralWidget);
        line_v->setObjectName(QString::fromUtf8("line_v"));

        gridLayout->addWidget(line_v, 4, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 7, 1, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(400, 0));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 0, 301, 261));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        border_top = new QToolButton(gridLayoutWidget);
        border_top->setObjectName(QString::fromUtf8("border_top"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(border_top->sizePolicy().hasHeightForWidth());
        border_top->setSizePolicy(sizePolicy);
        border_top->setCheckable(true);
        border_top->setChecked(true);

        gridLayout_2->addWidget(border_top, 0, 1, 1, 2);

        border_left = new QToolButton(gridLayoutWidget);
        border_left->setObjectName(QString::fromUtf8("border_left"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(border_left->sizePolicy().hasHeightForWidth());
        border_left->setSizePolicy(sizePolicy1);
        border_left->setCheckable(true);
        border_left->setChecked(true);

        gridLayout_2->addWidget(border_left, 1, 0, 2, 1);

        border_bottom = new QToolButton(gridLayoutWidget);
        border_bottom->setObjectName(QString::fromUtf8("border_bottom"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(border_bottom->sizePolicy().hasHeightForWidth());
        border_bottom->setSizePolicy(sizePolicy2);
        border_bottom->setCheckable(true);
        border_bottom->setChecked(true);

        gridLayout_2->addWidget(border_bottom, 3, 1, 1, 2);

        border_right = new QToolButton(gridLayoutWidget);
        border_right->setObjectName(QString::fromUtf8("border_right"));
        sizePolicy1.setHeightForWidth(border_right->sizePolicy().hasHeightForWidth());
        border_right->setSizePolicy(sizePolicy1);
        border_right->setCheckable(true);
        border_right->setChecked(true);

        gridLayout_2->addWidget(border_right, 1, 3, 2, 1);


        gridLayout->addWidget(widget, 1, 2, 7, 1);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy3);
        spinBox->setMinimum(2);
        spinBox->setMaximum(10);
        spinBox->setValue(3);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        line_h = new QLineEdit(centralWidget);
        line_h->setObjectName(QString::fromUtf8("line_h"));

        gridLayout->addWidget(line_h, 5, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        line_q = new QLineEdit(centralWidget);
        line_q->setObjectName(QString::fromUtf8("line_q"));

        gridLayout->addWidget(line_q, 6, 1, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(spinBox, line_A);
        QWidget::setTabOrder(line_A, line_B);
        QWidget::setTabOrder(line_B, line_E);
        QWidget::setTabOrder(line_E, line_v);
        QWidget::setTabOrder(line_v, line_h);
        QWidget::setTabOrder(line_h, line_q);
        QWidget::setTabOrder(line_q, pushButton);
        QWidget::setTabOrder(pushButton, border_left);
        QWidget::setTabOrder(border_left, border_bottom);
        QWidget::setTabOrder(border_bottom, border_top);
        QWidget::setTabOrder(border_top, border_right);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Dlugosc a", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Dlugosc b", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "E", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "mi v", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Oblicz", 0, QApplication::UnicodeUTF8));
        border_top->setText(QString());
        border_left->setText(QString());
        border_bottom->setText(QString());
        border_right->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Macierz", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Wysokosc h", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "q", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Wybierz punkty przegubu oraz punktu obciazenia:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
