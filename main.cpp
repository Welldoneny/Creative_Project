#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("НИИ ТПУ");
    QApplication::setApplicationName("Notix");
    // установка стандартного стиля
    a.setStyle("fusion");
    // главное окно
    MainWindow w;
    w.show();
    return a.exec();
}
