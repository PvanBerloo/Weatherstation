/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTestClass
{
public:
    QWidget *centralWidge;
    QListView *listView;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtTestClass)
    {
        if (QtTestClass->objectName().isEmpty())
            QtTestClass->setObjectName(QString::fromUtf8("QtTestClass"));
        QtTestClass->resize(600, 400);
        centralWidge = new QWidget(QtTestClass);
        centralWidge->setObjectName(QString::fromUtf8("centralWidge"));
        listView = new QListView(centralWidge);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 10, 581, 271));
        label = new QLabel(centralWidge);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 290, 55, 16));
        QtTestClass->setCentralWidget(centralWidge);
        menuBar = new QMenuBar(QtTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        QtTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtTestClass->setStatusBar(statusBar);

        retranslateUi(QtTestClass);

        QMetaObject::connectSlotsByName(QtTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtTestClass)
    {
        QtTestClass->setWindowTitle(QCoreApplication::translate("QtTestClass", "QtTest", nullptr));
        label->setText(QCoreApplication::translate("QtTestClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtTestClass: public Ui_QtTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
