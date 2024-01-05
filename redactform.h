#ifndef REDACTFORM_H
#define REDACTFORM_H

#include <QWidget>
#include "note.h"
namespace Ui {
class RedactForm;
}

class RedactForm : public QWidget
{
    Q_OBJECT

public:
    explicit RedactForm(QWidget *parent = nullptr);
    ~RedactForm();
public slots:
    void redactSlot(Note *choosenNote);
private:
    Ui::RedactForm *ui;
signals:
    void redactSignalform(QString newname, QDateTime newdate);
private slots:
    void on_ApplyBtn_clicked();
};

#endif // REDACTFORM_H
