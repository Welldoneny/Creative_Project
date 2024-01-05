#include "note.h"

Note::Note()
{
    QDate dt = QDate::currentDate();          // получаем дату и время создания
    QString n = dt.toString();                // устанавливаем вместо имени
    QTime tm = QTime::currentTime();
    QString nn = tm.toString();
    name = n + " " + nn;
    createTime = QDateTime::currentDateTime();
}
Note::Note(QString name)
{
    QDateTime *dt = new QDateTime;
    createTime = dt->currentDateTime();        //устанавливаем дату создания
    this->name = name;                         //устанавливаем имя заметки из строки в конструкторе
}
Note::Note(const Note &other)
{
    this->name = other.name;                   //конструктор копирования
    this->createTime = other.createTime;       //копируем данные из объекта other
    this->deadLineTime = other.deadLineTime;
    this->content = other.content;
}
void Note:: SetName(QString name)              // устанавливаем имя заметке
{
    this->name = name;
}
QString Note::GetName()                       //возвращаем имя заметки
{
    return this->name;
}
QString Note::GetContent()                    //возвращает содержимое заметки
{
    return this->content;
}
void Note::SetContent(QString content)        //устанавливает содержимое заметки
{
    this->content = content;
}
void Note::SetDeadLine(QDateTime time)         //устанавливает время сроков для заметки
{
    this->deadLineTime = time;
}
QDateTime Note::GetDeadLineTime()             //возвращает время срока
{
    return deadLineTime;
}
QDateTime Note::GetCreationTime()             //возвращает время создания заметки
{
    return createTime;
}
