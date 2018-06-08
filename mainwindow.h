#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mp3player.h>
#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <librarymanager.h>
#include <iostream>
#include <QPushButton>
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
        bool selectionMode = false; //if true, the user is trying to group songs into a list.
        vector<int> selectedIndeces;
        Ui::MainWindow *ui;
        QString fileContents;
        mp3Player player;
        libraryManager lib_manager;
        void connectSignalsSlots();
        void readFile(const QString &fileName);
        void saveFile(const QString &fileName);

    private slots:
        void openInputFile();
        void openSaveFile();
        void play_btn_pressed();
        void play_list_item_pressed();
        void create_play_list_pressed();
        void load_play_list_pressed();
};

#endif // MAINWINDOW_H
