#include <QApplication>
#include "view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    view vista;
    vista.show();

    return a.exec();
}
