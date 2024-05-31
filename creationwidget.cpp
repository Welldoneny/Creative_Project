#include "creationwidget.h"
#include "ui_creationwidget.h"
#include "operation_systems.h"
#include <QFile> // Подключаем класс QFile
#include <QTextStream> // Подключаем класс QTextStream
#include <QDebug>
#include <QProcess>
CreationWidget::CreationWidget(QWidget *parent): QWidget(parent), ui(new Ui::CreationWidget)
{
    ui->setupUi(this);
}

CreationWidget::~CreationWidget()                                  //деструктор
{
    delete ui;
}
Note* CreationWidget::Create()                                      //метод возвращающий новую заметку
{
    QString name = ui->NameEdit->text();                            //получаем название заметки из поля ввода
    QDateTime deadLineTime = ui->DeadLineEdit->dateTime();          //получаем дату срока из поля ввода
    Note *note;                                                     //создаем указатель на заметку
    if(name == "")                                                  //если поле ввода пустое, то будет конструктор по умолчанию
    {
        note = new Note();
    }
    else                                                            //иначе в конструктор помещаем имя заметки
    {
        note = new Note(name);
    }
    note->SetDeadLine(deadLineTime);                                //устанавливаем дату срока
    if(OPERATION_SYSTEM_OF_USER == 1)                               //проверка операционной системы на windows
    {
        QProcess process;
        QString name = note->GetName();
        QFile notefile(name + ".txt");
        if(notefile.open(QIODevice::WriteOnly | QIODevice::Text))  // файл хранящий название заметки
        {                                                          // этот файл будем вызывать
            QTextStream writeStream(&notefile);
            writeStream << name;
            notefile.close(); // Закрываем файл
//            qDebug() <<"Содержимое notefile: " + name;
        }
//        QFile openfile(name + ".bat");
//        if(openfile.open(QIODevice::WriteOnly | QIODevice::Text)) //батник вызывающий файл
//        {
//            QTextStream writeStream(&openfile);
//            writeStream <<"notepad " + name + ".txt";
//            openfile.close(); // Закрываем файл
////            qDebug() <<"Содержимое openfile: notepad " + name + ".txt";
//        }
        QFile fileOut("file.bat");                                  // Связываем объект с файлом file.txt
        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))    // Если файл успешно открыт для записи в текстовом режиме
        {                                                           // Создаем объект класса QTextStream
            QTextStream writeStream(&fileOut);                      // и передаем ему адрес объекта fileOut
            QDateTime NotificationDateTime                          // получаем дату на день раньше срока
                    = deadLineTime.addDays(-1);
            QTime time = NotificationDateTime.time();
            QString formattedTime = time.toString("HH:mm");
            QDate date = NotificationDateTime.date();
            QString formattedDate = date.toString("MM/dd/yyyy");
            writeStream <<"schtasks /create /sc once /st "
            + formattedTime + " /sd " + formattedDate +
            " /tn " + note->GetName() + " /tr " + name + ".txt";
            fileOut.close();                                        // Закрываем файл
//            process.start("file.bat");                              // Запуск файла file.bat
//            process.waitForFinished();
//          fileOut.remove();
//qDebug() <<"Содержимое fileOut: schtasks /create /sc once /st "
//           + formattedTime + " /sd " + formattedDate +
//           " /tn " + note->GetName() + " /tr " + name + ".txt";
        }
    }
    return note;                                                    //возвращаем заметку
}

void CreationWidget::on_CreateNoteBtn_clicked()                     //слот вызывающийся сигналом клика
{
    Note *n = Create();                                             //создаем заметку
    emit signalCreate(n);                                           //подаем сигнал о создании заметки
    this->close();                                                  //закрываем окно
}
