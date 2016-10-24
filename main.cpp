#include "mainwidget.h"
#include "world.h"
#include <QApplication>
#include <object.h>

void UnitTest() {
	Object(10,10,10,10,"face").checkCollision(new Object(11,11,10,10,"notFace"));
	World::instance().reset();
}

int main(int argc, char *argv[])
{
    UnitTest();

    QApplication a(argc, argv);
    MainWidget w;
    w.LoadLevel("easy.lv");
    w.show();

    return a.exec();
}
