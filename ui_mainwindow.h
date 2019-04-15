/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPlay;
    QAction *actionStop;
    QAction *actionForward;
    QAction *actionBackward;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(447, 330);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionPlay->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay->setIcon(icon);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionStop->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon1);
        actionForward = new QAction(MainWindow);
        actionForward->setObjectName(QString::fromUtf8("actionForward"));
        actionForward->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForward->setIcon(icon2);
        actionBackward = new QAction(MainWindow);
        actionBackward->setObjectName(QString::fromUtf8("actionBackward"));
        actionBackward->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBackward->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setEnabled(false);

        verticalLayout->addWidget(saveButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 447, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setIconSize(QSize(18, 18));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionBackward);
        mainToolBar->addAction(actionPlay);
        mainToolBar->addAction(actionStop);
        mainToolBar->addAction(actionForward);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Game of Life", nullptr));
        actionPlay->setText(QApplication::translate("MainWindow", "Play", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPlay->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStop->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionForward->setText(QApplication::translate("MainWindow", "Forward", nullptr));
#ifndef QT_NO_SHORTCUT
        actionForward->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        actionBackward->setText(QApplication::translate("MainWindow", "Backward", nullptr));
#ifndef QT_NO_SHORTCUT
        actionBackward->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", nullptr));
#endif // QT_NO_SHORTCUT
        loadButton->setText(QApplication::translate("MainWindow", "Load", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
