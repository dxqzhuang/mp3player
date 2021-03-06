#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSignalsSlots();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectSignalsSlots()
{
    connect(ui->exitButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->openFileButton,SIGNAL(pressed()), this,SLOT(openInputFile()));
    connect(ui->mainWindow_play_btn, SIGNAL(pressed()),this,SLOT(play_btn_pressed()));
    connect(ui->mainWindow_create_play_list_btn, SIGNAL(pressed()),this,SLOT(create_play_list_pressed()));
    connect(ui->mainWindow_load_play_list_btn, SIGNAL(pressed()),this,SLOT(load_play_list_pressed()));
}

void MainWindow::openInputFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.mp3");
    if(fileName.isNull())
        return;
    try
    {
        int pos = fileName.lastIndexOf(QChar('/'));
        player.play(fileName);
        QPushButton* btn = new QPushButton(fileName.right(pos));
        connect(btn, SIGNAL(pressed()), this, SLOT(play_list_item_pressed()));
        lib_manager.add_new_song(fileName);
        //---set name
        QString btn_obj_name = QString::fromStdString("mainWindow_song_");
        btn_obj_name += QString::fromStdString(std::to_string(lib_manager.get_songs().size()-1));

        btn->setObjectName(btn_obj_name);
        //----/set name
        ui->mainWindow_song_list->addWidget(btn);
        //put this song into library manager

    }catch(MP3_PLAYER_ERRORS e)
    {
        switch (e) {
        case FILE_NOT_FOUND:
            cout << "file is not found!! check your directory name" << endl;
            break;
        default:
            break;
        }
    }
    ui->fileName->setText(fileName);
    //readFile(fileName);
}

void MainWindow::load_play_list_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.playlist");
    if(fileName.isNull())
        return;
    try
    {
        int old_size = lib_manager.get_songs().size();
        lib_manager.load_this_list(fileName);

        vector<QString> songs = lib_manager.get_songs();
        for(int i=old_size; i<songs.size(); i++)
        {
            int pos = songs[i].lastIndexOf(QChar('/'));
            QPushButton* btn = new QPushButton(fileName.right(pos));
            connect(btn, SIGNAL(pressed()), this, SLOT(play_list_item_pressed()));
            //---set name
            QString btn_obj_name = QString::fromStdString("mainWindow_song_");
            btn_obj_name += QString::fromStdString(std::to_string(i));

            btn->setObjectName(btn_obj_name);
            //----/set name
            ui->mainWindow_song_list->addWidget(btn);
            cout << "new widget added!" << endl;
        }

    }catch(MP3_PLAYER_ERRORS e)
    {
        switch (e) {
        case FILE_NOT_FOUND:
            cout << "file is not found!! check your directory name" << endl;
            break;
        default:
            break;
        }
    }
    ui->fileName->setText(fileName);
    //readFile(fileName);
}





void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::play_btn_pressed()
{
    player.togglePlay();
    QString currentText = ui->mainWindow_play_btn->text();
    if(currentText == "play")
        ui->mainWindow_play_btn->setText("pause");
    else
        ui->mainWindow_play_btn->setText("play");
}


void MainWindow::play_list_item_pressed()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    QString buttonText = buttonSender->text();
    QString btnName = buttonSender->objectName();
    int index = btnName[btnName.size()-1].unicode() - '0';
    cout << "this button is pressed: " << btnName.toStdString() << endl;
    cout << "index: " << index << endl;

    //when an item(song) in the list is pressed, play it
    if(!selectionMode)
        player.play(lib_manager.get_songs()[index]);
    else{
        selectedIndeces.push_back(index);

    }

}


void MainWindow::create_play_list_pressed()
{
    if(selectionMode)
    {
        selectionMode = false;
        lib_manager.group_these_into_play_list(selectedIndeces, "myPlayList");
        selectedIndeces.clear();
        lib_manager.save_this_list("myPlayList");
        cout << "myPlayList saved" << endl;
        ui->mainWindow_create_play_list_btn->setText("create play list");
    }
    else
    {
        selectionMode = true;
        ui->mainWindow_create_play_list_btn->setText("Group them!");

    }
}
