#include "typingtest.h"
#include "ui_typingtest.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QDebug>

TypingTest::TypingTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TypingTest)
{
    ui->setupUi(this);

    QPixmap bkgnd("./bg.png"); //***Put the path for the background image here.***
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    indexForCursorSpace = 0;
    startPos = 0;
    endPos = 0;
    tempWord = "";
    colorChanger = "";
    wordToChange = "";
    cDown = new QTimer;
    lcdDisp = 60;
    time = QTime(0, 0, 0);
    accuracy = 0;
    randNum = 0;

    seedTime();
    openFile();

    tCursor = ui->displayTextEdit->textCursor();

    getSpacePos();
    highlightText();
    getTempWord();
    initiateLcd();

    connect(ui->inputTextEdit, SIGNAL(textChanged()), this, SLOT(wordChecker()));
    connect(cDown, SIGNAL(timeout()), this, SLOT(updateLcd()));
    connect(ui->inputTextEdit, SIGNAL(textChanged()), this, SLOT(startCDown()));
}

TypingTest::~TypingTest()
{
    delete ui;
}

void TypingTest::updateLcd()
{
    if(lcdDisp == 0)
    {
        cDown->stop();
        ui->inputTextEdit->clear();
        ui->inputTextEdit->setDisabled(1);
        calculate();
        QMessageBox::information(this, tr("Time's Up!"), tr("  Statistics:\nTotal Entered Words: %1\nCorrect Words: %2"
                                                      "\nMistyped Words: %3"
                                                     "\nAccuracy: %4%\nTotal Words per Minute: %2")
                                .arg(QString::number(results.at(0)))
                                .arg(QString::number(results.at(1)))
                                .arg(QString::number(results.at(2)))
                                .arg(QString::number(accuracy, 'f', 2)));
    }
    else
    {
        lcdDisp--;
        initiateLcd();
    }
}

void TypingTest::startCDown()
{
    if(!ui->inputTextEdit->document()->isEmpty() && spaceCheck.size() > 0)
    {
    cDown->start(1000);
    disconnect(ui->inputTextEdit, SIGNAL(textChanged()), this, SLOT(startCDown()));
    }
}

void TypingTest::highlightText()
{
    fmt1.setBackground(Qt::lightGray);
    startPos = spaceIndex.at(indexForCursorSpace) + 1;
    endPos = spaceIndex.at(indexForCursorSpace + 1);
    tCursor.setPosition(startPos);
    tCursorScroll = tCursor;
    tCursor.setPosition(endPos, QTextCursor::KeepAnchor);
    tCursor.setCharFormat(fmt1);
    ui->displayTextEdit->setTextCursor(tCursorScroll);
}

void TypingTest::removeHightlight()
{
    fmt1.setBackground(Qt::transparent);
    tCursor.setCharFormat(fmt1);
}

void TypingTest::getTempWord()
{
    tempWord.clear();
    for(int i = spaceIndex.at(indexForCursorSpace) + 1; i < text.size(); i++)
    {
        if(!text.at(i).isSpace())
            tempWord.push_back(text.at(i));
        else
            break;
    }
}

void TypingTest::compareByLetter()
{
    int loop = 0;

    loop = spaceCheck.size() - 1;
    tempWord.push_back(" ");
    wordToChange = tempWord;
    wordToChange.chop(1);
    fmt2.setBackground(Qt::red);


    for(int i = 0; i <= loop; i ++)
    {
        if(spaceCheck.at(i) != tempWord.at(i))
        {
            tCursor.setCharFormat(fmt2);
            break;
        }
        else
            tCursor.setCharFormat(fmt1);
    }
    tempWord.chop(1);
}

void TypingTest::compareByWord()
{
    colorChanger = spaceCheck;
    colorChanger.chop(1);

    if(colorChanger == wordToChange)
    {
        tCursor.removeSelectedText();
        tCursor.insertHtml("<FONT color=green>"+wordToChange+"</FONT>");
        wordCount.push_back(1);
    }
    else
    {
        tCursor.removeSelectedText();
        tCursor.insertHtml("<FONT color=red>"+wordToChange+"</FONT>");
        wordCount.push_back(0);
    }
}

void TypingTest::getSpacePos()
{
    spaceIndex.push_back(-1);
    for(int i = 0; i < text.size(); i++)
    {
        if(text.at(i).isSpace())
            spaceIndex.push_back(i);
    }
}

void TypingTest::openFile()
{
    generateRand();
    QString filename = "./files/"+QString::number(randNum); //***Put the path for the files folder here.***

    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Notepad"), tr("Cannot read file %1:\%2.")
                             .arg(filename)
                             .arg(file.errorString()));
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->displayTextEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    text = ui->displayTextEdit->toPlainText();
}

void TypingTest::clearField()
{
    if(spaceCheck.at(spaceCheck.size() - 1).isSpace())
    {
        compareByWord();
        ui->inputTextEdit->clear();
        removeHightlight();
        indexForCursorSpace++;
        getTempWord();
        highlightText();
    }
}

void TypingTest::initiateLcd()
{
    QString text;

    disp = time.addSecs(lcdDisp);
    text = disp.toString("m:ss");
    ui->lcdNumber->display(text);
    ui->inputTextEdit->setEnabled(1);
}

void TypingTest::calculate()
{
    int correct = 0;
    int wrong = 0;

    for(unsigned int i = 0; i < wordCount.size(); i++)
    {
        if(wordCount.at(i) == 1)
            correct++;
    }
    wrong = wordCount.size() - correct;
    accuracy = (static_cast<double>(correct) / static_cast<double>(wordCount.size())) * 100;
    results.push_back(wordCount.size());
    results.push_back(correct);
    results.push_back(wrong);
}

void TypingTest::generateRand()
{
    int tempRand = 0;

    do
    {
        tempRand = qrand() % 8 + 1;
    }while(randNum == tempRand);
    randNum = tempRand;
}

void TypingTest::seedTime()
{
    QTime timeForSeed = QTime::currentTime();
    qsrand((uint)timeForSeed.msec());
}

void TypingTest::on_restart_clicked()
{
    indexForCursorSpace = 0;
    startPos = 0;
    endPos = 0;
    tempWord = "";
    colorChanger = "";
    wordToChange = "";
    lcdDisp = 60;
    accuracy = 0;
    spaceIndex.clear();
    wordCount.clear();
    results.clear();

    cDown->stop();
    initiateLcd();
    connect(ui->inputTextEdit, SIGNAL(textChanged()), this, SLOT(startCDown()));
    ui->displayTextEdit->clear();
    ui->inputTextEdit->clear();
    openFile();
    tCursor = ui->displayTextEdit->textCursor();
    getSpacePos();
    highlightText();
    getTempWord();
}

void TypingTest::wordChecker()
{
    spaceCheck = ui->inputTextEdit->toPlainText();

    if(!ui->inputTextEdit->document()->isEmpty() && spaceCheck.at(0).isSpace())
        ui->inputTextEdit->clear();
    if(!ui->inputTextEdit->document()->isEmpty() && spaceCheck.size() > 0)
    {
        compareByLetter();
        clearField();
    }
}

void TypingTest::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About TypingTest", "About TypingTest"
                                                       "\n\nThis application is developed by thegreathypocr1t.");
}

void TypingTest::on_actionHelp_triggered()
{
    QMessageBox::information(this, "Help", "Match the highlighted words displayed by typing the words in "
                                           "the provided space. Press the space key after you type each word. "
                                           "Input words as many as possible within one minute. The results will displayed "
                                           "after one minute. If you want to start again, just press the 'Restart' button. "
                                           "Enjoy!");
}
