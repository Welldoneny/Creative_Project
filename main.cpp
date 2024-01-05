#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //настройки неообходимые для корректной работы с реестром виндовс
    QApplication::setOrganizationName("НИИ ТПУ");    // устанавливаем название организации
    QApplication::setApplicationName("Notix");       //устанваливаем имя приложения
    // установка стандартного стиля
    a.setStyle("fusion");
    // главное окно
    MainWindow w;
    w.show();
    return a.exec();
}
