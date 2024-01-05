#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    noteList = new QList<Note*>; //список заметок
    names = new QList<QString>; //список названий заметок
    creationwidget = new CreationWidget(); //окно для создания заметки
    redactform = new RedactForm(); // окно редактирования заметки
    //соединяем сигнал создания заметки из окна создания заметок со слотом по созданию заметки в главном окне
    connect(creationwidget, &CreationWidget::signalCreate, this, &MainWindow::slotCreate);
    //соединяем сигнал редактирования заметки из главного окна со слотом по открытию окна редактирования
    connect(this, &MainWindow::redactSignalmain, redactform, &RedactForm::redactSlot);
    //соединяем сигнал о редактировании заметки из воторого окна со слотом по применению этих изменений в главном окне
    connect(redactform, &RedactForm::redactSignalform, this, &MainWindow::slotRedact);
    //
    settings = new QSettings(this);
    loadSettings();
}

MainWindow::~MainWindow()                          //деструктор
{
    saveSettings();
    delete ui;
}

void MainWindow::saveSettings()
{
    settings->setValue("geometry", geometry());
}

void MainWindow::loadSettings()
{
    setGeometry( settings->value( "geometry", QRect(200, 200, 1000, 680)).toRect() );
}


void MainWindow::on_CreateBtn_clicked()                 //слот вызывающийся сигналом клика
{
    creationwidget->show();                             //показывает окно создания заметки
}
void MainWindow::slotCreate(Note *note)                 //слот создания заметки вызвается сигналом создания заметки из окна создания заметки
{
    choosenNote = note;                                 //устанавливаем выбранную заметку как новосозданную
    ui->NoteList->addItem(note->GetName());             //добавляем заметку в список на форме
    ui->NoteEdit->setText(choosenNote->GetContent());   //открываем новую заметку для редактирования
    noteList->append(note);                             //добавляем новую заметку в список
    names->append(note->GetName());
}

void MainWindow::slotRedact(QString newname, QDateTime newdate)
{
    QString oldname = choosenNote->GetName();          //сохраняем старое имя
    for(int i = 0; i<names->size(); i++)               //ищем позицию в списке названий старого имени
    {
        if(oldname == names->at(i))
        {
            names->removeAt(i);                         //удаляем старое имя
            break;
        }
    }
    choosenNote->SetName(newname);                       //устанавливаем новое имя
    choosenNote->SetDeadLine(newdate);                   //устанавливаем новую дату срока
    names->append(newname);                              //добавляем новое имя
    ui->NoteList->addItem(choosenNote->GetName());       //добавляем на форму отредактированную заметку
    for(int i = 0; i<noteList->size(); i++)              //ищем и удаляем старую заметку на форме
    {
        QListWidgetItem *item = ui->NoteList->item(i);
        if( !(names->contains( item->text() )) )
        {
            delete ui->NoteList->takeItem(i);
            break;
        }
    }
}

void MainWindow::on_NoteList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
   QString name = current->text();                  //имя выбранной заметки
   for (int i = 0; i < noteList->size(); i++)       // перебираем наши заметки и если её имя совпадает с выбранной,
   {                                                //то выводим её содержимое
       Note *tmp = (Note*)(noteList->at(i));
       if(name == tmp->GetName())
       {
           choosenNote = tmp;                       //промежуточная переменная, показывает заметку с которой мы работаем
           ui->NoteEdit->setText(choosenNote->GetContent());//выводим содержимое заметки на экран
       }
   }
}

void MainWindow::on_NoteEdit_textChanged()          //слот вызывающийся изменением текста
{
    if(choosenNote != NULL)
    {
        QString text = ui->NoteEdit->toPlainText();  //получаем текст в окне
        choosenNote->SetContent(text);               //устанавливаем текст в выбранной заметке
    }
}

void MainWindow::on_RedactBtn_clicked()              //слот вызывающийся сигналом клика
{
    if(choosenNote != NULL)
    {
        redactform->show();                          //показывает окно редактирования заметки
        emit redactSignalmain(choosenNote);          //посылаем сигнал с выбранной заметкой
    }
}

void MainWindow::on_DeleteBtn_clicked()       //надо доработать, некорректно удаляет последний элемент
{
    if(choosenNote != NULL ) //&& noteList->size() > 1
    {
       QMessageBox::StandardButton answer =  QMessageBox::question(this, "Удаление заметки",
       "Вы действительно хотите удалить " + choosenNote->GetName(), QMessageBox::Yes | QMessageBox::No);
       if(answer == QMessageBox::Yes)
       {
           QString nametodelete = choosenNote->GetName();          //сохраняем имя которое нужно удалить
//           delete ui->NoteList->currentItem();
//           int n = ui->NoteList->count() - 1;
//           for(int j=n; j>=0; j--)
//           {
//             QListWidgetItem *it = ui->NoteList->item(j);
//             if (it->isSelected()) delete it;
//           }
//           for(int i = 0; i < noteList->size(); i++)                 //ищем позицию в списке названий
//           {
//               QListWidgetItem *item = ui->NoteList->item(i);
//              // QMessageBox::about(this, "", item->text());
//               if(nametodelete == item->text())
//               {
//                   //ui->NoteList->removeItemWidget(item);
//                   delete ui->NoteList->takeItem(i);
//                   //delete ui->NoteList->takeItem(i);                //удаляем на форме
//                   break;
//               }
//           }
//           foreach (QListWidgetItem *NAME, ui->NoteList->selectedItems())
//           {
//              delete ui->NoteList->takeItem(ui->NoteList->row(NAME));
//           }
           ui->NoteList->blockSignals(true);
           ui->NoteList->clear();
           ui->NoteList->blockSignals(false);
           for (int i = 0; i < noteList->size(); i++)                 //удаляем в списке имен
           {
               if(nametodelete == names->at(i))
               {
                   names->removeAt(i);
                   break;
               }
           }
           for (int i = 0; i < noteList->size(); i++)                 //удаляем в списке заметок
           {
               if(nametodelete == noteList->at(i)->GetName())
               {
                   noteList->removeAt(i);
                   break;
               }
           }
           for (int i = 0; i < noteList->size(); i++)                 //удаляем в списке заметок
           {
               ui->NoteList->addItem(noteList->at(i)->GetName());
           }
       }
    }
}
