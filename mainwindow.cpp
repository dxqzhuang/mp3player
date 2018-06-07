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
    connect(ui->saveFileButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
    connect(ui->mainWindow_play_btn, SIGNAL(pressed()),this,SLOT(play_btn_pressed()));
}

void MainWindow::readFile(const QString &fileName)
{
    char data;
    QFile input(fileName);
    input.open(QFile::ReadOnly);
    fileContents.clear();
    while(!input.atEnd())
        if(input.getChar(&data))
            fileContents += data;
    input.close();
    ui->fileContentsDisplay->clear();
    ui->fileContentsDisplay->append(fileContents);
}

void MainWindow::openSaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    saveFile(fileName);
}

void MainWindow::saveFile(const QString &fileName)
{
    QFile output(fileName);
    output.open(QFile::WriteOnly);
    output.write(fileContents.toStdString().c_str(), fileContents.size());
    output.close();
}

void MainWindow::openInputFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.mp3");
    if(fileName.isNull())
        return;
    try
    {
        player.play(fileName);
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
