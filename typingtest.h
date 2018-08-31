#ifndef TYPINGTEST_H
#define TYPINGTEST_H

#include <QMainWindow>
#include<QTextCursor>
#include<QTextCharFormat>
#include<QTimer>
#include<QTime>
#include<iostream>
using namespace std;

namespace Ui {
class TypingTest;
}

class TypingTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit TypingTest(QWidget *parent = 0);
    ~TypingTest();

private:
    Ui::TypingTest *ui;

private slots:
    void on_restart_clicked();
    void wordChecker();
    void updateLcd();
    void startCDown();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

private:
    QString text;
    QTextCursor tCursor;
    QTextCursor tCursorScroll;
    QTextCharFormat fmt1;
    QTextCharFormat fmt2;
    QString spaceCheck;
    vector<int> spaceIndex;
    int indexForCursorSpace;                     //used spaceIndex
    int startPos;
    int endPos;
    QString tempWord;
    QString colorChanger;                       //used in comparing with wordToChange
    QString wordToChange;
    vector<int> wordCount;
    QTimer *cDown;
    int lcdDisp;
    QTime time;
    QTime disp;
    vector<int> results;
    double accuracy;
    int randNum;

public:
    void highlightText();
    void removeHightlight();
    void getTempWord();
    void compareByLetter();
    void compareByWord();
    void getSpacePos();
    void openFile();
    void clearField();
    void initiateLcd();
    void calculate();
    void generateRand();
    void seedTime();
};

#endif // TYPINGTEST_H
