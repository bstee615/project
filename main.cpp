#include "mainwidget.h"
#include "world.h"
#include <QApplication>
#include <object.h>

void UnitTest() {
    Object::unitTest();
}

int main(int argc, char *argv[])
{
    //if (argc == 2){
    //    if (argv[1] == "-test"){
            UnitTest();
    //    }
    //}

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
