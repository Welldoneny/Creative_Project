#include "mainwindow.h"
#include "operation_systems.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef Q_OS_WIN32
   //QMessageBox::warning(0, QObject::tr("System"), QObject::tr("Windows"));
    OPERATION_SYSTEM_OF_USER = 1;
   //настройки неообходимые для корректной работы с реестром виндовс
   QApplication::setOrganizationName("НИИ ТПУ");    // устанавливаем название организации
   QApplication::setApplicationName("Notix");       //устанваливаем имя приложения
#endif

#ifdef Q_OS_LINUX
   // QMessageBox::warning(0, QObject::tr("System"), QObject::tr("Linux"));
   OPERATION_SYSTEM_OF_USER = 2;
#endif

    // установка стандартного стиля
    a.setStyle("fusion");
    // главное окно
    MainWindow w;
    w.show();
    return a.exec();
}
