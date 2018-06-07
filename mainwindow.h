#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <mp3player.h>
#include <iostream>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::MainWindow *ui;
        QString fileContents;
        mp3Player player;
        void connectSignalsSlots();
        void readFile(const QString &fileName);
        void saveFile(const QString &fileName);

    private slots:
        void openInputFile();
        void openSaveFile();
        void play_btn_pressed();
};

#endif // MAINWINDOW_H
