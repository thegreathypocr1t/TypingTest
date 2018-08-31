/********************************************************************************
** Form generated from reading UI file 'typingtest.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TYPINGTEST_H
#define UI_TYPINGTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TypingTest
{
public:
    QAction *actionHelp;
    QAction *actionAbout;
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QTextEdit *inputTextEdit;
    QPushButton *restart;
    QTextEdit *displayTextEdit;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuOptions;

    void setupUi(QMainWindow *TypingTest)
    {
        if (TypingTest->objectName().isEmpty())
            TypingTest->setObjectName(QStringLiteral("TypingTest"));
        TypingTest->resize(741, 372);
        actionHelp = new QAction(TypingTest);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(TypingTest);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(TypingTest);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(590, 260, 131, 41));
        inputTextEdit = new QTextEdit(centralWidget);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));
        inputTextEdit->setGeometry(QRect(150, 260, 431, 41));
        QFont font;
        font.setPointSize(18);
        inputTextEdit->setFont(font);
        inputTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        restart = new QPushButton(centralWidget);
        restart->setObjectName(QStringLiteral("restart"));
        restart->setGeometry(QRect(20, 260, 121, 41));
        displayTextEdit = new QTextEdit(centralWidget);
        displayTextEdit->setObjectName(QStringLiteral("displayTextEdit"));
        displayTextEdit->setGeometry(QRect(20, 70, 701, 151));
        QFont font1;
        font1.setPointSize(32);
        displayTextEdit->setFont(font1);
        displayTextEdit->setAutoFillBackground(false);
        displayTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        displayTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        displayTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        displayTextEdit->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(260, 10, 221, 51));
        QFont font2;
        font2.setPointSize(33);
        label->setFont(font2);
        TypingTest->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TypingTest);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 22));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        TypingTest->setMenuBar(menuBar);

        menuBar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionHelp);
        menuOptions->addAction(actionAbout);

        retranslateUi(TypingTest);

        QMetaObject::connectSlotsByName(TypingTest);
    } // setupUi

    void retranslateUi(QMainWindow *TypingTest)
    {
        TypingTest->setWindowTitle(QApplication::translate("TypingTest", "TypingTest", nullptr));
        actionHelp->setText(QApplication::translate("TypingTest", "Help", nullptr));
#ifndef QT_NO_SHORTCUT
        actionHelp->setShortcut(QApplication::translate("TypingTest", "F1", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("TypingTest", "About...", nullptr));
        restart->setText(QApplication::translate("TypingTest", "Restart", nullptr));
        label->setText(QApplication::translate("TypingTest", "TypingTest", nullptr));
        menuOptions->setTitle(QApplication::translate("TypingTest", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TypingTest: public Ui_TypingTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPINGTEST_H
