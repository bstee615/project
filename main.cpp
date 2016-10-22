#include "mainwidget.h"
#include <QApplication>
#include <object.h>

void UnitTest() {
	Object(10,10,10,10,"face").checkCollision(new Object(11,11,10,10,"notFace"));
}

int main(int argc, char *argv[])
{
    UnitTest();

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
