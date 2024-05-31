#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operation_systems.h"
#include <QFile> // Подключаем класс QFile
#include <QTextStream> // Подключаем класс QTextStream
#include <QDebug>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    noteList = new QList<Note*>; //список заметок
    names = new QList<QString>; //список названий заметок
    creationwidget = new CreationWidget(); //окно для создания заметки
    loginform = new LoginForm();//окно регистрации
    redactform = new RedactForm(); // окно редактирования заметки
    //соединяем сигнал создания заметки из окна создания заметок со слотом по созданию заметки в главном окне
    connect(creationwidget, &CreationWidget::signalCreate, this, &MainWindow::slotCreate);
    //соединяем сигнал редактирования заметки из главного окна со слотом по открытию окна редактирования
    connect(this, &MainWindow::redactSignalmain, redactform, &RedactForm::redactSlot);
    //соединяем сигнал о редактировании заметки из воторого окна со слотом по применению этих изменений в главном окне
    connect(redactform, &RedactForm::redactSignalform, this, &MainWindow::slotRedact);
    //класс управления настройками
    settings = new QSettings(this);
    //загружаем настройки
    loadSettings();

    //подсказки
    ui->SearchEdit->setToolTip("Уберите текст из поля, чтобы вернуть все заметки");
    ui->SearchEdit->setToolTipDuration(0);

    ui->CreateBtn->setToolTip("Здесь вы можете создать новую заметку");
    ui->RedactBtn->setToolTip("Здесь вы можете изменить название заметки");
    ui->DeleteBtn->setToolTip("Здесь вы можете безвозвратно удалить заметку");

}

MainWindow::~MainWindow()                          //деструктор
{
    saveSettings();                                //сохраняем настройки перед выходом
    delete ui;
}

void MainWindow::saveSettings()
{
    settings->setValue("geometry", geometry());     //сохраняем местоположение и размер окна
}

void MainWindow::loadSettings()
{
    //устанавливаем положение сохранное в настройках, если пусто то применяются значения по умолчанию
    setGeometry( settings->value( "geometry", QRect(400, 200, 640, 480)).toRect() );
}


void MainWindow::on_CreateBtn_clicked()                 //слот вызывающийся сигналом клика
{
    creationwidget->show();                             //показывает окно создания заметки
}
void MainWindow::slotCreate(Note *note)                 //слот создания заметки вызвается сигналом
{                                                       //создания заметки из окна создания заметки
    choosenNote = note;                                 //устанавливаем выбранную заметку как новосозданную
    ui->NoteList->addItem(note->GetName());             //добавляем заметку в список на форме
    ui->NoteEdit->setText(choosenNote->GetContent());   //открываем новую заметку для редактирования
    noteList->append(note);                             //добавляем новую заметку в список
    names->append(note->GetName());                     //добавляем имя заметки в список имен заметок
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

void MainWindow::on_DeleteBtn_clicked()
{
    if(choosenNote != NULL ) //&& noteList->size() > 1
    {
       QMessageBox::StandardButton answer =  QMessageBox::question(this, "Удаление заметки",
       "Вы действительно хотите удалить " + choosenNote->GetName(), QMessageBox::Yes | QMessageBox::No);
       if(answer == QMessageBox::Yes)
       {
           QString nametodelete = choosenNote->GetName();             //сохраняем имя которое нужно удалить
           ui->NoteList->blockSignals(true);                          //отключаем сигналы чтобы метод клир работал нормально
           ui->NoteList->clear();                                     //очищаем форму
           ui->NoteList->blockSignals(false);                         //без этого костыля появляется ошибка доступа памяти
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
           for (int i = 0; i < noteList->size(); i++)                 //добавляем элементы обратно на форму
           {
               ui->NoteList->addItem(noteList->at(i)->GetName());
           }
           if(OPERATION_SYSTEM_OF_USER == 1)
           {
               QFile filedel("del.bat");
               if(filedel.open(QIODevice::WriteOnly | QIODevice::Text))    // Если файл успешно открыт для записи в текстовом режиме
               {                                                           // Создаем объект класса QTextStream
                   QProcess process;
                   QTextStream writeStream(&filedel);                      // и передаем ему адрес объекта fileOut
                   writeStream <<"schtasks /delete /tn " + nametodelete;
                   filedel.close();
                   process.start("del.bat");                              // Запуск файла del.bat
                   process.waitForFinished();
                   filedel.remove();
               }
           }
       }
    }
}


void MainWindow::on_SearchEdit_textChanged(const QString &arg1) //поиск заметки
{
    //переписывает список заметок так, чтобы первым стоял тот, у которого совпадает имя
    QString search = arg1;                  //имя заметки которую мы ищем

    ui->NoteList->blockSignals(true);                          //отключаем сигналы чтобы метод клир работал нормально
    ui->NoteList->clear();                                     //очищаем форму
    ui->NoteList->blockSignals(false);                         //без этого костыля появляется ошибка доступа памяти
    for (int i = 0; i < noteList->size(); i++)                 //добавляем элементы обратно на форму
    {
        QString itemname = noteList->at(i)->GetName();         //ключ по которому ищем

        if(itemname.contains(search))                          //если он есть в названии
        {
            ui->NoteList->addItem(noteList->at(i)->GetName()); //добавляем на форму
        }
        else                                                   //иначе пропускаем
        {
            continue;
        }
    }
}

void MainWindow::on_LogInBtn_clicked()                        //слот вызывающийся сигналом клика
{
    loginform->show();                                        //показывает окно регистрации
}
