#include "typingtest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TypingTest w;
    w.setFixedSize(741, 372);
    w.show();

    return a.exec();
}
