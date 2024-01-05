#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creationwidget.h"
#include <QList>
#include "note.h"
#include "redactform.h"
#include <QListWidget>
#include <QMessageBox>
#include <QSettings>
//#include <windows.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveSettings();
    void loadSettings();
public slots:
    void slotCreate(Note *note);
    void slotRedact(QString newname, QDateTime newdate);
private slots:
    void on_CreateBtn_clicked();

    void on_NoteList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_NoteEdit_textChanged();

    void on_RedactBtn_clicked();
    void on_DeleteBtn_clicked();

signals:
    void redactSignalmain(Note *choosenNote);
private:
    Ui::MainWindow *ui;
    CreationWidget *creationwidget;
    RedactForm  *redactform;
    QList<Note*> *noteList;
    QList<QString> *names;
    Note *choosenNote = NULL;
    Note *created_note;
    Note *chosenforedit = NULL;
    QSettings *settings;
};
#endif // MAINWINDOW_H
