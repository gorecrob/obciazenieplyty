/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 23. Jun 17:18:10 2010
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
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLineEdit *dlugoscA;
    QLabel *label_7;
    QLineEdit *dlogoscB;
    QLabel *label_8;
    QLineEdit *wysokoscH;
    QLabel *label_9;
    QLineEdit *nacisk_E;
    QLabel *label_10;
    QLineEdit *wartosc_mi;
    QLineEdit *rozmiarMacierzy;
    QLineEdit *punktyPrzegubu;
    QLineEdit *punktyObciazenia;
    QLineEdit *watroscQ;
    QLabel *label_65;
    QLabel *label_66;
    QLabel *label_67;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(793, 685);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(230, 0, 321, 261));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        dlugoscA = new QLineEdit(formLayoutWidget);
        dlugoscA->setObjectName(QString::fromUtf8("dlugoscA"));

        formLayout->setWidget(0, QFormLayout::FieldRole, dlugoscA);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        dlogoscB = new QLineEdit(formLayoutWidget);
        dlogoscB->setObjectName(QString::fromUtf8("dlogoscB"));

        formLayout->setWidget(1, QFormLayout::FieldRole, dlogoscB);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_8);

        wysokoscH = new QLineEdit(formLayoutWidget);
        wysokoscH->setObjectName(QString::fromUtf8("wysokoscH"));

        formLayout->setWidget(2, QFormLayout::FieldRole, wysokoscH);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_9);

        nacisk_E = new QLineEdit(formLayoutWidget);
        nacisk_E->setObjectName(QString::fromUtf8("nacisk_E"));

        formLayout->setWidget(3, QFormLayout::FieldRole, nacisk_E);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_10);

        wartosc_mi = new QLineEdit(formLayoutWidget);
        wartosc_mi->setObjectName(QString::fromUtf8("wartosc_mi"));

        formLayout->setWidget(4, QFormLayout::FieldRole, wartosc_mi);

        rozmiarMacierzy = new QLineEdit(formLayoutWidget);
        rozmiarMacierzy->setObjectName(QString::fromUtf8("rozmiarMacierzy"));

        formLayout->setWidget(5, QFormLayout::FieldRole, rozmiarMacierzy);

        punktyPrzegubu = new QLineEdit(formLayoutWidget);
        punktyPrzegubu->setObjectName(QString::fromUtf8("punktyPrzegubu"));

        formLayout->setWidget(6, QFormLayout::FieldRole, punktyPrzegubu);

        punktyObciazenia = new QLineEdit(formLayoutWidget);
        punktyObciazenia->setObjectName(QString::fromUtf8("punktyObciazenia"));

        formLayout->setWidget(7, QFormLayout::FieldRole, punktyObciazenia);

        watroscQ = new QLineEdit(formLayoutWidget);
        watroscQ->setObjectName(QString::fromUtf8("watroscQ"));

        formLayout->setWidget(8, QFormLayout::FieldRole, watroscQ);

        label_65 = new QLabel(formLayoutWidget);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_65);

        label_66 = new QLabel(formLayoutWidget);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_66);

        label_67 = new QLabel(formLayoutWidget);
        label_67->setObjectName(QString::fromUtf8("label_67"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_67);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 270, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 270, 75, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 290, 781, 461));
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 20, 761, 331));
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textBrowser->setLineWrapMode(QTextEdit::NoWrap);
        textBrowser->setReadOnly(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 793, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(oblicz()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(wyczysc()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "D\305\202ugo\305\233\304\207 a", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "D\305\202ugo\305\233\304\207 b", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Wysoko\305\233\304\207 h", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Nascisk E [Pa]", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "mi v", 0, QApplication::UnicodeUTF8));
        label_65->setText(QApplication::translate("MainWindow", "Rozmiar macierzy", 0, QApplication::UnicodeUTF8));
        label_66->setText(QApplication::translate("MainWindow", "Punkty przegubu", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("MainWindow", "Punkty obciazenia", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "q", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Oblicz", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Wyczy\305\233\304\207", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Wynik:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
