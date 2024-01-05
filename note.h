#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>

class Note
{
protected:
    QString name; //имя заметки
    QDateTime createTime; //дата создания
    QDateTime deadLineTime; //дата срока
    QString content; // содержимое заметки
public:
    Note(); // конструктор по умолчанию, если пользователь не назвал заметку
    Note(QString name);   // конструктор с названием заметки
    Note(const Note &other); // конструктор копирования
    Note &operator=(const Note &other); // перегрузка оператора =
    QString GetName(); // возвращает имя заметки
    QString GetContent(); // возвращает содержимое заметки
    QDateTime GetCreationTime(); // возвращает дату создания заметки
    QDateTime GetDeadLineTime(); // возвращает дату срока заметки
    void SetDeadLine(QDateTime time); // устанавливает время срока
    void SetName(QString name); // устанавливает имя заметки
    void SetContent(QString content); // устанавливает содержимое заметки
};

#endif // NOTE_H
