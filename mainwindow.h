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
    void saveSettings();//сохраняет настройки
    void loadSettings();//загружаем настройки
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
    Ui::MainWindow *ui;//интерфейс
    CreationWidget *creationwidget;//окно создания заметок
    RedactForm  *redactform;//окно редактирования заметок
    QList<Note*> *noteList;//список заметок
    QList<QString> *names;//список названий заметок
    Note *choosenNote = NULL;//выбранная заметка в текущий момент
    QSettings *settings;//настройки
};
#endif // MAINWINDOW_H
