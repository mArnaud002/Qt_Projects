#include "todoapplication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    toDoApplication w;
    w.show();
    return a.exec();
}
