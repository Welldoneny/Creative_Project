#include "redactform.h"
#include "ui_redactform.h"

RedactForm::RedactForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RedactForm)
{
    ui->setupUi(this);
}

RedactForm::~RedactForm()
{
    delete ui;
}

void RedactForm::redactSlot(Note *choosenNote)
{
    //отображаем имя выбранной заметки
    ui->NameValueLabel->setText(choosenNote->GetName());
    //отображаем дату срока выбранной заметки
    ui->DateValueLabel->setText(choosenNote->GetDeadLineTime().toString());
}

void RedactForm::on_ApplyBtn_clicked()                          //слот вызываемый кликом по кнопке
{
    QString newname = ui->ChangeNameEdit->text();               //получаем значение для нового имени
    QDateTime newdate = ui->dateTimeEdit->dateTime();           //получаем значение для новой даты
    emit redactSignalform(newname, newdate);                    //отправляем сигнал
    this->close();                                              //закрываем окно
}
