#include<QApplication>
#include<QIcon>

#include"MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/Risorse/Icons/appIcon.png"));
    MainWindow main_wid;
    main_wid.show();
    return app.exec();
}

/*
 * Stack or Heap? In general, a QObject without a parent should be created on the stack
 * or defined as an subobject of another class. !!A QObject with a parent should not be
 * on the stack because then it might get deleted twice accidentally!!. All QObjects
 * created on the heap should either have a parent, or be managed somehow by another object.
*/
