#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QDirIterator>
#include <gst/gst.h>
#include "tplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Play();

private slots:
    void on_pbPlay_clicked();

    void on_pbStop_clicked();

    void on_pbPrev_clicked();

    void on_pbNext_clicked();

    void on_pbOpen_clicked();

private:
    TPlayer * player;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
