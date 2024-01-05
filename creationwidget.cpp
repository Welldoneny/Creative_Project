#include "creationwidget.h"
#include "ui_creationwidget.h"

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
    if(name == "")                                                  //если поле ввода пустое, то вызываем конструктор по умолчанию
    {
        note = new Note();
    }
    else                                                            //иначе в конструктор помещаем имя заметки
    {
        note = new Note(name);
    }
    note->SetDeadLine(deadLineTime);                                //устанавливаем дату срока
    return note;                                                    //возвращаем заметку
}

void CreationWidget::on_CreateNoteBtn_clicked()                     //слот вызывающийся сигналом клика
{
    Note *n = Create();                                             //создаем заметку
    emit signalCreate(n);                                           //подаем сигнал о создании заметки
    this->close();                                                  //закрываем окно
}
