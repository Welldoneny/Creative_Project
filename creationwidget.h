#ifndef CREATIONWIDGET_H
#define CREATIONWIDGET_H

#include <QWidget>
#include "note.h"
namespace Ui
{
class CreationWidget;
}

class CreationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreationWidget(QWidget *parent = nullptr);
    ~CreationWidget();
signals :
    void signalCreate(Note *note);
private slots:
    void on_CreateNoteBtn_clicked();

private:
    Ui::CreationWidget *ui;
    Note* Create();
};

#endif // CREATIONWIDGET_H
